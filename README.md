# NetComFullMessageQueue
Reproducing issues with .net dispatcher and com objects

If system main thread is blocked in a long-running out-going COM call, the main thread message queue is eventually filled with WM_TIMER messages.

This is a general problem with COM when the main thread is used to execute long running tasks, particularly related to the .net Dispatcher that introduces high frequency timers.

Raymond Chen writes about this problem in https://devblogs.microsoft.com/oldnewthing/20160624-00/?p=93745.

Screen shot below shows expected output after pushing the button and waiting for a while. Here, the COM server returns an error code because it fails to call back to the main thread due to full main thread message queue:

![image](https://user-images.githubusercontent.com/16581681/118053399-bba2dd80-b384-11eb-820f-7181545c70ac.png)
