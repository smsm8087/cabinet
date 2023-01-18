using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnimTool
{
    public class AnimFrame
    {
        public int FrameNo { get; set; }
        public Rectangle FrameRect { get; set; }
        public PointF Pivot { get; set; }
        public Bitmap FrameImage { get; set; }
    }
}
