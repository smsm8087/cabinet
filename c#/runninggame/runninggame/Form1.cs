using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;

namespace RunGame
{
    public partial class Form1 : Form
    {
        Bitmap bg_image = new Bitmap("bgimage.bmp");
        // Bitmap c_image = new Bitmap("playerrun.gif");
        // FrameDimension dimension = new FrameDimension(c_image.FrameDimensionsList[0]);
        bool landed = false;
        float gravity = 2.0f;
        float speed = 0;
        int score = 0;
        int posx=15;
        int posy=480;
        int platformspeed = 50;

        Random rnd = new Random();
        public Form1()
        {
            InitializeComponent();

            DoubleBuffered = true;
            //timer1.Start();
        }
        //void Update()
        //{



        //}
        TextureBrush mi = null;

        protected override void OnPaint(PaintEventArgs e)
        {
            //ImageAnimator.UpdateFrames();
            //e.Graphics.DrawImage(player.Image, posx, posy, 45, 48);

            base.OnPaint(e);
            if (mi == null)
            {
                mi = new TextureBrush(bg_image);
                mi.WrapMode = System.Drawing.Drawing2D.WrapMode.TileFlipXY;
            }
            Matrix m = new Matrix();
            m.Translate(-1, 0);
            //mi.Transform;
           mi.MultiplyTransform(m);

            Rectangle r = new Rectangle();
            r.Location = new Point(0, 0);
            r.Size = ClientSize;

            e.Graphics.DrawImage(bg_image, r);



            e.Graphics.FillRectangle(mi, 0, 0, ClientSize.Width, ClientSize.Height);

          

        }
        private void ui_tmrTick_Tick(object sender, EventArgs e)
        {

            speed += gravity;
            //c_image.Height += (int)speed;
            player.Top += (int)speed;
            player.Left = 80;
            label1.Text = "Score : " + score;

            foreach (Control x in this.Controls)
            {
                if (x is PictureBox && x.Tag == "Platform")
                {
                    x.Left -= platformspeed;
                    if (x.Left < -500)
                    {
                        x.Width = rnd.Next(300, 500);
                        x.Left = rnd.Next(500,1300);
                        score += 2;
                    }
                }


            }
            foreach (Control y in this.Controls)
            {
                if (y is PictureBox && y.Tag == "coin")
                {
                    y.Left -= platformspeed;
                    if (y.Left < -1200)
                    {
                        y.Width = rnd.Next(100, 100);
                        y.Left = rnd.Next(500,900);
                    }
                }
            }
            if (player.Bounds.IntersectsWith(p2.Bounds) ||
                player.Bounds.IntersectsWith(p1.Bounds))
            {
                landed = true;
                speed = 0.0f;
                player.Top = p2.Top - player.Height;
                //player.Image = Properties.Resources.batman_1;
                coin.Show();
                coin2.Show();

            }

            if (player.Bounds.IntersectsWith(coin.Bounds))
            {
                score += 5;
                coin.Hide();
            }
            if (player.Bounds.IntersectsWith(coin2.Bounds))
            {
                score += 5;
                coin2.Hide();
            }
            if (player.Top < -40 || player.Top > ClientSize.Height)
            {
                timer1.Stop();
                label1.Text = "GAME OVER 다시 시작하시려면 R키를 누르세요";
                label2.Text = "";
               
            }
            if(score >=100&& score<150)
            {
                platformspeed = 50;
                label2.Text = "<SPEED UP>";
            }
            if(score>=150 && score < 200)
            {
                label2.Text = "";
            }
            if (score >= 300 && score < 350)
            {
                platformspeed = 80;
                label2.Text = "<SPEED UP>";
            }
            if (score >= 350 && score < 500)
            {
                label2.Text = "";
            }
            if (score >= 500 && score < 550)
            {
                platformspeed = 120;
                label2.Text = "<FULL SPEED UP>";
            }
            if (score >= 750)
            {
                label2.Text = "";
            }

            Invalidate();
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space && landed == true)
            {
                speed = -30;

                landed = false;
            }
            if (e.KeyCode == Keys.R)
            {
                reset();
            }
        }

        private void reset()
        {
            platformspeed = 30;
            speed = 0;
            score = 0;
            p1.Width = 438;
            p2.Width = 438;


            player.Left = 15;
            player.Top = 480;

            p1.Left = 12;
            p1.Top = 520;

            p2.Left = 858;
            p2.Top = 520;

            coin2.Left = 977;
            coin2.Top = 250;

            coin.Left = 179;
            coin.Top = 250;

            timer1.Start();
        }

       
    }
    //protected override void OnLoad(EventArgs e)
    //{
    //    ImageAnimator.Animate(player.Image, new EventHandler(this.OnFrameChanged));
    //    base.OnLoad(e);
    //}
    //private void OnFrameChanged(object o, EventArgs e)
    //{
    //    this.Invalidate();
    //}


}
