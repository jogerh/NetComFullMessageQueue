using System;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using ComServerLib;
namespace FullMessageQueueNet
{
    public partial class MainWindow
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs args)
        {
            using (SingleThreadedApartment apartment = new SingleThreadedApartment())
            {
                // First, create a COM server on a separate single threaded apartment (STA)
                var comServerOnSeparateApartment = apartment.CreateInstance<IComServer>("ComServerLib.ComServer.1");

                // Then, Create another instance on the main thread STA. This will be the object processing callbacks
                Type comClientType = Type.GetTypeFromProgID("ComServerLib.CallbackClient.1");
                var comObjectOnMainThread = Activator.CreateInstance(comClientType) as CallbackClient;

                try
                {
                    // Start a long running task that periodically calls callbacks on the COM object on the main thread
                    comServerOnSeparateApartment.LongRunningTask(comObjectOnMainThread);
                }
                catch (COMException e)
                {
                    // Oops. The COM server failed to call calbacks from the server STA onto the maint thread STA.
                    MessageBox.Show($"COM Server callback failed: {e.Message}");
                }
            }
        }

        internal class SingleThreadedApartment : IDisposable
        {
            private Thread m_thread; // the STA thread
            private readonly TaskScheduler m_scheduler;

            // Set up the apartment and make it ready for creating instances on the apartment
            public SingleThreadedApartment()
            {
                var schedulerFuture = new TaskCompletionSource<TaskScheduler>();

                // start the STA thread with WPF Dispatcher
                m_thread = new Thread(_ =>
                {
                    // post a callback to get the TaskScheduler
                    Dispatcher.CurrentDispatcher.InvokeAsync( () => schedulerFuture.SetResult(TaskScheduler.FromCurrentSynchronizationContext()), DispatcherPriority.ApplicationIdle);

                    // run the message loop
                    Dispatcher.Run();
                });

                m_thread.SetApartmentState(ApartmentState.STA);
                m_thread.IsBackground = true;
                m_thread.Start();
                m_scheduler = schedulerFuture.Task.Result;
            }

            // Creates a COM object on the STA
            public T CreateInstance<T>(string progid) where T : class
            {
                T instance = null;
                InvokeAsync(() =>
                {
                    Type comServerType = Type.GetTypeFromProgID(progid);
                    instance = Activator.CreateInstance(comServerType) as T;
                }).Wait();
                return instance;

            }

            // shutdown the STA thread
            public void Dispose()
            {
                if (m_thread == null || !m_thread.IsAlive) 
                    return;
                InvokeAsync(Dispatcher.ExitAllFrames);
                m_thread.Join();
                m_thread = null;
            }

            private Task InvokeAsync(Action action)
            {
                return Task.Factory.StartNew(action, CancellationToken.None, TaskCreationOptions.None, m_scheduler);
            }
        }
    }
}
