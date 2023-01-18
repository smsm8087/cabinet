using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public static class Const
    {
        private static EventHandler tileSizeChange;
        public static event EventHandler TileSizeChange
        {
            add
            {
                tileSizeChange += value;
            }
            remove
            {
                tileSizeChange -= value;
            }
        }

        private static int tileSize = 0;
        public static int TileSize
        {
            get
            {
                if (tileSize > 0) return tileSize;
                IniFile iniFile = new IniFile();
                if (iniFile.KeyExists("TileSize"))
                {
                    tileSize = int.Parse(iniFile.Read("TileSize"));
                }
                return tileSize;
            }
            set
            {
                if(value > 0)
                {
                    tileSize = value;
                    IniFile iniFile = new IniFile();
                    iniFile.Write("TileSize", tileSize.ToString());

                    tileSizeChange(null, EventArgs.Empty);
                }
            }
        }
    }
}
