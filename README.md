# Reproducer for issues with cross-apartment calls to COM functions that executes for a long time

## Problem summary
We observe issues when calling COM servers from .NET code that uses the Dispatcher utility. When an outoing COM call to a different apartment takes a long time to execute, the main thread message queue is getting filled with WM_TIMER messages. Eventually, the capacity of 10000 elements is reached, and the main thread is no longer able to post messages to the message queue. This causes several problems, for example, callbacks from other COM apartments to the main thread fails.

## Investigation
This is a general problem with COM when a cross apartment function call takes a long time and there are active timers. Usually, it is possible to work around the problem by ensuring that there are not too many high frequency timers active. The problem gets worse with the .NET Dispatcher utility. This utility creates timers that run with a period of 10 ms. The .NET framework therefore makes it highly likely to face full message queues if an outgoing COM call takes a long time. 

Raymond Chen explains the mechanisms behind this COM issue in https://devblogs.microsoft.com/oldnewthing/20160624-00/?p=93745. While waiting for the outgoing COM call to complete, the COM modal loop calls PeekMessage() with a WM_SYSTIMER filter. This forces WM_TIMER messages to be generated on the message queue when there are due timers, even if there is no message loop that pumps these messages.

## Reproducer
The reproducer consists of two projects, a COM server implemented in ATL, and a client UI application implemented in C#/WPF. The COM server has a long running function that periodically calls a callback to a client callback listener. The UI application creates a COM server on a non-main-thread single threaded apartment, and passes it a client callback listener from the main thread apartment. The single threaded apartment is implemented using the System.Windows.Threading.Dispatcher.

The long running COM function is invoked by pushing the big button in the UI. This forces the main thread to enter the COM modal loop, because the server lives on a different apartment. During normal execution, the COM server successfully calls the client callback listener, since the COM modal loop allows for executing callbacks back onto the main thread. 

Unfortunately, while in the COM modal loop, the Dispatcher timers are pushed onto the main thread message queue, and eventually the server is unable to call the callback listener anymore, receiving RPC_E_SYS_CALL_FAILED errors.

The screen shot below shows expected output after pushing the button and waiting for a while. Here, the COM server returns an error code because it fails to call back to the main thread due to full main thread message queue:

![image](https://user-images.githubusercontent.com/16581681/118329032-d3a26a80-b506-11eb-9183-28b0aee6aee0.png)

## Build instructions
* Build debug configuration of solution.sln as administrator (registration of COM server is necessary, and happens automatically as part of the build)

## Instructions to run the reproducer
* Run FullMessageQueueNet\bin\x64\Debug\FullMessageQueueNet.exe, and push the button in the UI.
* Wait (if debugger is attached, the problem happens within a couple of minutes, otherwise it can take significantly more)
* Observe a dialog box showing the error message that is received by the COM server when attempting to call into the main thread.
