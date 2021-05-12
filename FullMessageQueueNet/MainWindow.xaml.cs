using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using ComServerLib;
namespace FullMessageQueueNet
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ComServerLib.ATLControl comObjectOnSeparateApartment;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            using (WpfApartment apartment = new WpfApartment())
            {
                Type t = Type.GetTypeFromProgID("ComServerLib.ATLControl.1");
                EventWaitHandle h = new EventWaitHandle(false, EventResetMode.AutoReset);

                apartment.Invoke(() =>
                {
                    comObjectOnSeparateApartment = Activator.CreateInstance(t) as ATLControl;
                    h.Set();
                });

                h.WaitOne();

                var comObjectOnMainThread = Activator.CreateInstance(t) as ATLControl;
                comObjectOnSeparateApartment.LongRunningTask(comObjectOnMainThread);
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
