using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gEarth.Scene
{
    public delegate void CurrentMapChanged(oepMap oldmap, oepMap newmap);
    public class Project
    {
        public Project()
        {

        }

        static public event CurrentMapChanged OnCurrentMapChanged;
        static private oepMap currentMap = null;

        static public oepMap CurrentMap
        {
            get { return currentMap; }
            set
            {
                oepMap oldmap = currentMap;
                currentMap = value;
                if(OnCurrentMapChanged!=null)
                {
                    OnCurrentMapChanged.Invoke(oldmap, currentMap);
                }
            }
        }

    }
}
