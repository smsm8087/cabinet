using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _2D_Game_Tool.myPanel;
using System.IO;


namespace _2D_Game_Tool.Forms
{
	public partial class Form_FloorIndexSetting : Form
	{

		private Image img = null;
		private MyPanels imgView;
		struct MapIndexInfo
		{
			public Point pt;
			public int nIndex;
			public string str;
		};

		List<MapIndexInfo> m_listInfo;

		public Form_FloorIndexSetting(string _str)
		{
			InitializeComponent();

			BackColor = Color.Gray;

			img = Image.FromFile(_str);
			imgView = new MyPanels(_str, new Point(0,0));
			imgView.Parent = this;

			DoubleBuffered = true;
			Size = new Size(imgView.Width + 100,imgView.Height + 100);
			timer1.Start();

			btn_Save.Location = new Point(imgView.Location.X  + imgView.Size.Width , imgView.Location.Y );
			btn_Close.Location = new Point(imgView.Location.X  + imgView.Size.Width , imgView.Location.Y + 25);
			btn_Load.Location = new Point(imgView.Location.X + imgView.Size.Width , imgView.Location.Y + 50);

			m_listInfo = new List<MapIndexInfo>();
			for ( int i = 0; i < img.Width/32; i++)
			{
				for( int j = 0; j < img.Height/32; j++)
				{
					MapIndexInfo item = new MapIndexInfo();
					item.pt = new Point(i, j);
					item.nIndex = 0;
					item.str = item.nIndex.ToString();
					m_listInfo.Add(item);
				}
			}


			timer1.Start();
		}


		private void timer1_Tick(object sender, EventArgs e)
		{
			imgView.Invalidate();


		}

		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaint(e);

			foreach(var item in m_listInfo)
			{

				Font font = DefaultFont;
				Brush brush = new SolidBrush(Color.Black);
				PointF pointF = new PointF(item.pt.X *32, item.pt.Y * 32);
				e.Graphics.DrawString(item.str,font,brush,pointF);
			}
		}

		private void btn_Save_Click(object sender, EventArgs e)
		{
			string path = @"D:\Sources\2D Game Tool\2D Game Tool\bin\Release\map1InfoData.txt";
			
			using (StreamWriter sw = File.CreateText(path))
			{
				sw.Write((img.Width / 32).ToString());
				sw.WriteLine();
				sw.Write((img.Height/32).ToString());
				sw.WriteLine();
				foreach(var items in m_listInfo)
				{
					sw.Write(items.str);
					sw.WriteLine();
				}
			}
			Close();
		}

		private void btn_Close_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void btn_Load_Click(object sender, EventArgs e)
		{
			m_listInfo.Clear();

			string path = @"D:\Sources\2D Game Tool\2D Game Tool\bin\Release\map1InfoData.txt";

			if( File.Exists(path))
			{
				using (StreamReader sr = File.OpenText(path))
				{
					string s = "";
					s = sr.ReadLine();
					int nX = int.Parse(s);
					s = sr.ReadLine();
					int nY = int.Parse(s);

					for (int i = 0; i < nX; i++)
					{
						for (int j = 0; j < nY; j++)
						{
							s = sr.ReadLine();
							MapIndexInfo item = new MapIndexInfo();
							item.pt = new Point(i, j);
							item.nIndex = int.Parse(s);
							item.str = item.nIndex.ToString();
							m_listInfo.Add(item);
						}
					}
				}
			}
			Select();
		}

		bool bFlag = false;
		private void btn_Load_MouseDown(object sender, MouseEventArgs e)
		{
			bFlag = true;
			Select();
		}

		private void btn_Load_MouseUp(object sender, MouseEventArgs e)
		{
			if (bFlag == false) return;

			Point pt = new Point(e.Location.X / 32, e.Location.Y / 32);
			for (int i = 0; i < m_listInfo.Count; i++)
			{
				if( pt.X == m_listInfo[i].pt.X && pt.Y == m_listInfo[i].pt.Y)
				{
					MapIndexInfo mii = m_listInfo[i];
					mii.nIndex++;
					mii.str = mii.nIndex.ToString();
					m_listInfo[i] = mii;
				}
			}
			Select();
		}

		private void btn_Load_MouseMove(object sender, MouseEventArgs e)
		{
			bFlag = false;
		}
	}
}
