using System;
using System.Xml;
using System.Text;
using System.Text.Json;

namespace XML
{
    class Program
    {
        static bool validateXml(string path)
        {
            var messages = new StringBuilder();

            var settings = new XmlReaderSettings
            {
                ValidationType = ValidationType.DTD,
                DtdProcessing = DtdProcessing.Parse
            };

            settings.ValidationEventHandler += (sender, args) => messages.AppendLine(args.Message);

            var reader = XmlReader.Create(path, settings);
            while (reader.Read()) {}

            if (messages.Length > 0)
            {
                throw (new Exception(messages.ToString()));
            }
            return true;
        }

        static void Main(string[] args)
        {
            validateXml("data.xml");

            try
            {

                XmlDocument xDoc = new XmlDocument();

                xDoc.Load("data.xml");


                XmlElement xRoot = xDoc.DocumentElement;


                foreach (XmlNode xnode in xRoot)
                {
                    foreach (XmlNode childnode in xnode.ChildNodes)
                    {
                        if (childnode.Name == "id")
                            Console.WriteLine($"ID: {childnode.InnerText}");
                        if (childnode.Name == "name")
                            Console.WriteLine($"Имя: {childnode.InnerText}");
                        if (childnode.Name == "born")
                            Console.WriteLine($"Дата рождения: {childnode.InnerText}");
                        if (childnode.Name == "died")
                            Console.WriteLine($"Дата смерти: {childnode.InnerText}");
                        

                        foreach (XmlNode chNode_comp in childnode.ChildNodes)
                        {
                            if (chNode_comp.Name == "title")
                                Console.WriteLine($"Название романа: {chNode_comp.InnerText}");
                            if (chNode_comp.Name == "type")
                                Console.WriteLine($"Тип произведения : {chNode_comp.InnerText}");
                            if (chNode_comp.Name == "year")
                                Console.WriteLine($"Год издания: {chNode_comp.InnerText} \n");
                        }
                    }
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}

