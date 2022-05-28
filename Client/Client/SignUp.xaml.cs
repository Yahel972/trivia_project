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

namespace Client
{   
    public class SignUpMessage
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
    }
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
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 6969);
            client.Connect(serverEndPoint);
            NetworkStream clientStream = client.GetStream();
            // TODO: add a new user to the dataBase
            var signup = new SignUpMessage
            {
                username = "Yahel",
                password = "Bareket",
                email = "yahel.bareket@gmail.com"
            };
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, signup);
            }
            byte[] thirdPart = ms.ToArray();
            int len = thirdPart.Length;
            byte[] firstPart = new byte[5];
            firstPart[0] = BitConverter.GetBytes(1)[0];
            firstPart[1] = (byte)(len >> 24);
            firstPart[2] = (byte)(len >> 16);
            firstPart[3] = (byte)(len >> 8);
            firstPart[4] = (byte)(len);
            byte[] buffer = firstPart.Concat(thirdPart).ToArray();
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();

        }
    }
}
