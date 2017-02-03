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
    public partial class betmanager : Form
    {
        public int nrplayer, playerpool;
        public string name1, name2, name3, name4;
        

        public betmanager()
        {
            InitializeComponent();
        }

        private void player1pooltb_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (char.IsNumber(e.KeyChar) || e.KeyChar == '.')
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

        private void red_win_bt_Click(object sender, EventArgs e)
        {
            int player1bet = int.Parse(player1bettb.Text);
            int player2bet = int.Parse(player2bettb.Text);
            int player3bet = int.Parse(player3bettb.Text);
            int player4bet = int.Parse(player4bettb.Text);

            int player1pool = int.Parse(player1pooltb.Text);
            int player2pool = int.Parse(player2pooltb.Text);
            int player3pool = int.Parse(player3pooltb.Text);
            int player4pool = int.Parse(player4pooltb.Text);


            //gamblings of player 1
            if (player1redcb.Checked == true && player1bluecb.Checked == false)
            {
                player1pooltb.Text = (player1pool + player1bet).ToString();
            }
            if (player1redcb.Checked == false && player1bluecb.Checked == true)
            {
                player1pooltb.Text = (player1pool - player1bet).ToString();
            }

            //gamblings of player 2
            if (player2redcb.Checked == true && player2bluecb.Checked == false)
            {
                player2pooltb.Text = (player2pool + player2bet).ToString();
            }
            if (player2redcb.Checked == false && player2bluecb.Checked == true)
            {
                player2pooltb.Text = (player2pool - player2bet).ToString();
            }

            //gamblings of player 3

            if (player3redcb.Checked == true && player3bluecb.Checked == false)
            {
                player3pooltb.Text = (player3pool + player3bet).ToString();
            }
            if (player3redcb.Checked == false && player3bluecb.Checked == true)
            {
                player3pooltb.Text = (player3pool - player3bet).ToString();
            }

            //gamblings of player 4
            if (player4redcb.Checked == true && player4bluecb.Checked == false)
            {
                player4pooltb.Text = (player4pool + player4bet).ToString();
            }
            if (player4redcb.Checked == false && player4bluecb.Checked == true)
            {
                player4pooltb.Text = (player4pool - player4bet).ToString();
            }

            //enable the betting boxes
            player1pooltb.Enabled = true;
            player2pooltb.Enabled = true;
            player3pooltb.Enabled = true;
            player4pooltb.Enabled = true;

            player1bettb.Enabled = true;
            player2bettb.Enabled = true;
            player3bettb.Enabled = true;
            player4bettb.Enabled = true;

            player1bluecb.Enabled = true;
            player2bluecb.Enabled = true;
            player3bluecb.Enabled = true;
            player4bluecb.Enabled = true;

            player1redcb.Enabled = true;
            player2redcb.Enabled = true;
            player3redcb.Enabled = true;
            player4redcb.Enabled = true;

            //uncheck any box
            player1redcb.Checked = false;
            player2redcb.Checked = false;
            player3redcb.Checked = false;
            player4redcb.Checked = false;

            player1bluecb.Checked = false;
            player2bluecb.Checked = false;
            player3bluecb.Checked = false;
            player4bluecb.Checked = false;

            //return bet value to 0
            player1bettb.Text = 0.ToString();
            player2bettb.Text = 0.ToString();
            player3bettb.Text = 0.ToString();
            player4bettb.Text = 0.ToString();

            //enable Make Bet Button
            //make_bet_bt.Visible = false;
            make_bet_bt.Enabled = true;

            //show the possible winner buttons and label
            menu3_titlelb.Visible = false;
            menu3_titlelb.Enabled = false;

            red_win_bt.Visible = false;
            red_win_bt.Enabled = false;

            blue_win_bt.Visible = false;
            blue_win_bt.Enabled = false;


        }

        private void blue_win_bt_Click(object sender, EventArgs e)
        {
            int player1bet = int.Parse(player1bettb.Text);
            int player2bet = int.Parse(player2bettb.Text);
            int player3bet = int.Parse(player3bettb.Text);
            int player4bet = int.Parse(player4bettb.Text);

            int player1pool = int.Parse(player1pooltb.Text);
            int player2pool = int.Parse(player2pooltb.Text);
            int player3pool = int.Parse(player3pooltb.Text);
            int player4pool = int.Parse(player4pooltb.Text);


            //gamblings of player 1
            if (player1redcb.Checked == true && player1bluecb.Checked == false)
            {
                player1pooltb.Text = (player1pool - player1bet).ToString();
            }
            if (player1redcb.Checked == false && player1bluecb.Checked == true)
            {
                player1pooltb.Text = (player1pool + player1bet).ToString();
            }

            //gamblings of player 2
            if (player2redcb.Checked == true && player2bluecb.Checked == false)
            {
                player2pooltb.Text = (player2pool - player2bet).ToString();
            }
            if (player2redcb.Checked == false && player2bluecb.Checked == true)
            {
                player2pooltb.Text = (player2pool + player2bet).ToString();
            }

            //gamblings of player 3

            if (player3redcb.Checked == true && player3bluecb.Checked == false)
            {
                player3pooltb.Text = (player3pool - player3bet).ToString();
            }
            if (player3redcb.Checked == false && player3bluecb.Checked == true)
            {
                player3pooltb.Text = (player3pool + player3bet).ToString();
            }

            //gamblings of player 4
            if (player4redcb.Checked == true && player4bluecb.Checked == false)
            {
                player4pooltb.Text = (player4pool - player4bet).ToString();
            }
            if (player4redcb.Checked == false && player4bluecb.Checked == true)
            {
                player4pooltb.Text = (player4pool + player4bet).ToString();
            }

            //enable the betting boxes
            player1pooltb.Enabled = true;
            player2pooltb.Enabled = true;
            player3pooltb.Enabled = true;
            player4pooltb.Enabled = true;

            player1bettb.Enabled = true;
            player2bettb.Enabled = true;
            player3bettb.Enabled = true;
            player4bettb.Enabled = true;

            player1bluecb.Enabled = true;
            player2bluecb.Enabled = true;
            player3bluecb.Enabled = true;
            player4bluecb.Enabled = true;

            player1redcb.Enabled = true;
            player2redcb.Enabled = true;
            player3redcb.Enabled = true;
            player4redcb.Enabled = true;

            //uncheck any box
            player1redcb.Checked = false;
            player2redcb.Checked = false;
            player3redcb.Checked = false;
            player4redcb.Checked = false;

            player1bluecb.Checked = false;
            player2bluecb.Checked = false;
            player3bluecb.Checked = false;
            player4bluecb.Checked = false;

            //return bet value to 0
            player1bettb.Text = 0.ToString();
            player2bettb.Text = 0.ToString();
            player3bettb.Text = 0.ToString();
            player4bettb.Text = 0.ToString();

            //enable Make Bet Button
            //make_bet_bt.Visible = false;
            make_bet_bt.Enabled = true;

            //show the possible winner buttons and label
            menu3_titlelb.Visible = false;
            menu3_titlelb.Enabled = false;

            red_win_bt.Visible = false;
            red_win_bt.Enabled = false;

            blue_win_bt.Visible = false;
            blue_win_bt.Enabled = false;
        }

        private void player1redcb_CheckedChanged(object sender, EventArgs e)
        {
            if (player1redcb.Checked == true)
            {
                player1bluecb.Enabled = false;
            }
            else { player1bluecb.Enabled = true; }
            
        }

        private void player2redcb_CheckedChanged(object sender, EventArgs e)
        {
            if (player2redcb.Checked == true)
            {
                player2bluecb.Enabled = false;
            }
            else { player2bluecb.Enabled = true; }
        }

        private void player3redcb_CheckedChanged(object sender, EventArgs e)
        {
            if (player3redcb.Checked == true)
            {
                player3bluecb.Enabled = false;
            }
            else { player3bluecb.Enabled = true; }
        }

        private void player4redcb_CheckedChanged(object sender, EventArgs e)
        {
            if (player4redcb.Checked == true)
            {
                player4bluecb.Enabled = false;
            }
            else { player4bluecb.Enabled = true; }
        }

        private void player1bluecb_CheckedChanged(object sender, EventArgs e)
        {
            if (player1bluecb.Checked == true)
            {
                player1redcb.Enabled = false;
            }
            else { player1redcb.Enabled = true; }
        }

        private void player2bluecb_CheckedChanged(object sender, EventArgs e)
        {
            if (player2bluecb.Checked == true)
            {
                player2redcb.Enabled = false;
            }
            else { player2redcb.Enabled = true; }
        }

        private void player3bluecb_CheckedChanged(object sender, EventArgs e)
        {
            if (player3bluecb.Checked == true)
            {
                player3redcb.Enabled = false;
            }
            else { player3redcb.Enabled = true; }
        }

        private void player4bluecb_CheckedChanged(object sender, EventArgs e)
        {
            if (player4bluecb.Checked == true)
            {
                player4redcb.Enabled = false;
            }
            else { player4redcb.Enabled = true; }
        }

        public betmanager(int nr, int pool, string p1, string p2, string p3, string p4)
        {
            InitializeComponent();
            nrplayer = nr;
            playerpool = pool;
            name1 = p1;
            name2 = p2;
            name3 = p3;
            name4 = p4;
        }

        private void make_bet_bt_Click(object sender, EventArgs e)
        {
                if (int.Parse(player1bettb.Text) > int.Parse(player1pooltb.Text))
                {
                    MessageBox.Show("Player 1 Bet is Higher than his pool!");
                   
                }
                else if (int.Parse(player2bettb.Text) > int.Parse(player2pooltb.Text))
                {
                    MessageBox.Show("Player 2 Bet is Higher than his pool!");
                    
                }
                else if (int.Parse(player3bettb.Text) > int.Parse(player3pooltb.Text))
                {
                    MessageBox.Show("Player 3 Bet is Higher than his pool!");
                   
                }
                else if (int.Parse(player4bettb.Text) > int.Parse(player4pooltb.Text))
                {
                    MessageBox.Show("Player 4 Bet is Higher than his pool!");
                    
                }
           else
            { 

            //block the player pool, player bet textboxes and red-blue checkboxes from user alterations
            player1pooltb.Enabled = false;
            player2pooltb.Enabled = false;
            player3pooltb.Enabled = false;
            player4pooltb.Enabled = false;

            player1bettb.Enabled = false; 
            player2bettb.Enabled = false; 
            player3bettb.Enabled = false; 
            player4bettb.Enabled = false;

            player1bluecb.Enabled = false;
            player2bluecb.Enabled = false;
            player3bluecb.Enabled = false;
            player4bluecb.Enabled = false;

            player1redcb.Enabled = false;
            player2redcb.Enabled = false;
            player3redcb.Enabled = false;
            player4redcb.Enabled = false;

            //disable Make Bet Button
            //make_bet_bt.Visible = false;
            make_bet_bt.Enabled = false;

            //show the possible winner buttons and label
            menu3_titlelb.Visible = true;
            menu3_titlelb.Enabled = true;

            red_win_bt.Visible = true;
            red_win_bt.Enabled = true;

            blue_win_bt.Visible = true;
            blue_win_bt.Enabled = true;
        }
       }

        private void end_session_bt_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void betmanager_Load(object sender, EventArgs e)
        {
            switch (nrplayer)
            {
                case 1:
                    //disable the non participating players player labels
                    player2lb.Visible = false;
                    player2lb.Enabled = false;

                    player3lb.Visible = false;
                    player3lb.Enabled = false;

                    player4lb.Visible = false;
                    player4lb.Enabled = false;

                    //disable the non participating players pool labels
                    player2poollb.Visible = false;
                    player2poollb.Enabled = false;

                    player3poollb.Visible = false;
                    player3poollb.Enabled = false;

                    player4poollb.Visible = false;
                    player4poollb.Enabled = false;

                    //disable the non participating players pool textboxes
                    player2pooltb.Visible = false;
                    player2pooltb.Enabled = false;

                    player3pooltb.Visible = false;
                    player3pooltb.Enabled = false;

                    player4pooltb.Visible = false;
                    player4pooltb.Enabled = false;

                    //disable the non participating players bet label
                    player2betlb.Visible = false;
                    player2betlb.Enabled = false;

                    player3betlb.Visible = false;
                    player3betlb.Enabled = false;

                    player4betlb.Visible = false;
                    player4betlb.Enabled = false;


                    //disable the non participating players bet TextBox
                    player2bettb.Visible = false;
                    player2bettb.Enabled = false;

                    player3bettb.Visible = false;
                    player3bettb.Enabled = false;

                    player4bettb.Visible = false;
                    player4bettb.Enabled = false;

                    //disable the non participating players Red label
                    player2redlb.Visible = false;
                    player2redlb.Enabled = false;

                    player3redlb.Visible = false;
                    player3redlb.Enabled = false;

                    player4redlb.Visible = false;
                    player4redlb.Enabled = false;

                    //disable the non participating players Red Checkbox
                    player2redcb.Visible = false;
                    player2redcb.Enabled = false;

                    player3redcb.Visible = false;
                    player3redcb.Enabled = false;

                    player4redcb.Visible = false;
                    player4redcb.Enabled = false;

                    //disable the non participating players Blue label
                    player2bluelb.Visible = false;
                    player2bluelb.Enabled = false;

                    player3bluelb.Visible = false;
                    player3bluelb.Enabled = false;

                    player4bluelb.Visible = false;
                    player4bluelb.Enabled = false;

                    //disable the non participating players Blue Checkbox
                    player2bluecb.Visible = false;
                    player2bluecb.Enabled = false;

                    player3bluecb.Visible = false;
                    player3bluecb.Enabled = false;

                    player4bluecb.Visible = false;
                    player4bluecb.Enabled = false;

                    player1pooltb.Text = playerpool.ToString();
                    if(name1 == "") { }
                    else
                    {
                        player1lb.Text = name1;
                    }
                    
                    break;

                case 2:
                    //disable the non participating players player labels
                    player3lb.Visible = false;
                    player3lb.Enabled = false;

                    player4lb.Visible = false;
                    player4lb.Enabled = false;

                    //disable the non participating players pool labels
                    player3poollb.Visible = false;
                    player3poollb.Enabled = false;

                    player4poollb.Visible = false;
                    player4poollb.Enabled = false;

                    //disable the non participating players pool textboxes
                    player3pooltb.Visible = false;
                    player3pooltb.Enabled = false;

                    player4pooltb.Visible = false;
                    player4pooltb.Enabled = false;

                    //disable the non participating players bet label
                    player3betlb.Visible = false;
                    player3betlb.Enabled = false;

                    player4betlb.Visible = false;
                    player4betlb.Enabled = false;


                    //disable the non participating players bet TextBox
                    player3bettb.Visible = false;
                    player3bettb.Enabled = false;

                    player4bettb.Visible = false;
                    player4bettb.Enabled = false;

                    //disable the non participating players Red label
                    player3redlb.Visible = false;
                    player3redlb.Enabled = false;

                    player4redlb.Visible = false;
                    player4redlb.Enabled = false;

                    //disable the non participating players Red Checkbox
                    player3redcb.Visible = false;
                    player3redcb.Enabled = false;

                    player4redcb.Visible = false;
                    player4redcb.Enabled = false;

                    //disable the non participating players Blue label
                    player3bluelb.Visible = false;
                    player3bluelb.Enabled = false;

                    player4bluelb.Visible = false;
                    player4bluelb.Enabled = false;

                    //disable the non participating players Blue Checkbox
                    player3bluecb.Visible = false;
                    player3bluecb.Enabled = false;

                    player4bluecb.Visible = false;
                    player4bluecb.Enabled = false;

                    //setting the player bet pool
                    player1pooltb.Text = playerpool.ToString();
                    if (name1 == "") { }
                    else
                    {
                        player1lb.Text = name1;
                    }
                    player2pooltb.Text = playerpool.ToString();
                    if (name2 == "") { }
                    else
                    {
                        player2lb.Text = name2;
                    }

                    break;

                case 3:
                    //disable the non participating players player labels
                    //player3lb.Visible = false;
                    //player3lb.Enabled = false;

                    player4lb.Visible = false;
                    player4lb.Enabled = false;

                    //disable the non participating players pool labels
                   // player3poollb.Visible = false;
                    //player3poollb.Enabled = false;

                    player4poollb.Visible = false;
                    player4poollb.Enabled = false;

                    //disable the non participating players pool textboxes
                  //  player3pooltb.Visible = false;
                  //  player3pooltb.Enabled = false;

                    player4pooltb.Visible = false;
                    player4pooltb.Enabled = false;

                    //disable the non participating players bet label
                //    player3betlb.Visible = false;
                  //  player3betlb.Enabled = false;

                    player4betlb.Visible = false;
                    player4betlb.Enabled = false;


                    //disable the non participating players bet TextBox
                  //  player3bettb.Visible = false;
                  //  player3bettb.Enabled = false;

                    player4bettb.Visible = false;
                    player4bettb.Enabled = false;

                    //disable the non participating players Red label
                //    player3redlb.Visible = false;
                //    player3redlb.Enabled = false;

                    player4redlb.Visible = false;
                    player4redlb.Enabled = false;

                    //disable the non participating players Red Checkbox
                //    player3redcb.Visible = false;
                //    player3redcb.Enabled = false;

                    player4redcb.Visible = false;
                    player4redcb.Enabled = false;

                    //disable the non participating players Blue label
                //    player3bluelb.Visible = false;
                //    player3bluelb.Enabled = false;

                    player4bluelb.Visible = false;
                    player4bluelb.Enabled = false;

                    //disable the non participating players Blue Checkbox
                //    player3bluecb.Visible = false;
                //    player3bluecb.Enabled = false;

                    player4bluecb.Visible = false;
                    player4bluecb.Enabled = false;

                    //setting the player bet pool and name
                    player1pooltb.Text = playerpool.ToString();
                    if (name1 == "") { }
                    else
                    {
                        player1lb.Text = name1;
                    }

                    player2pooltb.Text = playerpool.ToString();
                    if (name2 == "") { }
                    else
                    {
                        player2lb.Text = name2;
                    }

                    player3pooltb.Text = playerpool.ToString();
                    if (name3 == "") { }
                    else
                    {
                        player3lb.Text = name3;
                    }

                    break;
                default:
                    player1pooltb.Text = playerpool.ToString();
                    if (name1 == "") { }
                    else
                    {
                        player1lb.Text = name1;
                    }

                    player2pooltb.Text = playerpool.ToString();
                    if (name2 == "") { }
                    else
                    {
                        player2lb.Text = name2;
                    }

                    player3pooltb.Text = playerpool.ToString();
                    if (name3 == "") { }
                    else
                    {
                        player3lb.Text = name3;
                    }

                    player4pooltb.Text = playerpool.ToString();
                    if (name4 == "") { }
                    else
                    {
                        player4lb.Text = name4;
                    }

                    break;


            }
        }
    }
}
