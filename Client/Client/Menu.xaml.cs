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
    }

    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();
            Check_Buttons();
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

        private void Open_Best_Scores_Page(object sender, RoutedEventArgs e)
        {
            BestScores bs = new BestScores();
            bs.Show();
            this.Close();
        }

        /** function updates the buttons state by the user's state (loggen in / not) */
        private void Check_Buttons()
        {
            if (Global.isLoggedIn)
            {
                this.joinRoomB.IsEnabled = true;
                this.createRoomB.IsEnabled = true;
                this.myStatusB.IsEnabled = true;
                this.bestScoresB.IsEnabled = true;
                this.logInB.Visibility = System.Windows.Visibility.Hidden;
                this.logOutB.Visibility = System.Windows.Visibility.Visible;
            }
            else
            {
                this.joinRoomB.IsEnabled = false;
                this.createRoomB.IsEnabled = false;
                this.myStatusB.IsEnabled = false;
                this.bestScoresB.IsEnabled = false;
                this.logInB.Visibility = System.Windows.Visibility.Visible;
                this.logOutB.Visibility = System.Windows.Visibility.Hidden;
            }
        }

        private void Log_Out(object sender, RoutedEventArgs e)
        {
            Global.isLoggedIn = false;

            Menu m = new Menu();
            m.Show();
            this.Close();
        }
    }
}
