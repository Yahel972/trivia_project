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
    public partial class Login : Window
    {
        public Login()
        {
            InitializeComponent();
            this.LoggedInUser.Content = Global.loggedInName;
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void Check_Validation_And_Log_In(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(this._username.Text))  // invalid username length
            {
                MessageBox.Show("Invalid Name Given", "INVALID NAME", MessageBoxButton.OK, MessageBoxImage.Error);
                this._username.Clear();
            }
            else if (this._password.Text.Length < 4)  // invalid password length
            {
                MessageBox.Show("Password's Length Must be at least 4 Letters", "INVALID PASSWORD", MessageBoxButton.OK, MessageBoxImage.Error);
                this._password.Clear();
            }
            else
                Log_In();
        }

        private void Log_In()
        {
            // sending login request to server and getting its response:
            byte[] message = Global.communicator.getLoginMessage(this._username.Text, this._password.Text);
            Global.communicator.sendMessage(message);
            OnlyStatusResponse response = Global.communicator.getGeneralResponse(Global.communicator.reciveResponse());

            if(response.status == 2)  // username does not exists
            {
                MessageBox.Show("Username doesn't exits", "INVALID USERNAME", MessageBoxButton.OK, MessageBoxImage.Error);
                this._username.Clear();
                this._password.Clear();
            }
            else if (response.status == 3)  // password does not matches username
            {
                MessageBox.Show("Password doesn't match the given username", "INVALID PASSWORD", MessageBoxButton.OK, MessageBoxImage.Error);
                this._password.Clear();
            }
            else if (response.status == 4)  // user is already connected
            {
                MessageBox.Show("User is Already Connected", "USER ALREADY CONNECTED", MessageBoxButton.OK, MessageBoxImage.Error);
                this._username.Clear();
                this._password.Clear();
            }
            else  // valid request
            {
                Global.isLoggedIn = true;
                Global.loggedInName = this._username.Text;
                Back_To_Menu(null, null);
            }
        }
    }
}
