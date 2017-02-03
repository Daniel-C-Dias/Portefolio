using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace saltybet_manual
{
    public partial class main_menu : Form
    {
        public main_menu()
        {
            InitializeComponent();
        }

        private void enterbt_Click(object sender, EventArgs e)
        {
            
            int num_players = int.Parse(nr_players_tb.Text);
            int pool_players = int.Parse(player_pool_tb.Text);

            if (num_players < 0 || num_players > 4 || pool_players < 0)
            {
                MessageBox.Show("Invalid Number of Players or Player Pool Amount");
            }
            else
            {
                //disable and hide the elements from the main menu
                menu1_title1.Visible = false;
                menu1_title1.Enabled = false;

                menu1_title2.Visible = false;
                menu1_title2.Enabled = false;

                menu1_title3.Visible = false;
                menu1_title3.Enabled = false;

                cifrao.Visible = false;
                cifrao.Enabled = false;

                nr_players_tb.Visible = false;
                nr_players_tb.Enabled = false;

                player_pool_tb.Visible = false;
                player_pool_tb.Enabled = false;

                enterbt.Visible = false;
                enterbt.Enabled = false;

                pictureBox1.Visible = false;
                pictureBox1.Enabled = false;

                //enable and show the elements from the player name settings menu 
                menu2_title.Visible = true;
                menu2_title.Enabled = true;

                pictureBox2.Visible = true;
                pictureBox2.Enabled = true;

                menu2_backbt.Visible = true;
                menu2_backbt.Enabled = true;

                menu2_okbt.Visible = true;
                menu2_okbt.Enabled = true;

                //enable the elements that depend on the number of players
                switch (num_players)
                {
                    case 1:
                        menu2_label1.Visible = true;
                        menu2_label1.Enabled = true;

                        menu2_textBox1.Visible = true;
                        menu2_textBox1.Enabled = true;

                        break;
                    case 2:
                        menu2_label1.Visible = true;
                        menu2_label1.Enabled = true;

                        menu2_textBox1.Visible = true;
                        menu2_textBox1.Enabled = true;

                        menu2_label2.Visible = true;
                        menu2_label2.Enabled = true;

                        menu2_textBox2.Visible = true;
                        menu2_textBox2.Enabled = true;

                        break;

                    case 3:
                        menu2_label1.Visible = true;
                        menu2_label1.Enabled = true;

                        menu2_textBox1.Visible = true;
                        menu2_textBox1.Enabled = true;

                        menu2_label2.Visible = true;
                        menu2_label2.Enabled = true;

                        menu2_textBox2.Visible = true;
                        menu2_textBox2.Enabled = true;

                        menu2_label3.Visible = true;
                        menu2_label3.Enabled = true;

                        menu2_textBox3.Visible = true;
                        menu2_textBox3.Enabled = true;

                        break;

                    case 4:
                        menu2_label1.Visible = true;
                        menu2_label1.Enabled = true;

                        menu2_textBox1.Visible = true;
                        menu2_textBox1.Enabled = true;

                        menu2_label2.Visible = true;
                        menu2_label2.Enabled = true;

                        menu2_textBox2.Visible = true;
                        menu2_textBox2.Enabled = true;

                        menu2_label3.Visible = true;
                        menu2_label3.Enabled = true;

                        menu2_textBox3.Visible = true;
                        menu2_textBox3.Enabled = true;

                        menu2_label4.Visible = true;
                        menu2_label4.Enabled = true;

                        menu2_textBox4.Visible = true;
                        menu2_textBox4.Enabled = true;

                        break;

                }
            }
        }

        private void menu2_okbt_Click(object sender, EventArgs e)
        {
            betmanager f2 = new betmanager(int.Parse(nr_players_tb.Text), int.Parse(player_pool_tb.Text), menu2_textBox1.Text, menu2_textBox2.Text , menu2_textBox3.Text , menu2_textBox4.Text);
            this.Hide();
            f2.ShowDialog();
            this.Show();
        }

        private void menu2_backbt_Click(object sender, EventArgs e)
        {

            int num_players = int.Parse(nr_players_tb.Text);
            int pool_players = int.Parse(player_pool_tb.Text);

            //Clean the Previous Inserted Names
            menu2_textBox1.Text = "";
            menu2_textBox2.Text = "";
            menu2_textBox3.Text = "";
            menu2_textBox4.Text = "";

            //Enable and Show the elements from the main menu
            menu1_title1.Visible = true;
                menu1_title1.Enabled = true;

                menu1_title2.Visible = true;
                menu1_title2.Enabled = true;

                menu1_title3.Visible = true;
                menu1_title3.Enabled = true;

                cifrao.Visible = true;
                cifrao.Enabled = true;

                nr_players_tb.Visible = true;
                nr_players_tb.Enabled = true;

                player_pool_tb.Visible = true;
                player_pool_tb.Enabled = true;

                enterbt.Visible = true;
                enterbt.Enabled = true;

                pictureBox1.Visible = true;
                pictureBox1.Enabled = true;

                //disable and hide the elements from the player name settings menu 
                menu2_title.Visible = false;
                menu2_title.Enabled = false;

                pictureBox2.Visible = false;
                pictureBox2.Enabled = false;

                menu2_backbt.Visible = false;
                menu2_backbt.Enabled = false;

                menu2_okbt.Visible = false;
                menu2_okbt.Enabled = false;

                //disable and hide the elements that depend on the number of players
                switch (num_players)
                {
                    case 1:
                    menu2_label1.Visible = false;
                    menu2_label1.Enabled = false;

                    menu2_textBox1.Visible = false;
                    menu2_textBox1.Enabled = false;

                    break;
                    case 2:
                    menu2_label1.Visible = false;
                    menu2_label1.Enabled = false;

                    menu2_textBox1.Visible = false;
                    menu2_textBox1.Enabled = false;

                    menu2_label2.Visible = false;
                    menu2_label2.Enabled = false;

                    menu2_textBox2.Visible = false;
                    menu2_textBox2.Enabled = false;

                    break;

                    case 3:
                    menu2_label1.Visible = false;
                    menu2_label1.Enabled = false;

                    menu2_textBox1.Visible = false;
                    menu2_textBox1.Enabled = false;

                    menu2_label2.Visible = false;
                    menu2_label2.Enabled = false;

                    menu2_textBox2.Visible = false;
                    menu2_textBox2.Enabled = false;

                    menu2_label3.Visible = false;
                    menu2_label3.Enabled = false;

                    menu2_textBox3.Visible = false;
                    menu2_textBox3.Enabled = false;

                    break;

                    case 4:
                        menu2_label1.Visible = false;
                        menu2_label1.Enabled = false;

                        menu2_textBox1.Visible = false;
                        menu2_textBox1.Enabled = false;

                        menu2_label2.Visible = false;
                        menu2_label2.Enabled = false;

                        menu2_textBox2.Visible = false;
                        menu2_textBox2.Enabled = false;

                        menu2_label3.Visible = false;
                        menu2_label3.Enabled = false;

                        menu2_textBox3.Visible = false;
                        menu2_textBox3.Enabled = false;

                        menu2_label4.Visible = false;
                        menu2_label4.Enabled = false;

                        menu2_textBox4.Visible = false;
                        menu2_textBox4.Enabled = false;

                        break;
            }
        }

        private void nr_players_tb_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (char.IsNumber(e.KeyChar) && e.KeyChar <'5' ) 
            {

            }
            else
            {
                if (e.KeyChar != (char)8)
                {
                    e.Handled = e.KeyChar != (char)Keys.Back;
                    MessageBox.Show("Please Only Enter Integer Numbers Between 1 and 4 ");
                }
            }
        }

        private void player_pool_tb_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (char.IsNumber(e.KeyChar) || e.KeyChar == '.' )  
            {

            }
            else
            {
                if (e.KeyChar != (char)8)
                {
                    e.Handled = e.KeyChar != (char)Keys.Back;
                    MessageBox.Show("Please Only Enter Number Values");
                }
            }
        }
    }
}
