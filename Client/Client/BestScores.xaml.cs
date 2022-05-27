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
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for BestScores.xaml
    /// </summary>
    public partial class BestScores : Window
    {
        public BestScores()
        {
            InitializeComponent();
            this.LoggedInUser.Content = Global.loggedInName;

            getbestScores();
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void getbestScores()
        {
            /*
            TODO: update labels (from server):
            this.first.Content = 
            this.second.Content = 
            this.third.Content = 
            */
        }
    }
}
