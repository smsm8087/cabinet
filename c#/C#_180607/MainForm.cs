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
    public partial class MainForm : Form
    {
        string[] m_aButtonText = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "+", "-", "*", "/", "(", ")", "←", "C", "=" };
        public MainForm()
        {
            InitializeComponent();

            DoubleBuffered = true;

            ui_lbCalc.Text = "-0.5-0.9+5.5*(33+55)*(55-33*(1.5-20)-10)+(-30-(-10))";

            ui_tmrTick.Start();
            //ui_tmrTick.Stop()
            Button b = null;
            
            for(int i = 0; i < m_aButtonText.Length; ++i)
            {
                int nRow = i / 4;
                int nCol = i % 4;
                b = new Button();
                b.Location = new System.Drawing.Point(5 + nRow * 35, 50 + nCol * 35);
                b.Name = m_aButtonText[i];
                b.Size = new System.Drawing.Size(30, 30);
                b.TabIndex = 0;
                b.Text = m_aButtonText[i];
                b.UseVisualStyleBackColor = true;
                b.Parent = this;
                b.Click += new EventHandler(OnButtonClick);
            }
            int w = 20 + (m_aButtonText.Length / 4) * 35;
            int h = 50 + (m_aButtonText.Length / 4) * 35 + 5;
            //Size = new Size(w, h);
            ui_lbCalc.Size = new Size((m_aButtonText.Length / 4) * 35 - 5, ui_lbCalc.Size.Height); 
        }

        int OperatorPriority(string s)
        {
            if (s == "(" || s == ")") return 0;
            if (s == "+" || s == "-") return 1;
            if (s == "*" || s == "/") return 2;
            return -1;
        }

        void Calc()
        {
            string sIn = "(" + ui_lbCalc.Text + ")";
            string sOut = string.Empty;
            int n = 0;

            List<string> vecPostfix = new List<string>();
            Stack<string> stkOperator = new Stack<string>();

            while (GetToken(sIn, ref sOut, ref n))
            {
                //cout << sOut << endl;
                if (!IsOperator(sOut))
                {
                    vecPostfix.Add(sOut);
                }
                else
                {
                    if (sOut == "(")
                    {
                        stkOperator.Push(sOut);
                    }
                    else if (sOut == ")")
                    {
                        while (true)
                        {
                            string sTop = stkOperator.Pop();
                            
                            if (sTop == "(")
                            {
                                break;
                            }
                            vecPostfix.Add(sTop);
                        }
                    }
                    else
                    {
                        string sTop = stkOperator.Peek();
                        while (stkOperator.Any() &&
                            OperatorPriority(sTop) >= OperatorPriority(sOut))
                        {
                            stkOperator.Pop();
                            vecPostfix.Add(sTop);
                            sTop = stkOperator.Peek();
                        }
                        stkOperator.Push(sOut);
                    }
                }
            }

            while (stkOperator.Any())
            {
                vecPostfix.Add(stkOperator.Pop());
            }

            Stack<float> stkOperand = new Stack<float>();
            for (int i = 0; i < vecPostfix.Count; i++)
            {
                if (!IsOperator(vecPostfix[i]))
                {
                    stkOperand.Push(float.Parse(vecPostfix[i]));
                }
                else
                {
                    float f2 = stkOperand.Pop();
                    float f1 = stkOperand.Pop();
                    if (vecPostfix[i] == "+")
                    {
                        stkOperand.Push(f1 + f2);
                    }
                    else if (vecPostfix[i] == "-")
                    {
                        stkOperand.Push(f1 - f2);
                    }
                    else if (vecPostfix[i] == "*")
                    {
                        stkOperand.Push(f1 * f2);
                    }
                    else if (vecPostfix[i] == "/")
                    {
                        stkOperand.Push(f1 / f2);
                    }
                }
            }

            ui_lbCalc.Text = stkOperand.Pop().ToString();
        }


        bool IsOperator(string sIn)
        {
            if (sIn == "(" ||
                sIn == ")" ||
                sIn == "+" ||
                sIn == "-" ||
                sIn == "*" ||
                sIn == "/")
            {
                return true;
            }
            return false;
        }

        bool IsOperator(string sIn, ref int n)
        {
            if (sIn[n] == '(' ||
                sIn[n] == ')' ||
                sIn[n] == '+' ||
                sIn[n] == '*' ||
                sIn[n] == '/')
            {
                return true;
            }

            if (sIn[n] == '-')
            {
                if (sIn[n - 1] != '(')
                {
                    return true;
                }
            }
            return false;
        }

        bool GetToken(string sIn, ref string sOut, ref int n)
        {
            if (sIn.Length == n)
                return false;

            sOut = "";
            if (IsOperator(sIn, ref n))
            {
                sOut = sIn[n++].ToString();
                return true;
            }

            while (!IsOperator(sIn, ref n))
            {
                sOut += sIn[n++].ToString();
            }
            return true;
        }

        void OnButtonClick(object sender, EventArgs e)
        {
            Button b = sender as Button;
            if (b == null) return;
            List<string> lst = m_aButtonText.ToList();
            lst.RemoveRange(m_aButtonText.Length - 3, 3);
            if (lst.Contains(b.Text))
            {
                ui_lbCalc.Text += b.Text;
            }
            else if(b.Text == "←")
            {
                ui_lbCalc.Text = ui_lbCalc.Text.Remove(ui_lbCalc.Text.Length - 1);
            }
            else if (b.Text == "C")
            {
                ui_lbCalc.Text = string.Empty;
            }
            else if (b.Text == "=")
            {
                Calc();
            }
        }

        void Update() { }

        Image m_Image = Image.FromFile("spritesheet-demo.png");
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawImage(m_Image, 0, 0);
        }

        private void ui_tmrTick_Tick(object sender, EventArgs e)
        {
            Update();
            Invalidate();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            int aaa = 0;
        }
    }
}
