/*
  object.cc -- handling native and manged object instances
  Copyright (c) 2011 Eric Karge

  dotnet-connector, a small library assisting create c++/.net wrappers
  The authors can be contacted at <eric@struction.de>

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#define dotnet_connector_BUILD
#include <dnc/class>
#include <msclr/lock.h>

namespace dotnet_connector {
/*
native_handle::native_handle(handle<object> x) :
	m_const(false),
	m_volatile(false),
	m_ptr(const_cast<void *>(x.pointer()))
{}

native_handle::native_handle(handle<object const> x) :
	m_const(true),
	m_volatile(false),
	m_ptr(const_cast<void *>(x.pointer()))
{}

native_handle::native_handle(handle<object volatile> x) :
	m_const(false),
	m_volatile(true),
	m_ptr(const_cast<void *>(x.pointer()))
{}

native_handle::native_handle(handle<object const volatile> x) :
	m_const(true),
	m_volatile(true),
	m_ptr(const_cast<void *>(x.pointer()))
{}
*/

void *
NativeObject::Pointer::get() {
	if ( m_state & c_const )
		throw gcnew System::AccessViolationException("const violation");
	if ( m_state & c_volatile )
		throw gcnew System::AccessViolationException("volatile violation");
	return m_ptr;
}

void const *
NativeObject::ConstPointer::get() {
	if ( m_state & c_volatile )
		throw gcnew System::AccessViolationException("volatile violation");
	return m_ptr;
}

void volatile *
NativeObject::VolatilePointer::get() {
	if ( m_state & c_const )
		throw gcnew System::AccessViolationException("const violation");
	return m_ptr;
}

void const volatile *
NativeObject::CVPointer::get() {
	return m_ptr;
}

bool
NativeObject::Const::get() {
	return m_state & c_const;
}

bool
NativeObject::Volatile::get() {
	return m_state & c_volatile;
}

bool
NativeObject::DeleteOnDispose::get() {
	return m_state & c_delete_on_dispose;
}

bool
NativeObject::IsManaged::get() {
	return m_state & c_managed;
}

void
NativeObject::Disconnect() {
	m_ptr = nullptr;
	m_state = 0; 
}

void
NativeObject::Claim() {
	msclr::lock(this);
	m_state |= c_delete_on_dispose;
}

void
NativeObject::Release() {
	m_state &= ~c_delete_on_dispose;
}

NativeObject::~NativeObject() {
}

NativeObject::NativeObject(native_handle x, bool dod, bool managed) :
	m_ptr(x.m_ptr),
	m_state((x.m_const ? c_const : 0) | (x.m_volatile ? c_volatile : 0) | (dod ? c_delete_on_dispose : 0) | (managed ? c_managed : 0))
{}

void
gchandle<object>::free(gchandle * & _handle)
{
	if ( _handle != nullptr ) {
		static_cast<GCHandle>(IntPtr(_handle)).Free();
	}
	_handle = nullptr;
}

gchandle<object> *
gchandle<object>::clone(gchandle * _handle)
{
	return allocate(_handle->that());
}

void
gchandle<object>::change_type(gchandle * & _handle, handle_type _type) {
	gchandle *
	old_handle = _handle;

	_handle = static_cast<gchandle *>(static_cast<IntPtr>(GCHandle::Alloc(_handle->that(),
	   _type == Weak                  ? GCHandleType::Weak :
	   _type == WeakTrackResurrection ? GCHandleType::WeakTrackResurrection :
	   _type == Pinned                ? GCHandleType::Pinned :
	   GCHandleType::Normal)).ToPointer());

	free(old_handle);
}

} /* namespace dotnet_connector */
