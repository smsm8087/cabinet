using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace MapEditer
{

    public partial class Form1 : Form
    {
        //List<Rectangle> imagelist = new List<Rectangle>();
       
        
        int row;
        int col;
        int tilesize = 32;
        bool isselected = false;
        int Count = 0;
        int mapcount = 0;
        int OB = -1;
        int lstcount = 0;
        Bitmap b_image = new Bitmap("tilemap.bmp");
        List<Point> lstselected = new List<Point>();
        Pen pen = new Pen(Color.Black);
        Rectangle rect = new Rectangle();
        Rectangle rectsource = new Rectangle();
        Point selectedItem = new Point();
        Point mouse = new Point();
        st temp = new st();
        public Form1()
        {
            InitializeComponent();
            WindowState = FormWindowState.Maximized;
            //Invalidate();
        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            
            //Form1.Size = new Size(b_image.Size.Width + 25, b_image.Size.Height + 25);
        }

        private void ui_panel_Paint(object sender, PaintEventArgs e)
        {

           
            pen.Color = Color.Black;
            Point p1 = new Point(0, 0);
            Point p2 = new Point(row* tilesize, 0);
            int resultrow = 0;
            int resultcol = 0;
            
            //가로줄5
            for (int i = 0; i < row+1; i++)
            {
                p1.Y = i * tilesize;
                p2.Y = p1.Y;
                resultrow += p1.Y;
                e.Graphics.DrawLine(pen, p1, p2);
            }

            
           // 세로줄
           p1.X = 0; p1.Y = 0;
            p2.X = 0; p2.Y = col* tilesize;
            for (int i = 0; i < col+1; i++)
            {
                p1.X = i * tilesize;
                p2.X = p1.X;
                resultcol += p2.X;
                e.Graphics.DrawLine(pen, p1, p2);
            }
            //resultrow += AutoScrollPosition.X;
            //resultcol += AutoScrollPosition.Y;
            ui_panel.AutoScrollMinSize = new Size(resultrow, resultcol);
            //ui_panel.Size = new Size(resultrow, resultcol);
            // 선택된 타일 사각형
            pen.Color = Color.Red;
            pen.Width = 3;

            rect.X = mouse.X * tilesize;
            rect.Y = mouse.Y * tilesize;
            rect.Width = tilesize;
            rect.Height = tilesize;

            e.Graphics.DrawRectangle(pen, rect);
            if (ListST != null)
            {
                for (int i = 0; i < ListST.Count; i++)
                {
                    if (ListST[i].bit == null)
                    {
                        //pen.Color = Color.Red;
                        //e.Graphics.DrawRectangle(pen, ListST[i].s_P.X, ListST[i].s_P.Y, tilesize, tilesize);
                        Brush b = new SolidBrush(Color.Black);
                        e.Graphics.FillRectangle(b, ListST[i].s_P.X, ListST[i].s_P.Y, tilesize, tilesize);
                    }
                    else
                    {
                        e.Graphics.DrawImage(ListST[i].bit, ListST[i].s_P.X, ListST[i].s_P.Y, tilesize, tilesize);
                    }
                   
                }
            }

            //ui_panel.Size = new Size(row * tilesize + AutoScrollPosition.X, col * tilesize + AutoScrollPosition.Y);

        }
        private void ui_panel_MouseMove(object sender, MouseEventArgs e)
        {
            mouse.X = e.X/ tilesize;
            mouse.Y = e.Y/ tilesize;
            //Invalidate();
        }



        private void timer1_Tick(object sender, EventArgs e)
        {
            ui_panel2.Invalidate();
            ui_panel.Invalidate();
        }

        private void ui_btn_ok_Click(object sender, EventArgs e)
        {
            row = int.Parse(ui_txt_row.Text);
            col = int.Parse(ui_txt_col.Text);
            //row = palletImage.Size.Height / Const.TileSize;
            //col = palletImage.Size.Width / Const.TileSize;
        }

       
     

        private void ui_panel2_Paint(object sender, PaintEventArgs e)
        {
            if (b_image == null) return;
            //ui_tabpage.Size.Width = b_image.Size.Width;
            
            ui_panel2.Size = new Size(b_image.Size.Width + 25, b_image.Size.Height + 25);
            e.Graphics.DrawImage(b_image, 0, 0);

            // 선택된 타일 사각형
            pen.Color = Color.Red;
            pen.Width = 3;

            rectsource.X = selectedItem.X * tilesize;
            rectsource.Y = selectedItem.Y * tilesize;
            rectsource.Width = tilesize;
            rectsource.Height = tilesize;

            e.Graphics.DrawRectangle(pen, rectsource);
        }

      

        private void ui_panel_MouseClick(object sender, MouseEventArgs e)
        {
            if (null != bitmap2)
            {
                Count++;
                st tmp;
                tmp.s_P = Point.Empty;
                tmp.s_P.X = mouse.X * tilesize;
                tmp.s_P.Y = mouse.Y * tilesize;
                tmp.bit = (Bitmap)bitmap2.Clone();
                tmp.TileCount = Count;
                //tmp.OB = OB;
                ListST.Add(tmp);
                mapcount++;
            }
        }

        Bitmap bitmap2 = null;
        private void ui_panel2_MouseClick(object sender, MouseEventArgs e)
        {
           
            bitmap2 = b_image.Clone(Rectangle.FromLTRB(selectedItem.X * tilesize, selectedItem.Y * tilesize, (selectedItem.X * tilesize) + 32, (selectedItem.Y * tilesize) + 32), System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            lstselected.Add(selectedItem);
            lstcount++;
        }

        struct st
        {
            public Bitmap bit;
            public Point s_P;
            public int TileCount;
            //public int OB;
        };
        List<st> ListST = new List<st>();

        private void ui_panel2_MouseMove(object sender, MouseEventArgs e)
        {
            selectedItem.X = e.X / tilesize;
            selectedItem.Y = e.Y / tilesize;
        }

        private void Save_Click(object sender, EventArgs e)
        {
            StreamWriter sw = new StreamWriter("data.txt");

            
            sw.WriteLine(tilesize);
            sw.WriteLine(row);
            sw.WriteLine(col);
            sw.WriteLine(mapcount);
            //sw.WriteLine(lstcount);
            //foreach (var image in lstselected)
            //{
            //    sw.WriteLine(image.X);
            //    sw.WriteLine(image.Y);
            //}
            foreach (var item in ListST)
            {
               
                sw.WriteLine(item.s_P.X/tilesize);
                sw.WriteLine(item.s_P.Y/tilesize);
                //sw.WriteLine(item.OB);
            }
            sw.Close();
        }
        
        private void 로드ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ListST.Clear();
            //Bitmap bitTemp = null;
            StreamReader sr = new StreamReader("data.txt");
            List<st> lstTemp = new List<st> ();
            //Point pt = new Point(0, 0);
            //List<Point> lstPoint = new List<Point>();
            //Graphics g = CreateGraphics();
            //bitTemp = b_image.Clone(Rectangle.FromLTRB(selectedItem.X * tilesize, selectedItem.Y * tilesize, (selectedItem.X * tilesize) + 32, (selectedItem.Y * tilesize) + 32), System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            tilesize = int.Parse(sr.ReadLine());
            row = int.Parse(sr.ReadLine());
            col = int.Parse(sr.ReadLine());
            mapcount = int.Parse(sr.ReadLine());
            //lstcount = int.Parse(sr.ReadLine());
            //for (int i = 0; i < lstcount; i++)
            //{
            //    pt.X = int.Parse(sr.ReadLine());
            //    pt.Y = int.Parse(sr.ReadLine());
            //    lstPoint.Add(pt);
            //}
                //    bitTemp = b_image.Clone(Rectangle.FromLTRB
                // (pt.X * tilesize,
                // pt.Y * tilesize,
                // (pt.X * tilesize) + 32,
                // (pt.Y * tilesize) + 32),
                // System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                //}

            for (int i =0; i < mapcount; i++)
            {
               //temp.bit = bitTemp;
                
                temp.s_P.X = int.Parse(sr.ReadLine())*tilesize;
                temp.s_P.Y = int.Parse(sr.ReadLine())*tilesize;
                //temp.OB = int.Parse(sr.ReadLine());
                lstTemp.Add(temp);
            }
            ListST = lstTemp;

            ui_panel.Invalidate();
        }
    }
}
