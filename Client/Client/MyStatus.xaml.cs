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
            this.LoggedInUser.Content = Global.LoggedInName;

            //getStatus(); TODO: add parameters


        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        void getStatus()
        {
            byte[] fullMessage = Global.Communicator.getNoDataMessage(8);
            Global.Communicator.sendMessage(fullMessage);
            byte[] statistics = Global.Communicator.reciveResponse();
            getStatisticsResponse response = Global.Communicator.getStatisticsResponse(statistics);
            // TODO: get user's status and apply the 4 variables above
        }
    }
}
