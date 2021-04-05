namespace shoot
{
    partial class Form_Shoot
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.pictureBox_Shoot = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_Rad = new System.Windows.Forms.TextBox();
            this.textBox_NumShoot = new System.Windows.Forms.TextBox();
            this.textBox_NumRemain = new System.Windows.Forms.TextBox();
            this.textBox4_Cord = new System.Windows.Forms.TextBox();
            this.textBox_OnTarget = new System.Windows.Forms.TextBox();
            this.textBox_PastTarget = new System.Windows.Forms.TextBox();
            this.button_Shoot = new System.Windows.Forms.Button();
            this.errorProviderRad = new System.Windows.Forms.ErrorProvider(this.components);
            this.errorProviderShoot = new System.Windows.Forms.ErrorProvider(this.components);
            this.errorProvider_Cord = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Shoot)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProviderRad)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProviderShoot)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider_Cord)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox_Shoot
            // 
            this.pictureBox_Shoot.Location = new System.Drawing.Point(413, 0);
            this.pictureBox_Shoot.Name = "pictureBox_Shoot";
            this.pictureBox_Shoot.Size = new System.Drawing.Size(543, 556);
            this.pictureBox_Shoot.TabIndex = 0;
            this.pictureBox_Shoot.TabStop = false;
            this.pictureBox_Shoot.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox_Shoot_Paint);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Radius";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 81);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(144, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "Number of shots fired";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 128);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 17);
            this.label3.TabIndex = 3;
            this.label3.Text = "Shots left.";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 178);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(110, 17);
            this.label4.TabIndex = 4;
            this.label4.Text = "Coordinates X;Y";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 437);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(100, 17);
            this.label5.TabIndex = 5;
            this.label5.Text = "Number of hits";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 483);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(0, 17);
            this.label6.TabIndex = 6;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(15, 470);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(121, 17);
            this.label7.TabIndex = 7;
            this.label7.Text = "Number of misses";
            // 
            // textBox_Rad
            // 
            this.textBox_Rad.Location = new System.Drawing.Point(218, 30);
            this.textBox_Rad.Name = "textBox_Rad";
            this.textBox_Rad.Size = new System.Drawing.Size(100, 22);
            this.textBox_Rad.TabIndex = 8;
            this.textBox_Rad.Validating += new System.ComponentModel.CancelEventHandler(this.textBox_Rad_Validating);
            // 
            // textBox_NumShoot
            // 
            this.textBox_NumShoot.Location = new System.Drawing.Point(218, 75);
            this.textBox_NumShoot.Name = "textBox_NumShoot";
            this.textBox_NumShoot.Size = new System.Drawing.Size(100, 22);
            this.textBox_NumShoot.TabIndex = 9;
            this.textBox_NumShoot.Validating += new System.ComponentModel.CancelEventHandler(this.textBox_NumShoot_Validating);
            this.textBox_NumShoot.Validated += new System.EventHandler(this.textBox_NumShoot_Validated);
            // 
            // textBox_NumRemain
            // 
            this.textBox_NumRemain.Location = new System.Drawing.Point(218, 123);
            this.textBox_NumRemain.Name = "textBox_NumRemain";
            this.textBox_NumRemain.Size = new System.Drawing.Size(100, 22);
            this.textBox_NumRemain.TabIndex = 10;
            this.textBox_NumRemain.Text = "0";
            this.textBox_NumRemain.TextChanged += new System.EventHandler(this.textBox_NumRemain_TextChanged_1);
            // 
            // textBox4_Cord
            // 
            this.textBox4_Cord.Location = new System.Drawing.Point(218, 178);
            this.textBox4_Cord.Name = "textBox4_Cord";
            this.textBox4_Cord.Size = new System.Drawing.Size(100, 22);
            this.textBox4_Cord.TabIndex = 11;
            this.textBox4_Cord.Validating += new System.ComponentModel.CancelEventHandler(this.textBox4_Cord_Validating);
            // 
            // textBox_OnTarget
            // 
            this.textBox_OnTarget.Location = new System.Drawing.Point(218, 431);
            this.textBox_OnTarget.Name = "textBox_OnTarget";
            this.textBox_OnTarget.Size = new System.Drawing.Size(100, 22);
            this.textBox_OnTarget.TabIndex = 12;
            this.textBox_OnTarget.Text = "0";
            // 
            // textBox_PastTarget
            // 
            this.textBox_PastTarget.Location = new System.Drawing.Point(218, 470);
            this.textBox_PastTarget.Name = "textBox_PastTarget";
            this.textBox_PastTarget.Size = new System.Drawing.Size(100, 22);
            this.textBox_PastTarget.TabIndex = 13;
            this.textBox_PastTarget.Text = "0";
            // 
            // button_Shoot
            // 
            this.button_Shoot.Location = new System.Drawing.Point(95, 275);
            this.button_Shoot.Name = "button_Shoot";
            this.button_Shoot.Size = new System.Drawing.Size(223, 57);
            this.button_Shoot.TabIndex = 14;
            this.button_Shoot.Text = "Shoot";
            this.button_Shoot.UseVisualStyleBackColor = true;
            this.button_Shoot.Click += new System.EventHandler(this.button_Shoot_Click);
            // 
            // errorProviderRad
            // 
            this.errorProviderRad.ContainerControl = this;
            // 
            // errorProviderShoot
            // 
            this.errorProviderShoot.ContainerControl = this;
            // 
            // errorProvider_Cord
            // 
            this.errorProvider_Cord.ContainerControl = this;
            // 
            // Form_Shoot
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(957, 557);
            this.Controls.Add(this.button_Shoot);
            this.Controls.Add(this.textBox_PastTarget);
            this.Controls.Add(this.textBox_OnTarget);
            this.Controls.Add(this.textBox4_Cord);
            this.Controls.Add(this.textBox_NumRemain);
            this.Controls.Add(this.textBox_NumShoot);
            this.Controls.Add(this.textBox_Rad);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox_Shoot);
            this.Name = "Form_Shoot";
            this.Text = "Shoot";
            this.Load += new System.EventHandler(this.Form_Shoot_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Shoot)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProviderRad)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProviderShoot)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider_Cord)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox_Shoot;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_Rad;
        private System.Windows.Forms.TextBox textBox_NumShoot;
        private System.Windows.Forms.TextBox textBox_NumRemain;
        private System.Windows.Forms.TextBox textBox4_Cord;
        private System.Windows.Forms.TextBox textBox_OnTarget;
        private System.Windows.Forms.TextBox textBox_PastTarget;
        private System.Windows.Forms.Button button_Shoot;
        private System.Windows.Forms.ErrorProvider errorProviderRad;
        private System.Windows.Forms.ErrorProvider errorProviderShoot;
        private System.Windows.Forms.ErrorProvider errorProvider_Cord;
    }
}

