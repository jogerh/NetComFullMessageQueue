// ComServer.cpp : Implementation of DLL Exports.


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ComServer_i.h"

class CComServerModule : public ATL::CAtlDllModuleT<CComServerModule>
{
public:
    DECLARE_LIBID(LIBID_ComServerLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMSERVER, "{6ed1b1aa-807b-4a28-87b6-fcdc18ab8dc3}")
};

CComServerModule _AtlModule;

using namespace ATL;

// Used to determine whether the DLL can be unloaded by OLE.
    STDAPI
    DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type.
    STDAPI
    DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
    STDAPI
    DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
    return hr;
}

// DllUnregisterServer - Removes entries from the system registry.
    STDAPI
    DllUnregisterServer(void)
{
    HRESULT hr = _AtlModule.DllUnregisterServer();
    return hr;
}

