using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace AnimTool
{
    public partial class AnimPanel : UserControl
    {
        int animIndex = 0;
        //List<AnimFrame> currentAnimList = null;
        AnimGroup animGroup = null;
        public AnimPanel()
        {
            InitializeComponent();
            DoubleBuffered = true; 
        }

        public void StartAnim(AnimGroup ag)
        {
            animGroup = ag;
            ui_tmrTick.Start();
            animIndex = 0;
        }

        public void StopAnim()
        {
            ui_tmrTick.Stop();
            animIndex = 0;
        }

        public void SetAnimInterval(float sec)
        {
            ui_tmrTick.Interval = (int)(sec * 1000);
        }
        
        private void ui_tmrTick_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void AnimPanel_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                if (animGroup == null || animGroup.AnimFrames.Count() == 0) return;
                Size s = this.Size;
                AnimFrame af = animGroup.AnimFrames[animIndex];
                int x = (int)(s.Width / 2.0f - af.FrameImage.Width * af.Pivot.X);
                int y = (int)(s.Height / 2.0f - af.FrameImage.Height * af.Pivot.Y);
                e.Graphics.DrawImage(animGroup.AnimFrames[animIndex].FrameImage, x, y);
                ++animIndex;
                animIndex = animIndex % animGroup.AnimFrames.Count();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
            }
        }
    }
}
