using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        void App_DispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            Global.IsLoggedIn = false;
            Global.LoggedInName = "";
            byte[] fullMessage = Global.Communicator.getNoDataMessage(3);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();

            // Prevent default unhandled exception processing
            e.Handled = true;
        }

        private void Application_Exit(object sender, ExitEventArgs e)
        {
            Global.IsLoggedIn = false;
            Global.LoggedInName = "";
            byte[] fullMessage = Global.Communicator.getNoDataMessage(3);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();

        }
    }
}
