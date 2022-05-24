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
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void Check_Validation_And_Log_In(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(this._username.Text) || isNameRegistered(this._username.Text))
                MessageBox.Show("Invalid Name Given", "INVALID NAME", MessageBoxButton.OK, MessageBoxImage.Error);
            else if (this._password.Text.Length < 4 || isPasswordMatches(this._username.Text, this._password.Text))
                MessageBox.Show("Password doesn't match the given username", "INVALID PASSWORD", MessageBoxButton.OK, MessageBoxImage.Error);
            else
            {

            }
        }

        private bool isNameRegistered(string username)
        {
            // TODO: Return if the user is registered in the data-base

            return false;
        }

        private bool isPasswordMatches(string username, string password)
        {
            // TODO: Return if the given password matches the given name

            return false;
        }
    }
}
