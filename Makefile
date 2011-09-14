VERSION=1.1

CXX=cl
CXXFLAGS=/clr /EHa /O2
# CXXFLAGS=/clr /EHa /Zi /MD
RC=rc
RCFLAGS=
LD=link
LDFLAGS=
# LDFLAGS=/DEBUG

BUILDDIR=build
SRCDIR=src
OBJECTS=$(BUILDDIR)\object.obj $(BUILDDIR)\exception.obj $(BUILDDIR)\version.obj $(BUILDDIR)\dotnet-connector.res

all: $(BUILDDIR)\dotnet-connector.dll $(BUILDDIR)\dotnet-connector.signed.dll

$(OBJECTS):

$(BUILDDIR)\dotnet-connector.dll: $(OBJECTS)
	$(LD) $(LDFLAGS) /VERSION:$(VERSION) /DLL /OUT:$@ $**

$(BUILDDIR)\dotnet-connector.signed.dll: $(OBJECTS)
	sn -k $(BUILDDIR)\dotnet-connector.key
	$(LD) $(LDFLAGS) /VERSION:$(VERSION) /KEYFILE:$(BUILDDIR)\dotnet-connector.key /DLL /OUT:$@ $**

clean:
	del /Q $(BUILDDIR)\*.*

{$(SRCDIR)\}.cc{$(BUILDDIR)\}.obj:
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) /Iinclude /c $< /Fo$@

{$(SRCDIR)\}.rc{$(BUILDDIR)\}.res:
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(RC) $(RCFLAGS) /fo $@ $<
