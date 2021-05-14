#include "pch.h"
#include "ComServer.h"
#include <comdef.h>

HRESULT CComServer::LongRunningTask(IComServer* comObjectOnMainThread)
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

HRESULT CComServer::Callback()
{
    return S_OK;
}
