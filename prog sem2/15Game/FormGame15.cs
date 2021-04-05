using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Game15
{
    public partial class FormGame15 : Form
    {
        GameLogic game;

        public FormGame15()
        {
            InitializeComponent();
            game = new GameLogic(4);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GameStart();
        }

        private void button12_Click(object sender, EventArgs e)
        {
            int position = Convert.ToInt32(((Button)sender).Tag);
            game.Shift(position);

            

            refresh();

            if (game.CheckNum())
            {
                MessageBox.Show("You win!!!");
                GameStart();
            }
        }

        private Button button(int position)
        {
            switch (position)
            {
                case 0: return button0;
                case 1: return button1;
                case 2: return button2;
                case 3: return button3;
                case 4: return button4;
                case 5: return button5;
                case 6: return button6;
                case 7: return button7;
                case 8: return button8;
                case 9: return button9;
                case 10: return button10;
                case 11: return button11;
                case 12: return button12;
                case 13: return button13;
                case 14: return button14;
                case 15: return button15;

                default: return null;
            }
        }

        private void GameStart()
        {
            game.Start();

            for (int i = 0; i < 100; i++)
                game.ShiftRandom();
                
            refresh();
               
        }

        private void MenuStart_Click(object sender, EventArgs e)
        {
            GameStart();
        }

        private void refresh()
        {
            for(int pos = 0; pos < 16; pos++)
            {
                int nr = game.GetNum(pos);

                button (pos).Text = nr.ToString();
                button(pos).Visible = (nr > 0);
            }
        }



    }
}
