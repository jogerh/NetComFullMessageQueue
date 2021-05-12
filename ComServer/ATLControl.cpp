// ATLControl.cpp : Implementation of CATLControl
#include "pch.h"
#include "ATLControl.h"

#include <comdef.h>


// CATLControl
HRESULT CATLControl::LongRunningTask(IATLControl* comObjectOnMainThread)
{
    HRESULT result = S_OK;
    while (SUCCEEDED(result)) {
        Sleep(1000);
        // System Call Failed returned if main thread 
        // message queue is full
        result = comObjectOnMainThread->Callback(); 
    }
    return result;
}

HRESULT CATLControl::Callback()
{
    return S_OK;
}
