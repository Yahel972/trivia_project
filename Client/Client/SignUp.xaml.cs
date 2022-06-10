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
using System.Net.Sockets;
using System.Net;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Bson;
using System.Text.RegularExpressions;

namespace Client
{   
    public partial class SignUp : Window
    {
        public SignUp()
        {
            InitializeComponent();
            this.LoggedInUser.Content = Global.LoggedInName;
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void Check_Validation_And_Sign_Up(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(this._username.Text))
            {
                MessageBox.Show("Invalid Name Given", "INVALID NAME", MessageBoxButton.OK, MessageBoxImage.Error);
                this._username.Clear();
            }
            else if (this._password.Text.Length < 4)
            {
                MessageBox.Show("Invalid Password Given (At Least 4 Letters Required)", "INVALID PASSWORD", MessageBoxButton.OK, MessageBoxImage.Error);
                this._password.Clear();
            }
            else if (string.IsNullOrWhiteSpace(this._email.Text))
            {
                MessageBox.Show("Invalid Mail Given", "INVALID MAIL", MessageBoxButton.OK, MessageBoxImage.Error);
                this._email.Clear();
            }
            else  // all parameters are valid
                Add_New_User();
        }

        private void Add_New_User()
        {
            // sending sign-up request to server and getting its response:
            byte[] fullMessage = Global.Communicator.getSignupMessage(this._username.Text, this._password.Text, this._email.Text);
            Global.Communicator.sendMessage(fullMessage);
            OnlyStatusResponse response = Global.Communicator.getGeneralResponse(Global.Communicator.reciveResponse());

            if (response.status == 0)  // user already exists
            {
                MessageBox.Show("Username Already Exists", "INVALID USERNAME", MessageBoxButton.OK, MessageBoxImage.Error);
                this._username.Clear();
            }
            else  // valid request
            {
                Back_To_Menu(null, null);
            }
        }
        public static int CheckStrength(string password)
        {
            int score = 0;

            if (password.Length < 1)
                return 0;
            if (password.Length < 4)
                return 1;

            if (password.Length >= 4)
                score++;
            if (password.Length >= 8)
                score++;
            if (Regex.IsMatch(password, @"[a-z]"))
                score++;
            if (Regex.IsMatch(password, @"[0-9]"))
                score++;

            if (Regex.IsMatch(password, @"[A-Z]"))
                score++;

            return score;
        }


        private void textChangedEventHandler(object sender, TextChangedEventArgs e)
        {

            string password = _password.Text;
            int howStrong = CheckStrength(password);
            if(howStrong == 0)
            {
                Howstrongpassword1.Visibility = Visibility.Hidden;
                Howstrongpassword2.Visibility = Visibility.Hidden;
            }
            if (howStrong <= 2)
            {
                Howstrongpassword1.Visibility = Visibility.Visible;
                Howstrongpassword2.Visibility = Visibility.Visible;
                Howstrongpassword1.Fill = new SolidColorBrush(Color.FromRgb(255, 51, 51));
                Howstrongpassword2.Content = "Weak";
            }
            else if (howStrong <= 3)
            {
                Howstrongpassword1.Visibility = Visibility.Visible;
                Howstrongpassword2.Visibility = Visibility.Visible;
                Howstrongpassword1.Fill = new SolidColorBrush(Color.FromRgb(255, 153, 51));
                Howstrongpassword2.Content = "Medium";
            }

            else if (howStrong <= 5)
            {
                Howstrongpassword1.Visibility = Visibility.Visible;
                Howstrongpassword2.Visibility = Visibility.Visible;
                Howstrongpassword1.Fill = new SolidColorBrush(Color.FromRgb(51, 255, 51));
                Howstrongpassword2.Content = "Strong";
            }
        }
    }
}
