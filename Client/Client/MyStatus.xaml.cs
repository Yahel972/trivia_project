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
    /// Interaction logic for MyStatus.xaml
    /// </summary>
    public partial class MyStatus : Window
    {
        int numOfGames;
        int numOfRightAnswers;
        int numOfWrongAnswers;
        double avgTimePerAnswer;

        public MyStatus()
        {
            InitializeComponent();
            this.LoggedInUser.Content = Global.loggedInName;

            getStatus();


        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        void getStatus()
        {
            // TODO: get user's status and apply the 4 variables above
        }
    }
}
