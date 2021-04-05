using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace calculator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            calculator("*");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            calculator("+");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            calculator("-");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            calculator("/");
        }

        public Boolean checking()
        {
            if(FirstTextBox.Text == "" || SecondTextBox.Text == "")
            {
                MessageBox.Show("Please fill Text Box. Thank you!!");
                return false;
            }

            return true;
        }

        public void calculator(string oprator)
        {
            Boolean ch = checking();
            if (ch == false)
            {
                reset();
            }

            int first_num = Convert.ToInt32(FirstTextBox.Text);
            int sec_num = Convert.ToInt32(SecondTextBox.Text);

            if (oprator.Equals("+"))
                ResultTextBox.Text = Convert.ToString(first_num + sec_num);

            if (oprator.Equals("-"))
                ResultTextBox.Text = Convert.ToString(first_num - sec_num);

            if (oprator.Equals("*"))
            {
                if (FirstTextBox.Text == "0" || SecondTextBox.Text == "0")
                {
                    MessageBox.Show("You can't enter 0");
                    FirstTextBox.Text = "1";
                    SecondTextBox.Text = "1";
                }
                ResultTextBox.Text = Convert.ToString(first_num * sec_num);
            }

            if (oprator.Equals("/"))
            {
                if (FirstTextBox.Text == "0" || SecondTextBox.Text == "0")
                {
                    MessageBox.Show("You can't enter 0");
                    FirstTextBox.Text = "1";
                    SecondTextBox.Text = "1";
                }

                ResultTextBox.Text = Convert.ToString(first_num / sec_num);
            }
        }

        private void reset()
        {
            FirstTextBox.Text = "0";
            SecondTextBox.Text = "0";

        }
    }
}
