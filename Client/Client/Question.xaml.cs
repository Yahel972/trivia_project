using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Diagnostics;

namespace Client
{
    public partial class Question : Window
    {
        public uint TimePerQuestion;
        public uint NumOfQuestions;
        public uint CurrentQuestion;

        public Button[] Answers;
        public int CorrectAnswer;
        public int ClickedButton;
        public bool InGame;

        public Thread t;
        Stopwatch stopwatch;

        public Question(uint time_per_question, uint num_of_questions, uint current_question = 1)
        {
            TimePerQuestion = time_per_question;
            NumOfQuestions = num_of_questions;
            CurrentQuestion = current_question;
            this.ClickedButton = 0;  // no button clicked yet
            this.InGame = true;
            stopwatch = new Stopwatch();

            InitializeComponent();
            Answers = new[] { this.Answer1B, this.Answer2B, this.Answer3B, this.Answer4B };

            t = new Thread(new ThreadStart(Game));
            t.Start();
        }

        private void Game()
        {
            for (int i = 0; i < NumOfQuestions && InGame; i++)
            {
                byte[] fullMessage = Global.Communicator.getNoDataMessage(15);
                Global.Communicator.sendMessage(fullMessage);
                GetQuestionResponse response = Global.Communicator.getQuestionResponse(Global.Communicator.reciveResponse());

                this.Dispatcher.Invoke(() =>
                {
                    this.QuestionContent.Content = response.question;
                    List<string> answers = response.answers;
                    var rnd = new Random();
                    var randomized = answers.OrderBy(item => rnd.Next());
                    answers = randomized.ToList();
                    this.Answer1B.Content = answers[0];
                    this.Answer2B.Content = answers[1];
                    this.Answer3B.Content = answers[2];
                    this.Answer4B.Content = answers[3];
                    this.Subject.Content += CurrentQuestion + "/" + NumOfQuestions;
                    this.ClickedButton = 0;
                });
                CurrentQuestion += 1;

                //Thread t = new Thread(new ThreadStart(Update_Timer));  // thread will update the timer each second
                //t.Start();

                // create a timer thread (changes timer) - CreateTimer() 
                // submit answer
                stopwatch.Start();  // starting to measure time 
                Thread.Sleep(Convert.ToInt32(this.TimePerQuestion) * 1000);
                //t.Abort();
                this.Dispatcher.Invoke(() =>
                {
                    Lock_All_Buttons(true);
                    Check_Answer(this.ClickedButton);
                });

                Thread.Sleep(2000);
                // reseting Window for next question
                this.Dispatcher.Invoke(() =>
                {
                    ResetButtons();
                    this.Subject.Content = "MagshiTrivia - Question ";
                });
                stopwatch.Reset();

                // create a timer thread (changes timer) - CreateTimer()
                // thread will call an ending function that will show correct answer & calculate points - Change_Buttons_Colors_TimesUp()
            }
            if(this.InGame)
            {
                this.Dispatcher.Invoke(() =>
                {
                    // TODO: show result as a MessageBox
                    // then after clicking OK return to the menu
                    byte[] fullMessage = Global.Communicator.getNoDataMessage(17);
                    Global.Communicator.sendMessage(fullMessage);
                    GetGameResultsResponse response = Global.Communicator.getGameResultsResponse(Global.Communicator.reciveResponse());

                    EndGame e = new EndGame(response.results, (int)TimePerQuestion);
                    e.Show();
                    this.Close();
                });
            }

        }

        private void Quit(object sender, RoutedEventArgs e)
        {
            // TODO: remove user from the game
            // special case if he is the only player
            InGame = false;
            byte[] fullMessage = Global.Communicator.getNoDataMessage(14);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();
            
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        /*
        private void Update_Timer()
        {
            uint currTime = this.TimePerQuestion;

            while (true)
            {
                this.Timer.Content = currTime;
                currTime--;
                Thread.Sleep(1000);
            }
        }*/

        private void Answer1B_Click(object sender, RoutedEventArgs e)
        {
            if (IsStateOK())
            {
                stopwatch.Stop();
                this.ClickedButton = 1;
                this.Answer1B.BorderThickness = new Thickness(1, 1, 1, 3);
                this.Answer1B.BorderBrush = Brushes.Black;
                Lock_All_Buttons(false);
                byte[] fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer1B.Content.ToString(), (uint)stopwatch.Elapsed.Seconds);
                Global.Communicator.sendMessage(fullMessage);
                GetSubmitAnswerResponse response = Global.Communicator.getSubmitAnswerResponse(Global.Communicator.reciveResponse());
                FindRightAnswer(response.rightAnswer);
            }
        }

        private void Answer2B_Click(object sender, RoutedEventArgs e)
        {
            if (IsStateOK())
            {
                stopwatch.Stop();
                this.ClickedButton = 2;
                this.Answer2B.BorderThickness = new Thickness(1, 1, 1, 3);
                this.Answer2B.BorderBrush = Brushes.Black;
                Lock_All_Buttons(false);
                byte[] fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer2B.Content.ToString(), (uint)stopwatch.Elapsed.Seconds);
                Global.Communicator.sendMessage(fullMessage);
                GetSubmitAnswerResponse response = Global.Communicator.getSubmitAnswerResponse(Global.Communicator.reciveResponse());
                FindRightAnswer(response.rightAnswer);
            }
        }

