using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class MainForm : Form
    {
        PalletForm palletForm = null;

        public MainForm()
        {
            InitializeComponent();
            if (palletForm == null)
            {
                palletForm = new PalletForm();
            }
            palletForm.Show(this);

            IniFile iniFile = new IniFile();
            if(iniFile.KeyExists("MapWidth") && iniFile.KeyExists("MapHeight"))
            {
                int w = int.Parse(iniFile.Read("MapWidth"));
                int h = int.Parse(iniFile.Read("MapHeight"));
                tileMap.MapSize = new Size(w, h);
            }
        }

        private void 팔레트열기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(palletForm == null)
            {
                palletForm = new PalletForm();
            }
            palletForm.Show(this);
        }

        private void 맵크기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MapSizeForm f = new MapSizeForm();
            DialogResult dr = f.ShowDialog();
            if(dr == DialogResult.OK)
            {
                tileMap.MapSize = f.MapSize;
                tileMap.Invalidate();

                IniFile iniFile = new IniFile();
                iniFile.Write("MapWidth", tileMap.MapSize.Width.ToString());
                iniFile.Write("MapHeight", tileMap.MapSize.Height.ToString());
            }
        }
    }
}
