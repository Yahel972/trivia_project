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
using System;

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
            byte[] fullMessage = Global.communicator.getNoDataMessage(8);
            Global.communicator.sendMessage(fullMessage);
            byte[] statistics = Global.communicator.reciveResponse();
            getStatisticsResponse response = Global.communicator.getStatisticsResponse(statistics);
            this.first.Content = response.statistics[0].Substring(0, response.statistics[0].IndexOf(':')) + "-" + response.statistics[0].Substring(response.statistics[0].IndexOf(':') + 1);
            this.second.Content = response.statistics[1].Substring(0, response.statistics[1].IndexOf(':')) + "-" + response.statistics[1].Substring(response.statistics[1].IndexOf(':') + 1);
            this.third.Content = response.statistics[2].Substring(0, response.statistics[2].IndexOf(':')) + "-" + response.statistics[2].Substring(response.statistics[2].IndexOf(':') + 1);

        }
    }
}
