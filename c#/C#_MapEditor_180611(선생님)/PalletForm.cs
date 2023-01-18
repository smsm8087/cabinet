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
    public partial class PalletForm : Form
    {
        PalletInner palletInner = null;

        public PalletForm()
        {
            InitializeComponent();

            palletInner = new PalletInner();
            palletInner.Parent = this;
            Point p = new Point(0, ui_msPallet.Size.Height);
            palletInner.Location = p;

            IniFile iniFile = new IniFile();
            if(iniFile.KeyExists("Image"))
            {
                string path = iniFile.Read("Image");
                palletInner.PalletImage = new Bitmap(path);
            }

            Const.TileSizeChange += new EventHandler(OnChangeTileSize);
        }

        protected void OnChangeTileSize(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void 열기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog d = new OpenFileDialog();
            d.ShowDialog();

            if (palletInner == null) return;
            palletInner.PalletImage = new Bitmap(d.FileName);
            Size s = ClientSize;
            s.Width = palletInner.Width;
            ClientSize = s;
            IniFile iniFile = new IniFile();
            iniFile.Write("Image", d.FileName);
            Invalidate();
        }
        
        private void PalletForm_Paint(object sender, PaintEventArgs e)
        {
            palletInner.Invalidate();

            Size s = ClientSize;
            s.Width = palletInner.Width;
            ClientSize = s;
        }

        private void 타일사이즈ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TileSizeForm f = new TileSizeForm();
            DialogResult dr = f.ShowDialog();
            if(dr == DialogResult.OK)
            {
                Invalidate();
            }
        }

        private void PalletForm_MouseDown(object sender, MouseEventArgs e)
        {
            Invalidate();
        }
    }
}