        private void Answer3B_Click(object sender, RoutedEventArgs e)
        {
            if (IsStateOK())
            {
                stopwatch.Stop();
                this.ClickedButton = 3;
                this.Answer3B.BorderThickness = new Thickness(1, 1, 1, 3);
                this.Answer3B.BorderBrush = Brushes.Black;
                Lock_All_Buttons(false);
                byte[] fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer3B.Content.ToString(), (uint)stopwatch.Elapsed.Seconds);
                Global.Communicator.sendMessage(fullMessage);
                GetSubmitAnswerResponse response = Global.Communicator.getSubmitAnswerResponse(Global.Communicator.reciveResponse());
                FindRightAnswer(response.rightAnswer);
            }
        }

        private void Answer4B_Click(object sender, RoutedEventArgs e)
        {
            if (IsStateOK())
            {
                stopwatch.Stop();
                this.ClickedButton = 4;
                this.Answer4B.BorderThickness = new Thickness(1, 1, 1, 3);
                this.Answer4B.BorderBrush = Brushes.Black;
                Lock_All_Buttons(false);
                byte[] fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer4B.Content.ToString(), (uint)stopwatch.Elapsed.Seconds);
                Global.Communicator.sendMessage(fullMessage);
                GetSubmitAnswerResponse response = Global.Communicator.getSubmitAnswerResponse(Global.Communicator.reciveResponse());
                FindRightAnswer(response.rightAnswer);
            }
        }
        private void FindRightAnswer(string rightAnswer)
        {
            if (this.Answer1B.Content.ToString().Equals(rightAnswer))
            {
                this.CorrectAnswer = 1;
            }
            if (this.Answer2B.Content.ToString().Equals(rightAnswer))
            {
                this.CorrectAnswer = 2;
            }
            if (this.Answer3B.Content.ToString().Equals(rightAnswer))
            {
                this.CorrectAnswer = 3;
            }
            if (this.Answer4B.Content.ToString().Equals(rightAnswer))
            {
                this.CorrectAnswer = 4;
            }
        }

        private void Lock_All_Buttons(bool eMode)
        {
            this.Answer1B.IsEnabled = eMode;
            this.Answer2B.IsEnabled = eMode;
            this.Answer3B.IsEnabled = eMode;
            this.Answer4B.IsEnabled = eMode;
        }

        private bool IsStateOK()
        {
            return (this.Answer1B.Background == Brushes.Beige && this.Answer2B.Background == Brushes.Beige && this.Answer3B.Background == Brushes.Beige && this.Answer4B.Background == Brushes.Beige);
        }

        private void Choose_Random_Answer()
        {
            Random rnd = new Random();
            int answer = rnd.Next(1,5);
            this.ClickedButton = answer;
            byte[] fullMessage = { };
            switch (answer)
            {
                case 1:
                    fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer1B.Content.ToString(), this.TimePerQuestion);
                    break;
                case 2:
                    fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer2B.Content.ToString(), this.TimePerQuestion);
                    break;
                case 3:
                    fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer3B.Content.ToString(), this.TimePerQuestion);
                    break;
                case 4:
                    fullMessage = Global.Communicator.getSubmitAnswerMessage(this.Answer4B.Content.ToString(), this.TimePerQuestion);
                    break;
            }
            Global.Communicator.sendMessage(fullMessage);
            GetSubmitAnswerResponse response = Global.Communicator.getSubmitAnswerResponse(Global.Communicator.reciveResponse());
            FindRightAnswer(response.rightAnswer);
        }

        private void Check_Answer(int button)
        {
            if (button == 0)  // times up
            {
                Choose_Random_Answer();
                Change_Buttons_Colors_TimesUp();
            }
            else if (button == this.CorrectAnswer)  // correct answer
            {
                Change_Buttons_Colors_Right();
                // TODO: calculate points & add to score
            }
            else  // wrong answer
            {
                Change_Buttons_Colors_Wrong(button);
            }
        }

        private void Change_Buttons_Colors_Right()
        {
            this.Answers[this.CorrectAnswer - 1].Background = Brushes.Green;
        }

        private void Change_Buttons_Colors_Wrong(int selectedAnswer)
        {
            this.Answers[selectedAnswer - 1].Background = Brushes.Red;
            this.Answers[this.CorrectAnswer - 1].Background = Brushes.Green;
        }

        private void Change_Buttons_Colors_TimesUp()
        {
            for (int i = 0; i < this.Answers.Length; i++)
            {
                if (i == (this.CorrectAnswer - 1))
                {
                    this.Answers[i].Background = Brushes.Green;
                }
                else
                {
                    this.Answers[i].Background = Brushes.Red;
                }
            }
        }

        private void ResetButtons()
        {
            this.Answer1B.Background = Brushes.Beige;
            this.Answer1B.BorderThickness = new Thickness(1, 1, 1, 1);

            this.Answer2B.Background = Brushes.Beige;
            this.Answer2B.BorderThickness = new Thickness(1, 1, 1, 1);

            this.Answer3B.Background = Brushes.Beige;
            this.Answer3B.BorderThickness = new Thickness(1, 1, 1, 1);

            this.Answer4B.Background = Brushes.Beige;
            this.Answer4B.BorderThickness = new Thickness(1, 1, 1, 1);
        }
    }
}
