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
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for EndGame.xaml
    /// </summary>
    public partial class EndGame : Window
    {
        public List<PlayerResults> result;
        public List<Result> SortedResults;
        public int questionTimer;
        public int yourScore;
        public string winningUser;

        public EndGame(List<PlayerResults> PlayerResults, int TimePerQuestion)
        {
            this.result = PlayerResults;
            this.questionTimer = TimePerQuestion;
            getSortedResults();
            InitializeComponent();
            if (winningUser.Equals(Global.LoggedInName))
            {
                MessageBox.Show("You won!!!\nYour score was: " + this.SortedResults[0].Score);
                Storyboard fireworkblack = this.FindResource("fireworkblack") as Storyboard;
                fireworkblack.Completed += Sb_Completed;
                fireworkblack.Begin();

                Storyboard fireworkblue = this.FindResource("fireworkBlue") as Storyboard;
                fireworkblue.Begin();

                Storyboard fireworkred = this.FindResource("fireworkFirebrick") as Storyboard;
                fireworkred.Begin();

            }
            else
            {
                MessageBox.Show("The user: " + this.winningUser + " won\nHis score is: " + this.SortedResults[0].Score);
            }

            displayusers();

        }

        private void Sb_Completed(object? sender, EventArgs e)
        {
            Storyboard fireworkblack = this.FindResource("fireworkblack") as Storyboard;
            fireworkblack.Begin();
            Storyboard fireworkblue = this.FindResource("fireworkBlue") as Storyboard;
            fireworkblue.Begin();
            Storyboard fireworkred = this.FindResource("fireworkFirebrick") as Storyboard;
            fireworkred.Begin();
        }

        private void displayusers()
        {

            for(int i = 0; i < this.SortedResults.Count(); i++)
            {
                UserScorListBoxist.Items.Add(this.SortedResults[i]);
            }
        }



        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            byte[] fullMessage = Global.Communicator.getNoDataMessage(14);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();

            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void getSortedResults()
        {
            List<Result> temp = new List<Result>();
            for(int i = 0; i < this.result.Count(); i++)
            {
                int score = (int)(((1 -((double)result[i].averageAnswerTime / (double)questionTimer / 2.00)) * 1000) * result[i].correctAnswerCount);
                if(Global.LoggedInName.Equals(result[i].username))
                {
                    this.yourScore = score;
                    temp.Add(new Result() { User = result[i].username, Score = score, Background = "White" });
                }
                else
                {
                    temp.Add(new Result() { User = result[i].username, Score = score, Background = "Beige" });
                }
            }
            temp.Sort((p, q) => p.Score.CompareTo(q.Score));
            temp.Reverse();
            this.winningUser = temp[0].User;
            this.SortedResults = temp;
        }
    }
}
public class Result
{
    public string User { get; set; }
    public int Score { get; set; }
    public string Background { get; set; }
}
