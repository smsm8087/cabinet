using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AnimTool
{
    public partial class SetPivotForm : Form
    {
        public PointF Pivot
        {
            get
            {
                float x = trackBar1.Value / 100.0f;
                float y = trackBar2.Value / 100.0f;
                return new PointF(x, y);
            }
        }

        public SetPivotForm(PointF p)
        {
            InitializeComponent();

            trackBar1.Value = (int)(p.X * 100);
            trackBar2.Value = (int)(p.Y * 100);
            label1.Text = "X : " + (trackBar1.Value / 100.0f).ToString();
            label2.Text = "Y : " + (trackBar2.Value / 100.0f).ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label1.Text = "X : " + (trackBar1.Value / 100.0f).ToString();
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label2.Text = "Y : " + (trackBar2.Value / 100.0f).ToString();
        }
    }
}

