/*
  exception.cc -- exception marshaling
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
#include <dnc/exception>
#include <msclr/lock.h>
using System::Runtime::InteropServices::Marshal;
using System::IntPtr;

namespace dotnet_connector {
NativeException::NativeException(native_exception_ptr const & eptr, System::String ^ message) :
	System::Exception(message),
	m_exception(new native_exception_ptr(eptr))
{}

NativeException::~NativeException()
{
	delete m_exception;
}

native_exception_ptr
NativeException::Pointer::get()
{
	return *m_exception;
}

managed_exception::managed_exception(gchandle<::dotnet_connector::exception> * exception) :
	std::exception(),
	m_exception(exception),
	m_what()
{
	try {
		m_what.reset(static_cast<char const *>(Marshal::StringToHGlobalAnsi(exception->that()->Message).ToPointer()), &m_what_deleter);
	}
	catch(...) {
	}
}

void
managed_exception::m_what_deleter(char const * what_ptr)
{
	Marshal::FreeHGlobal(IntPtr(const_cast<char *>(what_ptr)));
}

void
managed_exception::throw_managed() const
{
	throw this->managed();
}

char const *
managed_exception::what() const throw() {
	return m_what.get();
}

managed_exception::~managed_exception() {
}

void
marshal<exception>::from_native(std::exception_ptr const & eptr)
{
	try {
		std::rethrow_exception(eptr);
	}
	catch (managed_exception const & e) {
		throw e.managed()->that();
	}
	catch (std::exception const & e) {
		throw gcnew NativeException(native_exception_ptr(std::current_exception()), Marshal::PtrToStringAnsi(IntPtr(const_cast<char *>(e.what()))));
	}
}

void
relay<exception>::throw_managed(std::exception_ptr const & eptr, char const * what)
{
	throw gcnew NativeException(eptr, Marshal::PtrToStringAnsi(IntPtr(const_cast<char *>(what))));
}

} /* namespace dotnet_connector */
