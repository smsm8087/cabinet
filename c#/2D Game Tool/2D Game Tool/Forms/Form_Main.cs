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
using _2D_Game_Tool.Forms;


namespace _2D_Game_Tool
{
	public partial class Form_Main : Form
	{
		MyPanels Panel_Preview = null;
		MyPanels Panel_Map = null;
		string strTileName = "";

		public Form_Main()
		{
			InitializeComponent();
			WindowState = FormWindowState.Maximized;

		}

		private void MapEditor_Load(object sender, EventArgs e)
		{
			strTileName = "../Release/Graphics/Tilesets/002-Woods01.png";
			Panel_Preview = new MyPanels(strTileName, new Point(5, 5 + menuStrip1.Size.Height), this);
			Panel_Preview.Name = "Preview";

			Panel_Map = new MyPanels(strTileName, new Point(Panel_Preview.Location.X + Panel_Preview.Size.Width + 10, Panel_Preview.Location.Y), this, new Point(20, 15));
			Panel_Map.Name = "mapView";

			ToolTipSetting();
			DoubleBuffered = true;

			Image img = Image.FromFile(strTileName);

			timer1.Start();
		}

		private void ToolTipSetting()
		{
			myTooltip.SetToolTip(Panel_Preview, "타일을 선택하십쇼");
			
		}


		protected override void OnResize(EventArgs e)
		{

		}

		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaint(e);
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			Panel_Preview.Invalidate();
			Panel_Map.Invalidate();
		}

		public Point GetSelectPrev()
		{
			return Panel_Preview.SelectTileNum;
		}

		private void ui_Tool_Menu_FloorIndex_Setting_Click(object sender, EventArgs e)
		{
			Form_FloorIndexSetting ffis = new Form_FloorIndexSetting(strTileName);
			ffis.ShowDialog();
		}

		private void saveToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Panel_Map.SaveMapData();
		}

		private void loadToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Panel_Map.LoadMapData();
		}
	}
}