using System;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Text;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace Json
{
    public class Author
    {
        public int id { get; set; }
        public string Name { get; set; }
        public string born { get; set; }
        public string died { get; set; }
        public string title { get; set; }
        public string type { get; set; }
        public int year { get; set; }

        public override string ToString()
        {
            return("ID: " + id.ToString() + "\n" + "Имя: " + Name.ToString() + "\n" + "Дата рождения: " + born.ToString() + "\n"  
                + "Дата смерти: " + died.ToString() + "\n" + "Название произведения: " + title.ToString() + "\n" 
                + "Тип произведения :"+ type.ToString() + "\n" + "Год издания: " + year.ToString() + "\n");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var jsonString = File.ReadAllText("data.json");
            
            if(jsonString.Length > 0)
            {
                var authors = JsonConvert.DeserializeObject<List<Author>>(jsonString);

                foreach (var author in authors)
                {
                    Console.WriteLine(author.ToString());
                }
            }
        }
    }
}
