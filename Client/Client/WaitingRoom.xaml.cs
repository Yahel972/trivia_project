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

namespace Client
{
    /// <summary>
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    public partial class WaitingRoom : Window
    {
        public string roomName;
        public bool isAdmin;

        public WaitingRoom(string Room_Name, bool Is_Admin)
        {
            roomName = Room_Name;
            isAdmin = Is_Admin;
            InitializeComponent();

            Check_Buttons(isAdmin);
            findAllConnectedUsers();

            this.connectedRoom.Content = "You are connected to room: \"" + roomName + "\"";
            this.LoggedInUser.Content = Global.loggedInName;
        }

        private void Check_Buttons(bool isAdmin)
        {
            if (isAdmin)
            {
                this.CloseRoomB.Visibility = Visibility.Visible;
                this.StartGameB.Visibility = Visibility.Visible;
                this.LeaveRoomB.Visibility = Visibility.Hidden;
            }
            else
            {
                this.CloseRoomB.Visibility = Visibility.Hidden;
                this.StartGameB.Visibility = Visibility.Hidden;
                this.LeaveRoomB.Visibility = Visibility.Visible;
            }
        }

        private void findAllConnectedUsers()
        {
            // TODO: find all the users who are connected to the game and add them to the listBox
        }

        private void CloseRoomB_Click(object sender, RoutedEventArgs e)
        {
            // TODO: close game for all users (loop through listBox)

            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void LeaveRoomB_Click(object sender, RoutedEventArgs e)
        {
            // TODO: remove user from the other user's listBox

            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void StartGameB_Click(object sender, RoutedEventArgs e)
        {
            // TODO: start game for all users (loop through listBox)
        }
    }
}
