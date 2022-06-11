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
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {

        public bool inJoinRoomScreen;
        public JoinRoom()
        {
            InitializeComponent();
            Thread t = new Thread(new ThreadStart(Refresh_Page));

            //this.Refresh_Page(null, null);
            this.LoggedInUser.Content = Global.LoggedInName;
            this.inJoinRoomScreen = true;
            t.Start();
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            this.inJoinRoomScreen = false;
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void Check_Validation_And_Join_Room(object sender, RoutedEventArgs e)
        {
            // TODO - check if room is full.
            uint roomId = Convert.ToUInt32(this.RoomsList.SelectedItem.ToString().Substring(this.RoomsList.SelectedItem.ToString().LastIndexOf(" - ") + 3));
            uint maxPlayers = 0;

            byte[] getPlayersMessage = Global.Communicator.getPlayersInRoomMessage(roomId);
            Global.Communicator.sendMessage(getPlayersMessage);
            byte[] players = Global.Communicator.reciveResponse();
            GetPlayersInRoomResponse getPlayersResponse = Global.Communicator.getPlayersInRoomResponse(players);
            uint currentPlayers = (uint)getPlayersResponse.players.Count;

            // getting all rooms and searching the room with the wanted ID
            byte[] fullMessage = Global.Communicator.getNoDataMessage(6);
            Global.Communicator.sendMessage(fullMessage);
            byte[] rooms = Global.Communicator.reciveResponse();
            GetRoomsResponse response = Global.Communicator.getRoomsResponse(rooms);
            for (int i = 0; i < response.Rooms.Count(); i++)
            {
                if (response.Rooms[i].id == roomId)
                {
                    maxPlayers = response.Rooms[i].maxPlayers;
                    break;
                }
            }

            if (currentPlayers < maxPlayers)  // checking if the given room is full
            {
                Join_Room(sender, e);
            }
            else
            {
                MessageBox.Show("Can't Join Room (Maximum " + maxPlayers + " Players)", "ROOM IS FULL", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Join_Room(object sender, RoutedEventArgs e)
        {
            this.inJoinRoomScreen = false;
            uint roomId = Convert.ToUInt32(this.RoomsList.SelectedItem.ToString().Substring(this.RoomsList.SelectedItem.ToString().LastIndexOf(" - ") + 3));
            
            byte[] fullMessage = Global.Communicator.getJoinRoomMessage(roomId);
            Global.Communicator.sendMessage(fullMessage);
            Global.Communicator.reciveResponse();

            WaitingRoom wr = new WaitingRoom(this.RoomsList.SelectedItem.ToString().Substring(0, this.RoomsList.SelectedItem.ToString().LastIndexOf(" - ")), false, roomId);
            wr.Show();
            this.Close();
        }

        private void Refresh_Page()
        {
            while(this.inJoinRoomScreen)
            {
                this.Dispatcher.Invoke(() =>
                {
                    this.RoomsList.Items.Clear();
                });
                byte[] fullMessage = Global.Communicator.getNoDataMessage(6);
                Global.Communicator.sendMessage(fullMessage);
                byte[] rooms = Global.Communicator.reciveResponse();
                GetRoomsResponse response = Global.Communicator.getRoomsResponse(rooms);
                for (int i = 0; i < response.Rooms.Count(); i++)
                {
                    this.Dispatcher.Invoke(() =>
                    {
                        this.RoomsList.Items.Add(response.Rooms[i].name + " - " + response.Rooms[i].id);
                    });
                }
                Thread.Sleep(3000);
            }

        }

        private void Check_Choosing_Room(object sender, SelectionChangedEventArgs e)
        {
            if (this.RoomsList.SelectedIndex >= 0)
            {
                this.JoinB.IsEnabled = true;
            }
            else
            {
                this.JoinB.IsEnabled = false;
            }
        }        
    }
}
