using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
using System.Net.Sockets;
using System.Net;

namespace Client
{
    class Global
    {
        public static bool IsLoggedIn = false;
        public static string LoggedInName = "";
        public static Communicator Communicator = new Communicator();
        public static AudioManager audioWindow = new AudioManager();
    }

    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();
            Check_Buttons();
            this.LoggedInUser.Content = Global.LoggedInName;
        }

        private void Quit(object sender, RoutedEventArgs e)
        {
            if (Global.IsLoggedIn)
            {
                Global.IsLoggedIn = false;
                Global.LoggedInName = "";
                byte[] fullMessage = Global.Communicator.getNoDataMessage(3);
                Global.Communicator.sendMessage(fullMessage);
                Global.Communicator.reciveResponse();
            }
            this.Close();
            Global.audioWindow.Close();
        }

        private void Open_Login_Page(object sender, RoutedEventArgs e)
        {
            var li = new Login();
            li.Show();
            this.Close();
        }

        private void Open_Sign_Up_Page(object sender, RoutedEventArgs e)
        {
            var su = new SignUp();
            su.Show();
            this.Close();
        }

        private void Open_Create_Room_Page(object sender, RoutedEventArgs e)
        {
            var cr = new CreateRoom();
            cr.Show();
            this.Close();
        }

        private void Open_My_Status_Page(object sender, RoutedEventArgs e)
        {
            var ms = new MyStatus();
            ms.Show();
            this.Close();
        }

        private void Open_Best_Scores_Page(object sender, RoutedEventArgs e)
        {
            var bs = new BestScores();
            bs.Show();
            this.Close();
        }

        private void Open_Join_Room_page(object sender, RoutedEventArgs e)
        {
            var jr = new JoinRoom();
            jr.Show();
            this.Close();
        }

        private void Open_Audio_Manager_Page(object sender, RoutedEventArgs e)
        {
            Global.audioWindow.Show();
        }

        /** function updates the buttons state by the user's state (loggen in / not) */
        private void Check_Buttons()
        {
            if (Global.IsLoggedIn)
            {
                this.JoinRoomB.IsEnabled = true;
                this.SignUpB.IsEnabled = false;
                this.CreateRoomB.IsEnabled = true;
                this.MyStatusB.IsEnabled = true;
                this.BestScoresB.IsEnabled = true;
                this.LogInB.Visibility = System.Windows.Visibility.Hidden;
                this.LogOutB.Visibility = System.Windows.Visibility.Visible;
            }
            else
            {
                this.JoinRoomB.IsEnabled = false;
                this.SignUpB.IsEnabled = true;
                this.CreateRoomB.IsEnabled = false;
                this.MyStatusB.IsEnabled = false;
                this.BestScoresB.IsEnabled = false;
                this.LogInB.Visibility = System.Windows.Visibility.Visible;
                this.LogOutB.Visibility = System.Windows.Visibility.Hidden;
            }
        }

        private void Log_Out(object sender, RoutedEventArgs e)
        {
            Global.IsLoggedIn = false;
            Global.LoggedInName = "";
            byte[] fullMessage = Global.Communicator.getNoDataMessage(3);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();
            var m = new Menu();
            m.Show();
            this.Close();
        }
    }
}
