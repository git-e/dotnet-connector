/*
  version.cc -- library version information
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

#include "version.h"
#define concat(a, b) a ## b
[assembly:System::Reflection::AssemblyTitleAttribute(dotnet_connector_VERSIONINFO_TITLE)];
[assembly:System::Reflection::AssemblyVersionAttribute(concat(dotnet_connector_VERSIONINFO_VERSION, ".*"))];
[assembly:System::Reflection::AssemblyCompanyAttribute(dotnet_connector_VERSIONINFO_COMPANY)];
[assembly:System::Reflection::AssemblyProductAttribute(dotnet_connector_VERSIONINFO_PACKAGE)];
[assembly:System::Reflection::AssemblyCopyrightAttribute(dotnet_connector_VERSIONINFO_COPYRIGHT)];
