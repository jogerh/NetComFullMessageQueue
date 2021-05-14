// ATLControl.h : Declaration of the CATLControl
#pragma once
#include "resource.h" // main symbols
#include "ComServer_i.h"

using namespace ATL;


// CATLControl
class ATL_NO_VTABLE CATLControl : public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<IATLControl, &IID_IATLControl, &LIBID_ComServerLib, /*wMajor =*/1, /*wMinor =*/0>,
    public CComCoClass<CATLControl, &CLSID_ATLControl>
{
public:
    DECLARE_REGISTRY_RESOURCEID(IDR_ATLCONTROL)

    BEGIN_COM_MAP(CATLControl)
        COM_INTERFACE_ENTRY(IATLControl)
        COM_INTERFACE_ENTRY(IUnknown)
    END_COM_MAP()

    HRESULT LongRunningTask(IATLControl* slave) override;
    HRESULT Callback() override;
};

OBJECT_ENTRY_AUTO(__uuidof(ATLControl), CATLControl)
