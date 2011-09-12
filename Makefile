CXX=cl
CXXFLAGS=/clr /EHa /O2
# CXXFLAGS=/clr /EHa /Zi /MD
RC=rc
RCFLAGS=
LD=link
LDFLAGS=
# LDFLAGS=/DEBUG

VERSION=1.1
OBJECTS=build\object.obj build\exception.obj build\version.obj build\dotnet-connector.res
all: build\dotnet-connector.dll build\dotnet-connector.signed.dll

build\dotnet-connector.dll: $(OBJECTS)
	$(LD) $(LDFLAGS) /VERSION:$(VERSION) /DLL /OUT:$@ $**

build\dotnet-connector.signed.dll: $(OBJECTS)
	sn -k build\dotnet-connector.key
	$(LD) $(LDFLAGS) /VERSION:$(VERSION) /KEYFILE:build\dotnet-connector.key /DLL /OUT:$@ $**

clean:
	del /Q build\*.*

{src\}.cc{build\}.obj:
	$(CXX) $(CXXFLAGS) /Iinclude /c $< /Fo$@

{src\}.rc{build\}.res:
	$(RC) $(RCFLAGS) /fo $@ $<
