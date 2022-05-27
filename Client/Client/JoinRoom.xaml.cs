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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        

        public JoinRoom()
        {
            InitializeComponent();
            ShowAllRooms();
            this.LoggedInUser.Content = Global.loggedInName;
        }

        private void Back_To_Menu(object sender, RoutedEventArgs e)
        {
            Menu m = new Menu();
            m.Show();
            this.Close();
        }

        private void ShowAllRooms()
        {
            // TODO: push all rooms from given vector to the listBox
            /*
            for (int i = 0; i < 10000; i++)
            {
                string dataToAdd = Vector[i].name + " - " + Vector[i].id;
                this.RoomsList.Items.Add(dataToAdd); 
            }*/
        }

        private void Join_Room(object sender, RoutedEventArgs e)
        {
            // TODO - join room
        }

        private void Refresh_Page(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < 10; i++)
            {
                this.RoomsList.Items.Add("or");
            }

            // TODO - refresh the page
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
