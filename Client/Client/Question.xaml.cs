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

namespace Client
{
    public partial class Question : Window
    {
        public uint TimePerQuestion;
        public uint NumOfQuestions;
        public uint CurrentQuestion;

        public Button[] Answers;
        public int CorrectAnswer;

        public Question(uint time_per_question, uint num_of_questions, uint current_question = 1)
        {
            TimePerQuestion = time_per_question;
            NumOfQuestions = num_of_questions;
            CurrentQuestion = current_question;

            InitializeComponent();
            Thread t = new Thread(new ThreadStart(Game));
            t.Start();
        }

        private void Game()
        {
            for (int i = 0; i < NumOfQuestions; i++)
            {
                byte[] fullMessage = Global.Communicator.getNoDataMessage(15);
                Global.Communicator.sendMessage(fullMessage);
                GetQuestionResponse response = Global.Communicator.getQuestionResponse(Global.Communicator.reciveResponse());
                response.
                this.Dispatcher.Invoke(() =>
                {
                    this.QuestionContent.Content = response.question;
                    this.Answer1B.Content = response.answers[0];
                    this.Answer2B.Content = response.answers[1];
                    this.Answer3B.Content = response.answers[2];
                    this.Answer4B.Content = response.answers[3];
                    this.Subject.Content += CurrentQuestion + "/" + NumOfQuestions;
                });
                CurrentQuestion += 1;
                Answers = new[] { this.Answer1B, this.Answer2B, this.Answer3B, this.Answer4B };
                // create a timer thread (changes timer) - CreateTimer() 
                // submit answer
                //}

                // recieve result
                RollQuestion();

                Thread.Sleep(3000);

                // create a timer thread (changes timer) - CreateTimer()
                // thread will call an ending function that will show correct answer & calculate points - Change_Buttons_Colors_TimesUp()

            }
            this.Dispatcher.Invoke(() =>
            {
                this.Close();
            });
        }

        private void Quit(object sender, RoutedEventArgs e)
        {
            // TODO: remove user from the game
            // special case if he is the only player
            // or if there are 2 players (other player will be the winner)
        }

        private void RollQuestion()
        {
            // TODO: roll a question from the DB
            // update question content, correct answer & buttons contents
            this.CorrectAnswer = 2;  // delete this line after, using it for now cause it is easier
        }

        private void CreateTimer()
        {
            // TODO: create a timer (use TimePerQuestion variable)
        }

        private void Answer1B_Click(object sender, RoutedEventArgs e)
        {
            // user chose answer 1
            if (this.CorrectAnswer == 1)  // correct ans
            {
                Change_Buttons_Colors_Right();
                // update scores
            }
            else  // wrong ans
            {
                Change_Buttons_Colors_Wrong(1);
            }

            // Wait 2 sec
        }

        private void Answer2B_Click(object sender, RoutedEventArgs e)
        {
            // user chose answer 2
            if (this.CorrectAnswer == 2)  // correct ans
            {
                Change_Buttons_Colors_Right();
                // update scores
            }
            else  // wrong ans
            {
                Change_Buttons_Colors_Wrong(2);
            }

            // Wait 2 sec
        }

        private void Answer3B_Click(object sender, RoutedEventArgs e)
        {
            // user chose answer 3
            if (this.CorrectAnswer == 3)  // correct ans
            {
                Change_Buttons_Colors_Right();
                // update scores
            }
            else  // wrong ans
            {
                Change_Buttons_Colors_Wrong(3);
            }

            // Wait 2 sec
        }

        private void Answer4B_Click(object sender, RoutedEventArgs e)
        {
            // user chose answer 4
            if (this.CorrectAnswer == 4)  // correct ans
            {
                Change_Buttons_Colors_Right();
                // update scores
            }
            else  // wrong ans
            {
                Change_Buttons_Colors_Wrong(4);
            }
            
            // Wait 2 sec
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

        private void Change_Buttons_Colors_TimesUp(int selectedAnswer)
        {
            for (int i = 0; i < this.Answers.Length; i++)
            {
                if (i == (selectedAnswer - 1))
                {
                    this.Answers[i].Background = Brushes.Green;
                }
                else
                {
                    this.Answers[i].Background = Brushes.Red;
                }
            }
        }
    }
}
