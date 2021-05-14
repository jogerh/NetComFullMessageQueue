using System;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using ComServerLib;
namespace FullMessageQueueNet
{
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        IATLControl m_comServerOnSeparateApartment;

        private void Button_Click(object sender, RoutedEventArgs args)
        {
            using (WpfApartment apartment = new WpfApartment())
            {
                // First, create a COM server on a separate single threaded apartment (STA)
                // Calls to this COM server will have to be marshalled through the regular
                // COM RPC mechanism. Likewise, calls from the COM server apartment into
                // the main thread STA have to be marshaled onto the main thread.
                Type comServerType = Type.GetTypeFromProgID("ComServerLib.ATLControl.1");
                
                apartment.Invoke(() =>
                {
                    m_comServerOnSeparateApartment = Activator.CreateInstance(comServerType) as ATLControl;
                });

                // Create another instance on the main thread STA. This will be the object processing callbacks
                var comObjectOnMainThread = Activator.CreateInstance(comServerType) as ATLControl;

                try
                {
                    // Start a long running task that periodically calls callbacks on the COM object on the main thread
                    m_comServerOnSeparateApartment.LongRunningTask(comObjectOnMainThread);
                }
                catch (COMException e)
                {
                    // Oops. The COM server failed to call calbacks from the server STA onto the maint thread STA.
                    MessageBox.Show($"COM Server callback failed: {e.Message}");
                }
            }
        }


        // Copy paste from internet.
        internal class WpfApartment : IDisposable
        {
            Thread _thread; // the STA thread
            TaskScheduler scheduler;

            public WpfApartment()
            {
                var tcs = new TaskCompletionSource<TaskScheduler>();

                // start the STA thread with WPF Dispatcher
                _thread = new Thread(_ =>
                {
                    // post a callback to get the TaskScheduler
                    Dispatcher.CurrentDispatcher.InvokeAsync(
                    () => tcs.SetResult(TaskScheduler.FromCurrentSynchronizationContext()),
                    DispatcherPriority.ApplicationIdle);

                    // run the WPF Dispatcher message loop
                    Dispatcher.Run();
                });

                _thread.SetApartmentState(ApartmentState.STA);
                _thread.IsBackground = true;
                _thread.Start();
                scheduler = tcs.Task.Result;
            }

            // shutdown the STA thread
            public void Dispose()
            {
                if (_thread != null && _thread.IsAlive)
                {
                    InvokeAsync(() => Dispatcher.ExitAllFrames());
                    _thread.Join();
                    _thread = null;
                }
            }

            // Task.Factory.StartNew wrappers
            public Task InvokeAsync(Action action)
            {
                return Task.Factory.StartNew(action,
                    CancellationToken.None, TaskCreationOptions.None, this.scheduler);
            }

            public void Invoke(Action action)
            {
                InvokeAsync(action).Wait();
            }
        }
    }
}
