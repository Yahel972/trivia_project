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
using System.Text.RegularExpressions;

namespace Client
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public CreateRoom()
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

        private void Check_Validation_And_Create_Room(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(this._roomName.Text) || this._roomName.Text.Contains("-"))
            {
                MessageBox.Show("Invalid Room Name Given", "INVALID ROOM NAME", MessageBoxButton.OK, MessageBoxImage.Error);
                this._roomName.Clear();
            }
            else if (IsRoomNameTaken(this._roomName.Text))
            {
                MessageBox.Show("Room Name Given is Already Taken", "INVALID ROOM NAME", MessageBoxButton.OK, MessageBoxImage.Error);
                this._roomName.Clear();
            }
            else if (this._numOfPlayers.Text == "0" || this._numOfPlayers.Text == "")
            {
                MessageBox.Show("Amount Of Players must be Bigger than 0", "INVALID AMOUNT OF PLAYERS", MessageBoxButton.OK, MessageBoxImage.Error);
                this._numOfPlayers.Clear();
            }
            else if (Convert.ToInt32(this._numOfQuestions.Text) > 10)
            {
                MessageBox.Show("Maximum Amount Of Questions is 10", "INVALID AMOUNT OF QUESTIONS", MessageBoxButton.OK, MessageBoxImage.Error);
                this._numOfQuestions.Clear();
            }
            else if (this._numOfQuestions.Text == "0" || this._numOfQuestions.Text == "")
            {
                MessageBox.Show("Amount Of Questions must be Bigger than 0", "INVALID AMOUNT OF QUESTIONS", MessageBoxButton.OK, MessageBoxImage.Error);
                this._numOfQuestions.Clear();
            }
            else if (this._timePerQuestion.Text == "0" || this._timePerQuestion.Text == "")
            {
                MessageBox.Show("Time per Question must be Bigger than 0", "INVALID TIME PER QUESTION", MessageBoxButton.OK, MessageBoxImage.Error);
                this._timePerQuestion.Clear();
            }
            else
                Create_Room();
        }

        private bool IsRoomNameTaken(string roomName)
        {
            byte[] roomsMsg = Global.Communicator.getNoDataMessage(6);
            Global.Communicator.sendMessage(roomsMsg);
            byte[] rooms = Global.Communicator.reciveResponse();
            GetRoomsResponse response = Global.Communicator.getRoomsResponse(rooms);

            for (int i = 0; i < response.Rooms.Count(); i++)
            {
                if (response.Rooms[i].name == this._roomName.Text)
                {
                    return true;
                }
            }

            return false;
        }

        /** function filters only numbers in a text box input */
        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }

        private void Create_Room()
        {
            // creating room
            byte[] fullMessage = Global.Communicator.getCreateRoomMessage(this._roomName.Text, Convert.ToUInt32(this._numOfPlayers.Text), Convert.ToUInt32(this._timePerQuestion.Text), Convert.ToUInt32(this._numOfQuestions.Text));
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();

            // getting room's id
            uint roomId = 0;
            byte[] roomsMsg = Global.Communicator.getNoDataMessage(6);
            Global.Communicator.sendMessage(roomsMsg);
            byte[] rooms = Global.Communicator.reciveResponse();
            GetRoomsResponse response = Global.Communicator.getRoomsResponse(rooms);
            for(int i = 0; i < response.Rooms.Count(); i++)
            {
                if (response.Rooms[i].name == this._roomName.Text)
                {
                    roomId = response.Rooms[i].id;
                    break;
                }
            }

            // openning waiting room
            WaitingRoom wr = new WaitingRoom(this._roomName.Text, true, roomId);
            wr.Show();
            this.Close();
        }
    }
}
