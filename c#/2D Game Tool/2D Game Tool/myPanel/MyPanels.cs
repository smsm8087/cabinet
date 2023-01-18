using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _2D_Game_Tool;
using System.IO;

namespace _2D_Game_Tool.myPanel
{
	class MyPanels : UserControl
	{
		public Point SelectTileNum;
		public Point MaxPos;
		string strFilePath;
		Image img = null;
		Form_Main myParent;

		private struct TileInfo
		{
			public bool bView;
			public int index;
			public int tileState;
			public Image img;
			public Point ptPos;
			public Point ptSelect;
		}

		List<TileInfo> lstTile;
		public MyPanels(string _path, Point _Pt)
		{
			InitializeComponent();
			img = Image.FromFile(_path);
			strFilePath = _path;
			BackgroundImage = img;
			Location = _Pt;                     // menustrip1
			Size = new Size(img.Width + 1, img.Height + 1);

			AutoScroll = true;
			DoubleBuffered = true;
		}

		public MyPanels(string _path, Point _Pt, Form_Main _parent)
		{
			InitializeComponent();
			img = Image.FromFile(_path);
			strFilePath = _path;
			BackgroundImage = img;
			Parent = _parent;
			myParent = _parent;
			Location = _Pt;                     // menustrip1
			Size = new Size(img.Width + 1, img.Height + 1);
			AutoScroll = true;
			DoubleBuffered = true;
		}
		public MyPanels(string _path, Point _Pt, Form_Main _parent, Point _MaxTileNum) // overloading
		{
			InitializeComponent();
			img = Image.FromFile(_path);
			strFilePath = _path;
			Location = _Pt;
			Parent = _parent;
			Size = new Size(32 * _MaxTileNum.X, 32 * _MaxTileNum.Y);
			BackColor = Color.White;
			MaxPos = _MaxTileNum;

			int n = 0;
			lstTile = new List<TileInfo>();

			for (int i = 0; i < _MaxTileNum.X; i++)
			{
				for (int j = 0; j < _MaxTileNum.Y; j++)
				{
					img = Image.FromFile(_path);
					TileInfo ti = new TileInfo();
					ti.bView = false;
					ti.img = img;
					ti.ptPos = new Point(i, j);
					ti.tileState = 0;
					ti.index = n;
					lstTile.Add(ti);
					n++;
				}
			}
			myParent = _parent;
			AutoScroll = true;
			DoubleBuffered = true;
		}


		private void InitializeComponent()
		{
			this.SuspendLayout();
			// 
			// MyPanels
			// 
			this.Name = "MyPanels";
			this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MyPanels_MouseDown);
			this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MyPanels_MouseUp);
			this.ResumeLayout(false);

		}

		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaint(e);

			Pen pen = new Pen(new SolidBrush(Color.Red));
			e.Graphics.DrawRectangle(pen, SelectTileNum.X * 32, SelectTileNum.Y * 32, 32, 32);

			if (lstTile == null) return;
			foreach (var item in lstTile)
			{
				if (item.bView == false) continue;
				e.Graphics.DrawImage(item.img, item.ptPos.X * 32, item.ptPos.Y * 32,
					new Rectangle(item.ptSelect.X * 32, item.ptSelect.Y * 32, 32, 32), GraphicsUnit.Pixel);
			}
		}
		private void MyPanels_MouseDown(object sender, MouseEventArgs e)
		{
			SelectTileNum.X = e.Location.X / 32;
			SelectTileNum.Y = e.Location.Y / 32;
			if ((((MyPanels)sender).Name) == "mapView")
			{
				Point pt = e.Location;
				pt.X = pt.X / 32;
				pt.Y = pt.Y / 32;

				for (int i = 0; i < lstTile.Count; i++)
				{
					if (pt.X == lstTile[i].ptPos.X && pt.Y == lstTile[i].ptPos.Y)
					{
						TileInfo ti = lstTile[i];
						ti.bView = true;
						ti.ptSelect = myParent.GetSelectPrev();
						lstTile[i] = ti;
						break;
					}
				}
			}
		}


		public void LoadMapData()
		{
			string s = @"D:\Sources\2D Game Tool\2D Game Tool\bin\Release\mapData1.txt";
			lstTile.Clear();

			if (File.Exists(s))
			{
				using (StreamReader sr = File.OpenText(s))
				{
					s = sr.ReadLine();
					Image backImg = Image.FromFile(s);

					s = sr.ReadLine();
					int nX = int.Parse(s);
					s = sr.ReadLine();
					int nY = int.Parse(s);

					for (int i = 0; i < nX; i++)
					{
						for (int j = 0; j < nY; j++)
						{
							TileInfo ti = new TileInfo();
							s = sr.ReadLine();
							ti.bView = bool.Parse(s);
							s = sr.ReadLine();
							ti.index = int.Parse(s);
							s = sr.ReadLine();
							ti.tileState = int.Parse(s);

							s = sr.ReadLine();
							ti.ptPos.X = int.Parse(s);
							s = sr.ReadLine();
							ti.ptPos.Y = int.Parse(s);

							s = sr.ReadLine();
							ti.ptSelect.X = int.Parse(s);
							s = sr.ReadLine();
							ti.ptSelect.Y = int.Parse(s);

							ti.img = backImg;
							lstTile.Add(ti);
						}
					}
				}
			}
		}

		public void SaveMapData()
		{
			string s = @"D:\Sources\2D Game Tool\2D Game Tool\bin\Release\mapData1.txt";
			using (StreamWriter sw = File.CreateText(s))
			{
				sw.Write(strFilePath);
				sw.WriteLine();
				sw.Write(MaxPos.X);
				sw.WriteLine();
				sw.Write(MaxPos.Y);
				sw.WriteLine();

				foreach (var items in lstTile)
				{
					sw.Write(items.bView.ToString());
					sw.WriteLine();
					sw.Write(items.index.ToString());
					sw.WriteLine();
					sw.Write(items.tileState.ToString());
					sw.WriteLine();
					sw.Write(items.ptPos.X.ToString());
					sw.WriteLine();
					sw.Write(items.ptPos.Y.ToString());
					sw.WriteLine();
					sw.Write(items.ptSelect.X.ToString());
					sw.WriteLine();
					sw.Write(items.ptSelect.Y.ToString());
					sw.WriteLine();
				}
			}
		}


		private void MyPanels_MouseUp(object sender, MouseEventArgs e)
		{
		}
	}
}
