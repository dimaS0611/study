using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace shoot
{
    public partial class Form_Shoot : Form
    {
        public Form_Shoot()
        {
            InitializeComponent();
        }

        int rad = 0;
        int count_of_shots;
        int X;
        int Y;
        List<KeyValuePair<int, int>> count_OnTarget = new List<KeyValuePair<int, int>>();
        List<KeyValuePair<int, int>> count_PastTarget = new List<KeyValuePair<int, int>>();

        private void Form_Shoot_Load(object sender, EventArgs e)
        {
            button_Shoot.Enabled = false;
        }

        private void pictureBox_Shoot_Paint(object sender, PaintEventArgs e)
        {
            float side = pictureBox_Shoot.Width;
            e.Graphics.FillRectangle(Brushes.White, new RectangleF(0, 0, side, side));
            e.Graphics.FillRectangle(Brushes.Green, new RectangleF(side / 2 - rad, side / 2 - rad, 2 * rad, 2 * rad));
            e.Graphics.FillEllipse(Brushes.White, new RectangleF(side / 2 - 2 * rad, side / 2 - 2 * rad, 2 * rad, 2 * rad));
            e.Graphics.FillEllipse(Brushes.White, new RectangleF(side / 2, side / 2, 2 * rad, 2 * rad));
            if (rad > 0)
            {
                e.Graphics.DrawLine(Pens.Blue, side / 2, 0, side / 2, side);
                e.Graphics.DrawLine(Pens.Blue, 0, side / 2, side, side / 2);
            }

            for (int i = 0; i < count_OnTarget.Count; i++)
                e.Graphics.FillEllipse(Brushes.Red, new RectangleF(count_OnTarget[i].Key - 2, count_OnTarget[i].Value - 2, 4, 4));
            
            for (int i = 0; i < count_PastTarget.Count; i++)
                e.Graphics.FillEllipse(Brushes.Red, new RectangleF(count_PastTarget[i].Key - 2, count_PastTarget[i].Value - 2, 4, 4));
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button_Shoot_Click(object sender, EventArgs e)
        {
            Graphics g = pictureBox_Shoot.CreateGraphics();
            if (Math.Abs(X) > rad || Math.Abs(Y) > rad)
            {
                errorProviderShoot.SetError(textBox4_Cord, "Missing target coordinates");
                textBox_NumShoot.Text = "";
            }
            else
            {
                if (X * Y >= 0)//первая и третья четверть
                {
                    if (Math.Abs(X) < rad && Math.Abs(Y) < rad)
                        count_OnTarget.Add(new KeyValuePair<int, int>(X + pictureBox_Shoot.Width / 2, pictureBox_Shoot.Width / 2 - Y));
                    else
                        count_PastTarget.Add(new KeyValuePair<int, int>(X + pictureBox_Shoot.Width / 2, pictureBox_Shoot.Width / 2 - Y));
                }
                else//вторая и четвертая
                {
                    float len = (float)Math.Sqrt((rad - Math.Abs(X)) * (rad - Math.Abs(X)) + (rad - Math.Abs(Y)) * (rad - Math.Abs(Y)));
                    X += pictureBox_Shoot.Width / 2;
                    Y = pictureBox_Shoot.Width / 2 - Y;
                    
                    if (len > rad)
                        count_OnTarget.Add(new KeyValuePair<int, int>(X, Y));
                    else
                        count_PastTarget.Add(new KeyValuePair<int, int>(X, Y));
                }
               
                pictureBox_Shoot_Paint(sender, new PaintEventArgs(g, new Rectangle(pictureBox_Shoot.Location, pictureBox_Shoot.Size)));
                count_of_shots--;
                textBox4_Cord.Text = "";
                textBox_NumRemain.Text = count_of_shots.ToString();
                textBox_OnTarget.Text = count_OnTarget.Count.ToString();
                textBox_PastTarget.Text = count_PastTarget.Count.ToString();
            }
        }

        private void textBox4_Cord_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                int pos = textBox4_Cord.Text.IndexOf(';');
                if (pos == -1 || pos == 0)
                    throw new Exception();
                X = Int32.Parse(textBox4_Cord.Text.Substring(0, pos));
                Y = Int32.Parse(textBox4_Cord.Text.Substring(pos + 1, textBox4_Cord.Text.Length - pos - 1));
                errorProvider_Cord.Clear();
            }
            catch
            {
                errorProvider_Cord.SetError(textBox4_Cord, "Input error! Enter num;num!");
                e.Cancel = true;
            }
        }

        private void textBox_NumShoot_Validated(object sender, EventArgs e)
        {
            textBox_NumRemain.Text = count_of_shots.ToString();
        }

        private void textBox_NumShoot_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                count_of_shots = Int32.Parse(textBox_NumShoot.Text);
                if (count_of_shots <= 0)
                    throw new Exception();
                button_Shoot.Enabled = true;
                errorProviderShoot.Clear();
            }
            catch
            {
                errorProviderShoot.SetError(textBox_NumShoot, "Input error");
                e.Cancel = true;
            }
        }

        private void textBox_Rad_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                rad = Int32.Parse(textBox_Rad.Text);
                if (rad <= 0)
                    throw new Exception();
                
                count_OnTarget = new List<KeyValuePair<int, int>>();
                count_PastTarget = new List<KeyValuePair<int, int>>();
                textBox_OnTarget.Text = "0";
                textBox_PastTarget.Text = "0";
                pictureBox_Shoot.Size = new Size(2 * rad, 2 * rad);
                Form_Shoot.ActiveForm.MinimumSize = new Size(4 * rad + 16, 2 * rad + 39);
                errorProviderRad.Clear();
            }
            catch
            {
                errorProviderRad.SetError(textBox_Rad, "Input error");
                e.Cancel = true;
            }
        }

        private void textBox_NumRemain_TextChanged_1(object sender, EventArgs e)
        {
            if (textBox_NumRemain.Text == "0")
            {
                button_Shoot.Enabled = false;
            }
            else
            {
                button_Shoot.Enabled = true;
            }
        }
    }
}
