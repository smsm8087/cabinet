using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CoApp1
{

    public partial class MainForm : Form
    {
        //변수선언시 public 이라고 개별적으로 안붙여주면 private로 선언됨
        //public int x;
        //List<int> m_lstCon = new List<int>();
        //Stack<int> m_stk = new Stack<int>();
        List<string> m_listString = new List<string>();
        Stack<string> m_sStack = new Stack<string>();
        Stack<float> m_colStack = new Stack<float>();
        //생성자
        public MainForm()
        {
            InitializeComponent();
            ////코드로 버튼 띄우기
            //Button b = new Button();
            //b.Location = new System.Drawing.Point(366, 52);
            ////b.Name = "ui_button1";
            //b.Size = new System.Drawing.Size(75, 23);
            //b.TabIndex = 2;
            //b.Text = "확인";
            //b.UseVisualStyleBackColor = true;
            //b.Click += new System.EventHandler(this.ui_button1_Click);
            //b.Parent = this;
        }

        //private void ui_button1_Click(object sender, EventArgs e)
        //{
        //    m_lstCon.Add(1);
        //    m_lstCon.Add(2);
        //    m_lstCon.Add(3);
        //    m_lstCon.Add(4);

        //    //var v = m_lstCon.
        //    foreach(var v in m_lstCon)
        //    {
                
        //    }
        //    for(int i = 0; i<m_lstCon.Capacity; ++i)
        //    {
        //        int x = 0;
        //    }
        //    string s = "asdf";
        //    //var a=s[2];
            
        //    MessageBox.Show(texbox_result.Text.ToString());
            
        //}

        private void btn_7_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "7";
        }

        private void btn_8_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "8";
        }

        private void btn_9_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "9";
        }

        private void btn_4_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "4";
        }

        private void btn_5_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "5";
        }

        private void btn_6_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "6";
        }

        private void btn_1_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "1";
        }

        private void btn_2_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "2";
        }

        private void btn_3_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "3";
        }

        private void btn_0_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "0";
        }

        private void btn_mul_Click(object sender, EventArgs e)
        {
            string s = texbox_result.Text;
            if (s.Length < 0)
                return;
            s = s[s.Length - 1].ToString();
            if (s == "*" || s == "/" || s == "+" || s == "-" || s == ".")
            {
                texbox_result.Text = texbox_result.Text.Substring(0, texbox_result.Text.Length - 1);

            }
            texbox_result.Text += "*";
        }
        private void btn_div_Click(object sender, EventArgs e)
        {
            string s = texbox_result.Text;
            if (s.Length < 0)
                return;

            s = s[s.Length - 1].ToString();
            if (s == "*" || s == "/" || s == "+" || s == "-" || s == ".")
            {
                texbox_result.Text = texbox_result.Text.Substring(0, texbox_result.Text.Length - 1);

            }
            texbox_result.Text += "/";
        }
        private void btn_sub_Click(object sender, EventArgs e)
        {
            if(texbox_result.Text.Length>0)
            {
                string s = texbox_result.Text;
                if (s.Length < 0)
                    return;

                s = s[s.Length-1].ToString();
                if(s == "*" || s == "/" || s == "+" || s == "-" || s == ".")
                {
                    texbox_result.Text = texbox_result.Text.Substring(0, texbox_result.Text.Length - 1);
                 
                }

            }
            texbox_result.Text += "-";
        }

        private void btn_puls_Click(object sender, EventArgs e)
        {
            if (texbox_result.Text.Length > 0)
            {
                string s = texbox_result.Text;
                if (s.Length < 0)
                    return;
                s = s[s.Length - 1].ToString();
                if (s == "*" || s == "/" || s == "+" || s == "-" || s == ".")
                {
                    texbox_result.Text = texbox_result.Text.Substring(0, texbox_result.Text.Length - 1);
              
                }

            }
            texbox_result.Text += "+";
        }
        
        private void btn_result_Click(object sender, EventArgs e)
        {
            string texboxstr = texbox_result.Text;
            string str = "";
            string strTemp = "";
            //str += texboxstr[i].ToString();
            for (int i = 0; i < texboxstr.Length; i++)
            {
                str += texboxstr[i].ToString();

                //맨처음 값은 -값도 가져와야됨
                if (i == 0 && str != "(")
                {
                    str = "";
                    //NumCol(m_listString, ref str, ref texboxstr, ref i);
                    for (int j = 0; j < texboxstr.Length; ++j)
                    {
                        str += texboxstr[j];
                        if (j + 1 < texboxstr.Length &&
                             (texboxstr[j + 1] == '-' ||
                             texboxstr[j + 1] == '+' ||
                             texboxstr[j + 1] == '*' ||
                             texboxstr[j + 1] == '/' ||
                             texboxstr[j + 1] == ')')
                             )
                        {
                            m_listString.Add(str);
                            i = j;
                            break;
                        }
                    }
                    str = "";
                }
                //열린 가로 뒤의 문자를 가져오기
                else if (str == "(")
                {
                    m_sStack.Push(str);
                    str = "";
                    str += texboxstr[i + 1];

                    if(str == "(")
                    {
                        
                        str = "";
                    }
                    else if(48 <= (int)str[0] && (int)str[0] <=57)
                    {
                        str = "";
                        for (int j = i + 1; j < texboxstr.Length; ++j)
                        {
                            str += texboxstr[j];
                            if (j + 1 < texboxstr.Length &&
                                 (texboxstr[j + 1] == '-' ||
                                texboxstr[j + 1] == '+' ||
                                texboxstr[j + 1] == '*' ||
                                texboxstr[j + 1] == '/' ||
                                texboxstr[j + 1] == ')')
                                 )
                            {
                                m_listString.Add(str);
                                i = j;
                                break;
                            }
                        
                        }
                        str = "";
                    }
                    else
                    {
                       // str = "";
                        ++i;
                        //NumCol(m_listString, ref str, ref texboxstr, ref i);
                        for (int j = i + 1; j < texboxstr.Length; ++j)
                        {
                            str += texboxstr[j];
                            if (j + 1 < texboxstr.Length &&
                                 (texboxstr[j + 1] == '-' ||
                                texboxstr[j + 1] == '+' ||
                                texboxstr[j + 1] == '*' ||
                                texboxstr[j + 1] == '/' ||
                                texboxstr[j + 1] == ')')
                                 )
                            {
                                m_listString.Add(str);
                                i = j;
                                break;
                            }
                            
                        }
                        str = "";
                    }
                    str = "";
                }
                //닫는 가로 나왔을때 스택에 여는 가로 나올때까지 리스트에 넣어줌
                else if (str == ")")
                {
                    var sstr = m_sStack.Pop();
                    while(sstr != "(")
                    {
                        m_listString.Add(sstr);
                        sstr = m_sStack.Pop();
                    }
                    //sstr = m_sStack.Pop();
                    str = "";
                }
                //숫자라면 리스트에 넣기
                else if(48 <= (int)str[0] && (int)str[0] <= 57)
                {
                    //str = "";
                    for (int j = i; j < texboxstr.Length; ++j)
                    {
                        
                        if (j + 1 < texboxstr.Length &&
                             (texboxstr[j + 1] == '-' ||
                             texboxstr[j + 1] == '+' ||
                             texboxstr[j + 1] == '*' ||
                             texboxstr[j + 1] == '/'  ||
                             texboxstr[j + 1] == ')')
                             )
                        {
                            m_listString.Add(str);
                            i = j;
                            break;
                        }
                        else
                        {
                            //맨끝이 닫는가로가 아니고 숫자일때
                            if(j+1 >= texboxstr.Length)
                            {
                                m_listString.Add(str);
                                i = j;
                                break;
                            }
                            //맨 끝이 닫는 가로가 나올때
                            else
                            {
                                str += texboxstr[j + 1];
                            }
                            
                        }
                     
                    }
                    str = "";
                }
                //그외의 부호들이 들어올때
                else
                {

                    int topCount = 0;
                    int strCount = 0;
                    bool isCheck = m_sStack.Any();
                    while(m_sStack.Any())
                    {

                        //우선순위 부여
                        if(m_sStack.Peek() == "+" || m_sStack.Peek() == "-")
                        {
                            topCount = 1;
                        }
                        else if (m_sStack.Peek() == "*" || m_sStack.Peek() == "/")
                        {
                            topCount = 2;
                        }
                        else
                        {
                            topCount = 0;
                        }
                        if (str == "+" || str == "-")
                        {
                            strCount = 1;
                        }
                        else if (str == "*" || str == "/")
                        {
                            strCount = 2;
                        }
                        else
                        {
                           // strCount = 0;
                        }

                        //가로열기를 만나면 빠져나몽
                        if(m_sStack.First() == "(")
                        {
                            break;
                        }
                        else
                        {
                            //탑값이 불러온 값보다 크거나 같다면 리스트에 넣어주고 스택빼줌
                            if(topCount >= strCount)
                            {
                                m_listString.Add(m_sStack.Pop());
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    m_sStack.Push(str);
                    if (!m_sStack.Any())
                    {
                        m_sStack.Push(str);
                    }
                    str = "";
                }
            }

            //스택이 빌때까지 넣어주기
            while(m_sStack.Any())
            {
                m_listString.Add(m_sStack.Pop());
            }

            foreach (var item in m_listString)
            {
                //숫자일 경우
                if(item.Length >1)
                {
                    m_colStack.Push(Convert.ToSingle(item));
                }
                else
                {
                    //아스키코드값 비교로 숫자일경우
                    if(48<=(int)item[0] && (int)item[0] <= 57)
                    {
                        m_colStack.Push(Convert.ToSingle(item));
                    }
                    //부호일 경우
                    else
                    {
                        float num1;
                        float num2;
                        float result=0;
                        if(m_colStack.Count>=2)
                        {
                            num1 = m_colStack.Pop();
                            num2 = m_colStack.Pop();
                            if (item == "-")
                            {
                                result = num2 - num1;
                            }
                            else if (item == "+")
                            {
                                result = num2 + num1;
                            }
                            else if (item == "*")
                            {
                                result = num2 * num1;
                            }
                            else if (item == "/")
                            {
                                result = num2 / num1;
                            }
                            m_colStack.Push(result);
                        }
                   
                        
                    }
                }
            }
            if(m_colStack.Count >0)
                texbox_num.Text = m_colStack.Pop().ToString();
        }
        private void btn_backspace_Click(object sender, EventArgs e)
        {
            if(texbox_result.Text.Length>0)
            {
                string str = texbox_result.Text;
                str = str.Substring(0, str.Length - 1);
                texbox_result.Text = str;
            }
        }

        private void btn_clear_Click(object sender, EventArgs e)
        {
            texbox_result.Text = "";
            m_listString.Clear();
            m_colStack.Clear();
        }

        private void btn_dot_Click(object sender, EventArgs e)
        {
            if (texbox_result.Text.Length > 0)
            {
                string s = texbox_result.Text;
                s = s[s.Length - 1].ToString();
                if (s == "*" || s == "/" || s == "+" || s == "-" || s == ".")
                {
                    texbox_result.Text = texbox_result.Text.Substring(0, texbox_result.Text.Length - 1);
                    //texbox_result.Text += "-";
                }

            }
            texbox_result.Text += ".";
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            texbox_result.Text += "(";
        }

        private void btn_close_Click(object sender, EventArgs e)
        {
            texbox_result.Text += ")";
        }

        //마우스 올려놓으면 색깔 변경
        private void btn_backspace_MouseEnter(object sender, EventArgs e)
        {
            Button b = sender as Button;
            if (b == null) return;
            b.ForeColor = Color.Aqua;
        }
        private void btn_backspace_MouseLeave(object sender, EventArgs e)
        {
            Button b = sender as Button;
            if (b == null) return;
            b.ForeColor = Color.Black;
        }

        //키입력은 포커스 설정후 속성에 KetDown에 이벤트를 가져오면됨
    }
}
