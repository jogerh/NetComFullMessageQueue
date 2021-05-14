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

    HRESULT LongRunningTask(IComServer* slave) override;
    HRESULT Callback() override;
};

OBJECT_ENTRY_AUTO(CLSID_ComServer, CComServer)
