using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnimTool
{
    public class AnimGroup
    {
        public List<AnimFrame> AnimFrames { get; set; }
        public string GroupName { get; set; }
        public Rectangle GroupRect { get; set; }

        public void SaveToFile(StreamWriter file)
        {
            file.WriteLine(GroupName);
            AnimFrames.Sort((a, b) => a.FrameNo > b.FrameNo ? 1 : -1);
            foreach (AnimFrame af in AnimFrames)
            {
                file.Write(af.FrameNo + " : ");
                file.WriteLine(af.FrameRect.ToString());
            }
        }
    }
}
