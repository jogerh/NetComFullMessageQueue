# NetComFullMessageQueue
Reproducing issues with .net dispatcher and com objects

If system main thread is blocked in a long-running out-going COM call, the main thread message queue is eventually filled with WM_TIMER messages.

This is a general problem with COM when the main thread is used to execute long running tasks, particularly related to the .net Dispatcher that introduces high frequency timers.

Expected output after pushing the button and waiting for a while:

![image](https://user-images.githubusercontent.com/16581681/118053399-bba2dd80-b384-11eb-820f-7181545c70ac.png)
