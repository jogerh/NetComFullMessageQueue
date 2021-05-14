#include "pch.h"
#include "ComServer.h"
#include <comdef.h>

HRESULT CComServer::LongRunningTask(ICallbackClient* comObjectOnMainThread)
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

HRESULT CCallbackClient::Callback()
{
    return S_OK;
}
