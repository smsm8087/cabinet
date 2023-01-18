using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AnimTool
{
    public partial class MainForm : Form
    {
        //bool transparentColorEdit = false;

        private Color transparentColor;
        public Color TransparentColor
        {
            get
            {
                return transparentColor;
            }
            set
            {
                transparentColor = value;
                ui_pnTransParentColor.BackColor = value;
            }
        }

        public MainForm()
        {
            InitializeComponent();
            transparentColor = ui_pnTransParentColor.BackColor;
        }

        public void AddAnimGroup(string groupName)
        {
            ui_cbAnimGroup.Items.Add(groupName);
        }

        private void 파일_열기_Click(object sender, EventArgs e)
        {
            ui_dlgOpenFile.FileName = string.Empty;
            ui_dlgOpenFile.Filter = "Image Files (JPG,PNG,GIF,BMP)|*.JPG;*.PNG;*.GIF;*.BMP";
            DialogResult dr = ui_dlgOpenFile.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ui_ucEditPanel.EditImage = new Bitmap(ui_dlgOpenFile.FileName);
            }
        }

        private void ui_pnTransParentColor_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.Hand;
//            transparentColorEdit = true;
            ui_ucEditPanel.TransparentColorEdit = true;
        }

        private void 시작ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(ui_cbAnimGroup.SelectedItem == null)
            {
                MessageBox.Show("선택된 애니매이션 그룹이 없습니다.");
                return;
            }
            ui_ucAnimPanel.StartAnim(ui_ucEditPanel.GetAnimGroup(ui_cbAnimGroup.SelectedItem.ToString()));
        }

        private void 정지ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ui_ucAnimPanel.StopAnim();
        }

        private void ui_trAnimInterval_ValueChanged(object sender, EventArgs e)
        {
            ui_ucAnimPanel.SetAnimInterval(ui_trAnimInterval.Value / 10.0f);
        }

        private void ui_rbFrameSelect_CheckedChanged(object sender, EventArgs e)
        {
            ui_ucEditPanel.EditMode = EditPanel.eEditMode.E_FRAME_SELECT;
        }

        private void ui_rbGroup_CheckedChanged(object sender, EventArgs e)
        {
            ui_ucEditPanel.EditMode = EditPanel.eEditMode.E_GROUP_SELECT;
        }

        private void 저장ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            if(dlg.ShowDialog() == DialogResult.OK)
            {
                ui_ucEditPanel.SaveToFile(dlg.FileName);
            }
        }
    }
}
