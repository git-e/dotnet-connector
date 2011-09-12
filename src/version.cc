#include "version.h"
#define concat(a, b) a ## b
[assembly:System::Reflection::AssemblyTitleAttribute(dotnet_connector_VERSIONINFO_TITLE)];
[assembly:System::Reflection::AssemblyVersionAttribute(concat(dotnet_connector_VERSIONINFO_VERSION, ".*"))];
[assembly:System::Reflection::AssemblyCompanyAttribute(dotnet_connector_VERSIONINFO_COMPANY)];
[assembly:System::Reflection::AssemblyProductAttribute(dotnet_connector_VERSIONINFO_PACKAGE)];
[assembly:System::Reflection::AssemblyCopyrightAttribute(dotnet_connector_VERSIONINFO_COPYRIGHT)];
