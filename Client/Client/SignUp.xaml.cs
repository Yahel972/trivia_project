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
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Window
    {
        public SignUp()
        {
            InitializeComponent();
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void Check_Validation_And_Sign_Up(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(_username.Text))
                MessageBox.Show("Invalid Name Given", "INVALID NAME", MessageBoxButton.OK, MessageBoxImage.Error);
            else if (_password.Text.Length < 4)
                MessageBox.Show("Invalid Password Given", "INVALID PASSWORD", MessageBoxButton.OK, MessageBoxImage.Error);
            else if (string.IsNullOrWhiteSpace(_email.Text))
                MessageBox.Show("Invalid Mail Given", "INVALID MAIL", MessageBoxButton.OK, MessageBoxImage.Error);
            else  // all parameters are valid
                Add_New_User();
        }

        private void Add_New_User()
        {
            // TODO: add a new user to the dataBase


        }
    }
}
