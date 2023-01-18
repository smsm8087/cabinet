using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.IO;

namespace AnimTool
{
    public partial class EditPanel : UserControl
    {
        public enum eEditMode
        {
            E_FRAME_SELECT,
            E_GROUP_SELECT
        }

        public eEditMode EditMode { get; set; }

        private bool selectMode = false;
        private Point selectStartPoint;
        private Point selectFinishPoint;

        AnimFrame selectedAnimFrame = null;
        List<AnimFrame> animFrame = new List<AnimFrame>();
        Dictionary<string, AnimGroup> animGroup = new Dictionary<string, AnimGroup>();

        public bool TransparentColorEdit { get; set; }

        protected Bitmap editImage;
        public Bitmap EditImage
        {
            get
            {
                return editImage;
            }
            set
            {
                editImage = value;
                Invalidate();
            }
        }

        public EditPanel()
        {
            InitializeComponent();

            DoubleBuffered = true;

            ui_tmrTick.Start();
        }

        public AnimGroup GetAnimGroup(string groupName)
        {
            animGroup[groupName].AnimFrames.Sort((a, b) => a.FrameNo > b.FrameNo ? 1 : -1);
            foreach (AnimFrame af in animGroup[groupName].AnimFrames)
            {
                af.FrameImage = editImage.Clone(af.FrameRect, editImage.PixelFormat);
            }
            return animGroup[groupName];
        }

        public void SaveToFile(string path)
        {
            StreamWriter file = new StreamWriter(path);

            foreach (var ag in animGroup)
            {
                ag.Value.SaveToFile(file);
            }

            file.Close();
        }

        private void EditPanel_Paint(object sender, PaintEventArgs e)
        {
            if (editImage != null)
            {
                e.Graphics.DrawImage(editImage, 0, 0);
            }

            using (Pen p = new Pen(Color.Black))
            {
                if(selectMode)
                {
                    Rectangle r = Rectangle.FromLTRB(
                        Math.Min(selectStartPoint.X, selectFinishPoint.X),
                        Math.Min(selectStartPoint.Y, selectFinishPoint.Y),
                        Math.Max(selectStartPoint.X, selectFinishPoint.X),
                        Math.Max(selectStartPoint.Y, selectFinishPoint.Y));

                    p.DashStyle = DashStyle.Dot;
                    e.Graphics.DrawRectangle(p, r);
                }

                using (Font f = new Font("Arial", 16))
                {
                    using (SolidBrush bb = new SolidBrush(Color.Black),
                        wb = new SolidBrush(Color.Wheat))
                    {
                        foreach (var af in animFrame)
                        {

                            Rectangle rc = af.FrameRect;
                            rc.Y -= 25;
                            rc.Height = 25;
                            rc.Width = (int)(rc.Width * 0.8f);
                            e.Graphics.FillRectangle(bb, rc);
                            e.Graphics.DrawString("#" + af.FrameNo, f, wb, rc.Location);

                            p.DashStyle = DashStyle.Dot;
                            e.Graphics.DrawRectangle(p, af.FrameRect);
                        }

                        foreach(var ag in animGroup)
                        {
                            Rectangle rc = ag.Value.GroupRect;
                            rc.Y = rc.Bottom - 25;
                            rc.Height = 25;
                            rc.Width = 200;
                            e.Graphics.FillRectangle(wb, rc);
                            e.Graphics.DrawString(ag.Value.GroupName, f, bb, rc.Location);


                            e.Graphics.DrawRectangle(p, ag.Value.GroupRect);
                        }
                    }
                }

            }
        }

        private void EditPanel_MouseDown(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left)
            {
                if (TransparentColorEdit)
                {
                    Cursor = Cursors.Default;
                    TransparentColorEdit = false;
                }
                else
                {
                    selectMode = true;
                    selectStartPoint = e.Location;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                selectedAnimFrame = null;

                foreach (AnimFrame af in animFrame)
                {
                    if(af.FrameRect.Contains(e.Location))
                    {
                        selectedAnimFrame = af;
                        break;
                    }
                }

                if(selectedAnimFrame != null)
                {
                    ui_cmRightMenu.Show(this, e.Location);
                }
            }
        }

