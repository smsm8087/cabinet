using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class TileMap : UserControl
    {
        public Size MapSize { get; set; }
        public PalletForm Pallet { get; set; }
        private Pen pen = new Pen(Color.White);

        public TileMap()
        {
            InitializeComponent();

            DoubleBuffered = true;
        }

        private void TileMap_Paint(object sender, PaintEventArgs e)
        {
            Size = new Size(MapSize.Width * Const.TileSize, MapSize.Height * Const.TileSize);

            pen.Color = Color.Black;
            pen.Width = 1;

            int row = MapSize.Width;
            int col = MapSize.Height;

            // 가로줄
            Point p1 = new Point(0, 0);
            Point p2 = new Point(Size.Width, 0);
            for (int i = 0; i < row; i++)
            {
                p1.Y = i * Const.TileSize;
                p2.Y = p1.Y;
                e.Graphics.DrawLine(pen, p1, p2);
            }

            // 세로줄
            p1.X = 0; p1.Y = 0;
            p2.X = 0; p2.Y = Size.Height;
            for (int i = 0; i < col; i++)
            {
                p1.X = i * Const.TileSize;
                p2.X = p1.X;
                e.Graphics.DrawLine(pen, p1, p2);
            }
        }

        private void TileMap_MouseDown(object sender, MouseEventArgs e)
        {
            if (Const.TileSize == 0) return;
            //selectedItem.X = e.X / Const.TileSize;
            //selectedItem.Y = e.Y / Const.TileSize;
            Invalidate();
        }
    }
}
