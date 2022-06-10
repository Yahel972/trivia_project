﻿using System;
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

        public int ClickedButton;

        public Question(uint time_per_question, uint num_of_questions, uint current_question = 1)
        {
            TimePerQuestion = time_per_question;
            NumOfQuestions = num_of_questions;
            CurrentQuestion = current_question;
            this.CorrectAnswer = 2;  // TODO UPDATE THAT AFTER ROLLING QUESTION
            this.ClickedButton = 0;  // no button clicked yet

            InitializeComponent();
            Answers = new[] { this.Answer1B, this.Answer2B, this.Answer3B, this.Answer4B };

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

                this.Dispatcher.Invoke(() =>
                {
                    this.QuestionContent.Content = response.question;
                    this.Answer1B.Content = response.answers[0];
                    this.Answer2B.Content = response.answers[1];
                    this.Answer3B.Content = response.answers[2];
                    this.Answer4B.Content = response.answers[3];
                    this.Subject.Content += CurrentQuestion + "/" + NumOfQuestions;
                    this.ClickedButton = 0;
                });
                CurrentQuestion += 1;

                // create a timer thread (changes timer) - CreateTimer() 
                // submit answer
                //}

                Thread.Sleep(Convert.ToInt32(this.TimePerQuestion) * 1000);

                this.Dispatcher.Invoke(() =>
                {
                    Lock_All_Buttons(true);
                    Check_Answer(this.ClickedButton);
                });

                Thread.Sleep(2000);

                this.Dispatcher.Invoke(() =>
                {
                    ResetButtons();
                    this.Subject.Content = "MagshiTrivia - Question ";
                });

                // create a timer thread (changes timer) - CreateTimer()
                // thread will call an ending function that will show correct answer & calculate points - Change_Buttons_Colors_TimesUp()
            }
            this.Dispatcher.Invoke(() =>
            {
                // TODO: show result as a MessageBox
                // then after clicking OK return to the menu

                Menu m = new Menu();
                m.Show();
                this.Close();
            });
        }

        private void Quit(object sender, RoutedEventArgs e)
        {
            // TODO: remove user from the game
            // special case if he is the only player
            // or if there are 2 players (other player will be the winner)
        }

        private void CreateTimer()
        {
            // TODO: create a timer (use TimePerQuestion variable)
        }

        private void Answer1B_Click(object sender, RoutedEventArgs e)
        {
            this.ClickedButton = 1;
            this.Answer1B.BorderThickness = new Thickness(1, 1, 1, 3);
            this.Answer1B.BorderBrush = Brushes.Black;
            Lock_All_Buttons(false);
        }

        private void Answer2B_Click(object sender, RoutedEventArgs e)
        {
            this.ClickedButton = 2;
            this.Answer2B.BorderThickness = new Thickness(1, 1, 1, 3);
            this.Answer2B.BorderBrush = Brushes.Black;
            Lock_All_Buttons(false);
        }

        private void Answer3B_Click(object sender, RoutedEventArgs e)
        {
            this.ClickedButton = 3;
            this.Answer3B.BorderThickness = new Thickness(1, 1, 1, 3);
            this.Answer3B.BorderBrush = Brushes.Black;
            Lock_All_Buttons(false);
        }

        private void Answer4B_Click(object sender, RoutedEventArgs e)
        {
            this.ClickedButton = 4;
            this.Answer4B.BorderThickness = new Thickness(1, 1, 1, 3);
            this.Answer4B.BorderBrush = Brushes.Black;
            Lock_All_Buttons(false);
        }

        private void Lock_All_Buttons(bool eMode)
        {
            this.Answer1B.IsEnabled = eMode;
            this.Answer2B.IsEnabled = eMode;
            this.Answer3B.IsEnabled = eMode;
            this.Answer4B.IsEnabled = eMode;
        }

        private void Check_Answer(int button)
        {
            if (button == 0)  // times up
            {
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
