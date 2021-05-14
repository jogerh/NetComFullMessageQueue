#pragma once
#include "resource.h" // main symbols
#include "ComServerModule_i.h"

using namespace ATL;

class ATL_NO_VTABLE CComServer : public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CComServer, &CLSID_ComServer>,
    public IComServer
{
public:
    DECLARE_REGISTRY_RESOURCEID(IDR_COMSERVER)

    BEGIN_COM_MAP(CComServer)
        COM_INTERFACE_ENTRY(IComServer)
    END_COM_MAP()

    HRESULT LongRunningTask(ICallbackClient* slave) override;
};

OBJECT_ENTRY_AUTO(CLSID_ComServer, CComServer)


class ATL_NO_VTABLE CCallbackClient : public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CCallbackClient, &CLSID_ComServer>,
    public ICallbackClient
{
public:
    DECLARE_REGISTRY_RESOURCEID(IDR_CALLBACKCLIENT)

    BEGIN_COM_MAP(CCallbackClient)
        COM_INTERFACE_ENTRY(ICallbackClient)
    END_COM_MAP()

    HRESULT Callback() override;
};

OBJECT_ENTRY_AUTO(CLSID_CallbackClient, CCallbackClient)