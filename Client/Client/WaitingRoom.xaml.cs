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
using System.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    public partial class WaitingRoom : Window
    {
        public string roomName;
        public bool isAdmin;
        public uint roomId;
        public bool inWaitingRoom;
        public bool userExitedRoom;
        public bool hasGameBegun;
        public uint timeToAnswer;
        public uint numOfQuestions;

        public WaitingRoom(string Room_Name, bool Is_Admin, uint Room_Id)
        {
            roomName = Room_Name;
            isAdmin = Is_Admin;
            roomId = Room_Id;
            this.userExitedRoom = false;
            this.hasGameBegun = false;
            this.inWaitingRoom = true;
            InitializeComponent();

            // check status
            Thread t = new Thread(new ThreadStart(Refresh_Waiting_Room));
            t.SetApartmentState(ApartmentState.STA);
            Check_Buttons(isAdmin);
            findAllConnectedUsers();

            this.connectedRoom.Content = "You are connected to room: \"" + roomName + "\"";
            this.LoggedInUser.Content = Global.LoggedInName;
            t.Start();
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
            this.userExitedRoom = true;
            byte[] fullMessage = Global.Communicator.getNoDataMessage(10);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();
        }

        private void LeaveRoomB_Click(object sender, RoutedEventArgs e)
        {
            // TODO: remove user from the other user's listBox
            this.userExitedRoom = true;
        }

        private void StartGameB_Click(object sender, RoutedEventArgs e)
        {
            // TODO: start game for all users (loop through listBox)
            this.hasGameBegun = true;
        }

        private void Refresh_Waiting_Room()
        {
            while (!this.userExitedRoom && !this.hasGameBegun)   
            {
                this.userExitedRoom = true;
                byte[] fullMessage = Global.Communicator.getNoDataMessage(12);
                Global.Communicator.sendMessage(fullMessage);
                byte[] response = Global.Communicator.reciveResponse();
                GetRoomStatusResponse getRoomStatusResponse = Global.Communicator.getRoomStatusResponse(response);
                timeToAnswer = getRoomStatusResponse.answerTimeout;
                numOfQuestions = getRoomStatusResponse.questionCount;
                this.hasGameBegun = getRoomStatusResponse.hasGameBegun;
                List<string> players = getRoomStatusResponse.players;
                this.Dispatcher.Invoke(() =>
                {
                    this.connectedUsers.Items.Clear();
                    for (int i = 0; i < players.Count(); i++)
                    {
                        if (Global.LoggedInName.Equals(players[i]))
                        {
                            this.userExitedRoom = false;
                        }
                        this.connectedUsers.Items.Add(players[i]);
                    }
                });
                Thread.Sleep(3000);
            }
            this.Dispatcher.Invoke(() =>
            {
                if (this.hasGameBegun)
                {
                    // create question game (pass paremeters: questionCount and answerTimeout
                    // questionGame.Show()
                    byte[] fullMessage = Global.Communicator.getNoDataMessage(11);
                    Global.Communicator.sendMessage(fullMessage);
                    Global.Communicator.reciveResponse();
                    Question q = new Question(timeToAnswer, numOfQuestions);
                    q.Show();
                    this.Close();
                }
                if(this.userExitedRoom)
                {
                    byte[] fullMessage = Global.Communicator.getNoDataMessage(13);
                    Global.Communicator.sendMessage(fullMessage);
                    Global.Communicator.reciveResponse();
                    var m = new Menu();
                    m.Show();
                    this.Close();
                }
            });
        }
    }
}