        private void FrameSelect()
        {
            try
            {
                Rectangle r = Rectangle.FromLTRB(
                                Math.Min(selectStartPoint.X, selectFinishPoint.X),
                                Math.Min(selectStartPoint.Y, selectFinishPoint.Y),
                                Math.Max(selectStartPoint.X, selectFinishPoint.X),
                                Math.Max(selectStartPoint.Y, selectFinishPoint.Y));

                int left = 0, top = 0, right = 0, bottom = 0;

                if (r.Bottom >= editImage.Height)
                {
                    r.Height -= (r.Bottom - editImage.Height);
                    r.Height -= 1;
                }

                MainForm f = ParentForm as MainForm;
                for (int i = r.Left; i < r.Right; ++i)
                {
                    bool isAllTransparent = true;
                    for (int j = r.Top; j < r.Bottom; ++j)
                    {
                        if (f.TransparentColor.ToArgb() != editImage.GetPixel(i, j).ToArgb())
                        {
                            isAllTransparent = false;
                            left = i - 1;
                            break;
                        }
                    }
                    if (!isAllTransparent) break;
                }

                for (int i = r.Right; i > r.Left; --i)
                {
                    bool isAllTransparent = true;
                    for (int j = r.Top; j < r.Bottom; ++j)
                    {
                        if (f.TransparentColor.ToArgb() != editImage.GetPixel(i, j).ToArgb())
                        {
                            isAllTransparent = false;
                            right = i + 1;
                            break;
                        }
                    }
                    if (!isAllTransparent) break;
                }


                for (int i = r.Top; i < r.Bottom; ++i)
                {
                    bool isAllTransparent = true;
                    for (int j = r.Left; j < r.Right; ++j)
                    {
                        if (f.TransparentColor.ToArgb() != editImage.GetPixel(j, i).ToArgb())
                        {
                            isAllTransparent = false;
                            top = i - 1;
                            break;
                        }
                    }
                    if (!isAllTransparent) break;
                }

                for (int i = r.Bottom; i > r.Top; --i)
                {
                    bool isAllTransparent = true;
                    for (int j = r.Left; j < r.Right; ++j)
                    {
                        if (f.TransparentColor.ToArgb() != editImage.GetPixel(j, i).ToArgb())
                        {
                            isAllTransparent = false;
                            bottom = i + 1;
                            break;
                        }
                    }
                    if (!isAllTransparent) break;
                }

                r.X = left;
                r.Y = top;
                r.Width = right - left;
                r.Height = bottom - top;

                if (r.Width > 0 && r.Height > 0)
                {
                    AnimFrame af = new AnimFrame();
                    af.FrameRect = r;
                    af.Pivot = new PointF(0.5f, 0.5f);
                    af.FrameNo = animFrame.Count() + 1;
                    animFrame.Add(af);
                }
            }
            catch (Exception ex)
            {
            }
        }

        private void GroupSelect()
        {
            Rectangle r = Rectangle.FromLTRB(
                                Math.Min(selectStartPoint.X, selectFinishPoint.X),
                                Math.Min(selectStartPoint.Y, selectFinishPoint.Y),
                                Math.Max(selectStartPoint.X, selectFinishPoint.X),
                                Math.Max(selectStartPoint.Y, selectFinishPoint.Y));


            List<AnimFrame> lst = new List<AnimFrame>();
            foreach(AnimFrame af in animFrame)
            {
                if(r.IntersectsWith(af.FrameRect))
                {
                    lst.Add(af);
                }
            }

            r = Rectangle.FromLTRB(int.MaxValue, int.MaxValue, 0, 0);
            foreach (AnimFrame af in animFrame)
            {
                if(af.FrameRect.Left < r.Left)
                {
                    r.X = af.FrameRect.X;
                }
                if (af.FrameRect.Top < r.Top)
                {
                    r.Y = af.FrameRect.Y;
                }
                if (r.Right < af.FrameRect.Right)
                {
                    r.Width = af.FrameRect.Right - r.Left;
                }
                if (r.Bottom < af.FrameRect.Bottom)
                {
                    r.Height = af.FrameRect.Bottom - r.Top;
                }
            }

            if (lst.Count() > 0)
            {
                AnimGroup ag = new AnimGroup();

                InputGroupNameForm f = new InputGroupNameForm();
                if (f.ShowDialog() == DialogResult.OK)
                {
                    ag.GroupName = f.GroupName;
                    ag.AnimFrames = lst;
                    ag.GroupRect = r;
                    animGroup.Add(f.GroupName, ag);
                    MainForm mf = ParentForm as MainForm;
                    mf.AddAnimGroup(f.GroupName);
                }
            }
        }

        private void EditPanel_MouseUp(object sender, MouseEventArgs e)
        {
            try
            {
                if (selectMode && editImage != null)
                {
                    selectMode = false;
                    selectFinishPoint = e.Location;

                    if (EditMode == eEditMode.E_FRAME_SELECT)
                    {
                        FrameSelect();
                    }
                    else if (EditMode == eEditMode.E_GROUP_SELECT)
                    {
                        GroupSelect();
                    }
                }
            }

            catch (Exception ex)
            {
            }
        }

        private void EditPanel_MouseMove(object sender, MouseEventArgs e)
        {
            selectFinishPoint = e.Location;

            if (TransparentColorEdit)
            {
                MainForm f = ParentForm as MainForm;
                if (f != null && editImage != null)
                {
                    f.TransparentColor = editImage.GetPixel(e.X, e.Y);
                }
            }
        }

        private void ui_tmrTick_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void 이름입력ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 피벗포인트설정ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (selectedAnimFrame == null)
            {
                MessageBox.Show("선택된 애니매이션 프레임이 없습니다.");
                return;
            }

            SetPivotForm f = new SetPivotForm(selectedAnimFrame.Pivot);
            if (f.ShowDialog() == DialogResult.OK)
            {
                selectedAnimFrame.Pivot = f.Pivot;
                selectedAnimFrame = null;
            }
        }

        private void 프레임번호ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (selectedAnimFrame == null)
            {
                MessageBox.Show("선택된 애니매이션 프레임이 없습니다.");
                return;
            }

            SetFrameNoForm f = new SetFrameNoForm();
            if (f.ShowDialog() == DialogResult.OK)
            {
                selectedAnimFrame.FrameNo = f.FrameNo;
                selectedAnimFrame = null;
            }

        }
    }
}
