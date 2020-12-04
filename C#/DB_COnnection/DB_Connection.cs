using System;
using System.Data;
using System.Data.OleDb;
namespace DB_Connection
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Подключаемся к базе данных онлайн-магазина:");
            OleDbConnection OnlineShop = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;data source =" +
                                                             "online_shop1.mdb");
            OnlineShop.Open();
            var CourierTable = new DataTable();
            var CustomerTable = new DataTable();
            
            OleDbDataAdapter adapter = new OleDbDataAdapter("select * FROM Курьер", OnlineShop);
            adapter.Fill(CourierTable);
   
            adapter = new OleDbDataAdapter("select * FROM Курьер", OnlineShop);
            adapter.Fill(CourierTable);
            Console.WriteLine(CourierTable.TableName);
            foreach (var column in CourierTable.Columns)
            {
                Console.Write(column.ToString() + "\t");
            }
            Console.WriteLine("\n*************************************************");
            foreach (DataRow row in CourierTable.Rows)
            {
                var cells = row.ItemArray;
                foreach (var cell in cells)
                {
                    Console.Write(cell.ToString() + "\t");
                }
                Console.WriteLine("\n*************************************************");
            }

            Console.WriteLine("Введите данные нового курьера:");
            string name;
            string contacts;
            int code;
            
            Console.Write("Фамилия, Имя, Отчество: ");
            name = Console.ReadLine();
            Console.Write("Адрес электронной почты: ");
            contacts = Console.ReadLine();
            Console.Write("Личный код курьера: ");
            code = int.Parse(Console.ReadLine());
            OleDbCommand add_courier = new OleDbCommand("INSERT INTO [Курьер] VALUES(@ФИО, @КОНТАКТ, @КОДКУРЬЕРА)", OnlineShop);
            add_courier.Parameters.AddWithValue("@ФИО", name);
            add_courier.Parameters.AddWithValue("@КОНТАКТ", contacts);
            add_courier.Parameters.AddWithValue("@КОДКУРЬЕРА", code);
            
            
            add_courier.ExecuteNonQuery();
           
            adapter = new OleDbDataAdapter("select * FROM Курьер", OnlineShop);
            adapter.Fill(CourierTable);
            foreach (var column in CourierTable.Columns)
            {
                Console.Write(column.ToString() + "\t");
            }
            Console.WriteLine("\n*************************************************");
            foreach (DataRow row in CourierTable.Rows)
            {
                var cells = row.ItemArray;
                foreach (var cell in cells)
                {
                    Console.Write(cell.ToString() + "\t");
                }
                Console.WriteLine("\n*************************************************");
            }
            Console.WriteLine("Нажмите Enter, чтобы продолжить");
            Console.ReadLine();
            
            ///////////////////////////////////////////////////////////////////////////////////////
            
            adapter = new OleDbDataAdapter("select * FROM Клиент", OnlineShop);
            adapter.Fill(CustomerTable);
            Console.WriteLine(CustomerTable.TableName);
            foreach (var column in CustomerTable.Columns)
            {
                Console.Write(column.ToString() + "\t");
            }
            Console.WriteLine("\n*************************************************");
            foreach (DataRow row in CustomerTable.Rows)
            {
                var cells = row.ItemArray;
                foreach (var cell in cells)
                {
                    Console.Write(cell.ToString() + "\t");
                }
                Console.WriteLine("\n*************************************************");
            }

            Console.WriteLine("Введите данные нового клиента.");
            
            string adress;
            
            Console.Write("Фамилия, Имя, Отчество: ");
            name = Console.ReadLine();
            Console.Write("Адрес электронной почты: ");
            contacts = Console.ReadLine();
            Console.Write("Адрес: ");
            adress = Console.ReadLine();
            Console.Write("Личный код клиента:");
            code = int.Parse(Console.ReadLine());
            
            OleDbCommand add_client = new OleDbCommand("INSERT INTO [Клиент] VALUES(@КОДКЛИЕНТА, @НАИМЕНОВАНИЕ, @АДРЕС, @КОНТАКТ)", OnlineShop);
            add_client.Parameters.AddWithValue("@КОДКЛИЕНТА", code);
            add_client.Parameters.AddWithValue("@КОНТАКТ", contacts);
            add_client.Parameters.AddWithValue("@Адрес", adress);
            add_client.Parameters.AddWithValue("@Наименование", name);
            add_client.ExecuteNonQuery();
            
            adapter = new OleDbDataAdapter("select * FROM Клиент", OnlineShop);
            adapter.Fill(CustomerTable);
            Console.WriteLine(CustomerTable.TableName);
            foreach (var column in CustomerTable.Columns)
            {
                Console.Write(column.ToString() + "\t");
            }
            Console.WriteLine("\n*************************************************");
            foreach (DataRow row in CustomerTable.Rows)
            {
                var cells = row.ItemArray;
                foreach (var cell in cells)
                {
                    Console.Write(cell.ToString() + "\t");
                }
                Console.WriteLine("\n*************************************************");
            }
            OnlineShop.Close();
        }
    }
}