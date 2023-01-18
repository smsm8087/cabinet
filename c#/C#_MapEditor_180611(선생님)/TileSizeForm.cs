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
    public partial class TileSizeForm : Form
    {
        public TileSizeForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Const.TileSize = int.Parse(textBox1.Text);
            DialogResult = DialogResult.OK;
        }
    }
}
