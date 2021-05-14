// ComServer.cpp : Implementation of DLL Exports.


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ComServerModule_i.h"
#include "ComServerModule_i.c"

class CComServerModule : public ATL::CAtlDllModuleT<CComServerModule>
{
public:
    DECLARE_LIBID(LIBID_ComServerLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMSERVERMODULE, "{6ed1b1aa-807b-4a28-87b6-fcdc18ab8dc3}")
};

CComServerModule s_atlModule;

using namespace ATL;

STDAPI DllCanUnloadNow(void)
{
    return s_atlModule.DllCanUnloadNow();
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
    return s_atlModule.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer(void)
{
    return s_atlModule.DllRegisterServer();
}

STDAPI DllUnregisterServer(void)
{
    return s_atlModule.DllUnregisterServer();
}

