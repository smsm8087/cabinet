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
    public partial class PalletInner : UserControl
    {
        Point selectedItem = new Point(0, 0);
        Pen pen = new Pen(Color.Red);
        Rectangle rect = new Rectangle();
        Bitmap palletImage = null;
        //public Bitmap 
        public Bitmap PalletImage
        {
            get
            {
                return palletImage;
            }
            set
            {
                Size = value.Size;
                palletImage = value;
                Invalidate();
            }
        }

        public PalletInner()
        {
            InitializeComponent();

            DoubleBuffered = true;
        }

        private void PalletInner_Paint(object sender, PaintEventArgs e)
        {
            if (palletImage == null) return;

            ClientSize = palletImage.Size;

            e.Graphics.DrawImage(palletImage, 0, 0);

            if (Const.TileSize == 0) return;

            pen.Color = Color.White;
            pen.Width = 1;
            int row = palletImage.Size.Height / Const.TileSize;
            int col = palletImage.Size.Width / Const.TileSize;

            // 가로줄
            Point p1 = new Point(0, 0);
            Point p2 = new Point(palletImage.Width, 0);
            for (int i = 0; i < row; i++)
            {
                p1.Y = i * Const.TileSize;
                p2.Y = p1.Y;
                e.Graphics.DrawLine(pen, p1, p2);
            }

            // 세로줄
            p1.X = 0; p1.Y = 0;
            p2.X = 0; p2.Y = palletImage.Height;
            for (int i = 0; i < col; i++)
            {
                p1.X = i * Const.TileSize;
                p2.X = p1.X;
                e.Graphics.DrawLine(pen, p1, p2);
            }

            // 선택된 타일 사각형
            pen.Color = Color.Red;
            pen.Width = 3;

            rect.X = selectedItem.X * Const.TileSize;
            rect.Y = selectedItem.Y * Const.TileSize;
            rect.Width = Const.TileSize;
            rect.Height = Const.TileSize;

            e.Graphics.DrawRectangle(pen, rect);
        }

        private void PalletInner_MouseDown(object sender, MouseEventArgs e)
        {
            if (Const.TileSize == 0) return;
            selectedItem.X = e.X / Const.TileSize;
            selectedItem.Y = e.Y / Const.TileSize;
            Invalidate();
        }
    }
}
