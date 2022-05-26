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
    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();
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
    }
}
