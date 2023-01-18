using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace StackCalcCS
{
    //private void operstack()
    //{

    //}
    //     부분적퍼블릭
    public partial class MainForm : Form
    {
        //스택은 팝하면서 탑을받을필요가없고 그냥받으면된다
        public List<string> m_lstNum = new List<string>(); // ->stl 의 벡터랑 같다.대신 쓰려면 뉴를 해줘야함 역시포인터기때문에
        public Stack<int> m_stkNum = new Stack<int>();
        public Stack<string> m_stkStringoper = new Stack<string>();

        //생성자
        //모든변수함수에 퍼블릭을안붙히면 프라이빗
        public MainForm()
        {

            InitializeComponent();



            //    Button b = new Button();
            //    b.Location = new System.Drawing.Point(517, 150);
            //    //b.Name = "ui_btnConfirm";
            //    b.Size = new System.Drawing.Size(75, 23);
            //    b.TabIndex = 3;
            //    b.Text = "확인";
            //    b.UseVisualStyleBackColor = true;
            //    b.Click += new System.EventHandler(this.ui_btnConfirm_Click);
            //    //여기까지하면 버튼안나옴 부모를지정해줘야 옮기던말던함  같은함수를 공유한다!!
            //    b.Parent = this;
            //    m_lstCon.Add(1);
            //    m_lstCon.Add(2);
            //    m_lstCon.Add(3);
            //    string s = "asdf";

            //    //auto == var   
            //    foreach(var v in m_lstCon)
            //    {
            //        MessageBox.Show(v.ToString());
            //    }



            //}

            //private void ui_btnConfirm_Click(object sender, EventArgs e)
            //{
            //    MessageBox.Show(ui_tbText.Text);
            //    MessageBox.Show(m_lstCon[2].ToString());
            //}

            //private void ui_btnConfirm_MouseClick(object sender, MouseEventArgs e)
            //{
            //    int x = e.X;
            //    int y = e.Y;
            //    MessageBox.Show(x.ToString());
            //}
        }

        private void ui_btNum1_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 1;
        }

        private void ui_btNum0_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 0;
        }

        private void ui_btNum2_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 2;
        }

        private void ui_btNum3_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 3;
        }

        private void ui_btNum4_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 4;
        }

        private void ui_btNum5_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 5;
        }

        private void ui_btNum6_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 6;
        }

        private void ui_btNum7_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 7;
        }

        private void ui_btNum8_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 8;
        }

        private void ui_btNum9_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += 9;
        }

        private void ui_btN_backspace_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text != "")
            {
                if (ui_textbox.Text == "0")
                {
                    return;
                }
                else
                {
                    ui_textbox.Text = ui_textbox.Text.Substring(0, ui_textbox.Text.Length - 1);
                }

            }
            else
            {
                ui_textbox.Text += "0";
            }

        }

        private void ui_btN_allclear_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text != "")
            {
                if (ui_textbox.Text == "0") return;
                else
                {
                    ui_textbox.Text = ui_textbox.Text.Substring(0, 0);
                    ui_textbox.Text += "0";
                }

            }
        }

        private void ui_btNoper_plus_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += "+";
        }

        private void ui_btNoper_minus_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += "-";
        }

        private void ui_btNoper_multi_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += "*";
        }

        private void ui_btNoper_divide_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += "/";
        }

        private void ui_btNoper_leftparent_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += "(";
        }

        private void ui_btNoper_rightparent_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += ")";
        }
        private void ui_btN_dot_Click(object sender, EventArgs e)
        {
            if (ui_textbox.Text == "0")
            {
                ui_textbox.Text = "";
            }
            ui_textbox.Text += ".";
        }

        private void ui_btNoper_equal_Click(object sender, EventArgs e)
        {
            String str = ui_textbox.Text;
            String strTemp = "";

            for (int i = 0; i < str.Length; i++)
            {
                strTemp = str[i].ToString();

                if (strTemp == "(")
                {
                    m_lstNum.Add(strTemp);
                    
                    strTemp = str[i + 1].ToString();//다음것으로 이동
                    if (strTemp == "-")
                    {
                        i++;
                        strTemp += str[i + 1].ToString();
                        while ((strTemp != "+" || strTemp != "-" || strTemp != "*" ||
                            strTemp != "/" || strTemp != "(" || strTemp != ")")
                            &&!String.IsNullOrEmpty(str))
                        {
                            i++;
                            strTemp += str[i + 1].ToString();
                        }
                        m_lstNum.Add(strTemp);
                        strTemp = "";
                    }
                    else if (strTemp == ")")
                    {
                        m_lstNum.Add(strTemp);
                        strTemp = "";
                    }
                    else if (strTemp == "(")
                    {
                        strTemp = str[i + 2].ToString();
                        while (strTemp != "(")
                        {
                            strTemp += str[i + 2].ToString();
                            i++;
                        }
                        m_lstNum.Add(strTemp);
                        strTemp = "";
                    }
                    //숫자일떄
                    else
                    {
                        strTemp = str[i + 2].ToString();
                        while (strTemp != "+" || strTemp != "-" || strTemp != "*" ||
                            strTemp != "/" || strTemp != "(" || strTemp != ")")
                        {
                            strTemp += str[i + 2].ToString();
                            i++;

                        }
                        m_lstNum.Add(strTemp);
                        strTemp = "";
                    }
                }
                else if (strTemp == "+" || strTemp == "-" ||
                        strTemp == "*" || strTemp == "/" || strTemp == ")")
                {
                    m_lstNum.Add(strTemp);
                    strTemp = "";
                }
                else
                {

                    while ((strTemp != "+" || strTemp != "-" || strTemp != "*"
                        || strTemp != "/" || strTemp != ")" || strTemp != "("))
                    {

                        if (!String.IsNullOrEmpty(str[i + 1].ToString()))
                        {
                            strTemp += str[i].ToString();
                            i++;
                        }
                        else
                            break;
                    }
                    m_lstNum.Add(strTemp);
                    strTemp = "";
                }


            }//포문 끝

            ui_textbox.Text = m_lstNum.ToString();


        }


    }
}
