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

namespace Client
{
    class Global
    {
        public static bool isLoggedIn = false;
        public static string loggedInName = "";
    }

    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();
            Check_Buttons();
            this.LoggedInUser.Content = Global.loggedInName;
        }

        private void Quit(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Open_Login_Page(object sender, RoutedEventArgs e)
        {
            Login li = new Login();
            li.Show();
            this.Close();
        }

        private void Open_Sign_Up_Page(object sender, RoutedEventArgs e)
        {
            SignUp su = new SignUp();
            su.Show();
            this.Close();
        }

        private void Open_Create_Room_Page(object sender, RoutedEventArgs e)
        {
            CreateRoom cr = new CreateRoom();
            cr.Show();
            this.Close();
        }

        private void Open_My_Status_Page(object sender, RoutedEventArgs e)
        {
            MyStatus ms = new MyStatus();
            ms.Show();
            this.Close();
        }

        private void Open_Best_Scores_Page(object sender, RoutedEventArgs e)
        {
            BestScores bs = new BestScores();
            bs.Show();
            this.Close();
        }

        private void Open_Join_Room_page(object sender, RoutedEventArgs e)
        {
            JoinRoom jr = new JoinRoom();
            jr.Show();
            this.Close();
        }

        /** function updates the buttons state by the user's state (loggen in / not) */
        private void Check_Buttons()
        {
            if (Global.isLoggedIn)
            {
                this.joinRoomB.IsEnabled = true;
                this.signUpB.IsEnabled = false;
                this.createRoomB.IsEnabled = true;
                this.myStatusB.IsEnabled = true;
                this.logInB.Visibility = System.Windows.Visibility.Hidden;
                this.logOutB.Visibility = System.Windows.Visibility.Visible;
            }
            else
            {
                this.joinRoomB.IsEnabled = false;
                this.signUpB.IsEnabled = true;
                this.createRoomB.IsEnabled = false;
                this.myStatusB.IsEnabled = false;
                this.logInB.Visibility = System.Windows.Visibility.Visible;
                this.logOutB.Visibility = System.Windows.Visibility.Hidden;
            }
        }

        private void Log_Out(object sender, RoutedEventArgs e)
        {
            Global.isLoggedIn = false;
            Global.loggedInName = "";

            Menu m = new Menu();
            m.Show();
            this.Close();
        }
    }
}
