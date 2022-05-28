﻿using System;
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

namespace Client
{   
    public partial class SignUp : Window
    {
        public SignUp()
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
            byte[] fullMessage = Global.communicator.getSignupMessage("or", "pini123", "or.pini@gmail.com"); // TODO: get the paremeters
            Global.communicator.sendMessage(fullMessage);
        }
    }
}
