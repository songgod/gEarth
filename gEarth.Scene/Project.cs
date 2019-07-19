using gEarthPack;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gEarth.Scene
{
    public delegate void CurrentMapChanged(oepMap oldmap, oepMap newmap);
    static public class Project
    {
        static Project()
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
                LastMapUrl = currentMap.Url;
                if (OnCurrentMapChanged!=null)
                {
                    OnCurrentMapChanged.Invoke(oldmap, currentMap);
                }
            }
        }

        static public string LastMapUrl
        {
            get
            {
                string path = Directory.GetCurrentDirectory() + "\\Config\\LastMap.txt";
                if (!File.Exists(path))
                    return "";
                FileStream fs = new FileStream(path,FileMode.Open);
                StreamReader sr = new StreamReader(fs);
                string url = sr.ReadLine();
                sr.Close();
                fs.Close();
                return url;
            }
            private set
            {
                string path = Directory.GetCurrentDirectory() + "\\Config\\LastMap.txt";
                FileStream fs = new FileStream(path, FileMode.OpenOrCreate);
                StreamWriter sr = new StreamWriter(fs);
                sr.WriteLine(value);
                sr.Close();
                fs.Close();
            }
        }

        static public string TempPath
        {
            get
            {
                try
                {
                    string temppath = System.IO.Path.GetTempPath() + "gEarth\\";
                    if (!Directory.Exists(temppath))
                        Directory.CreateDirectory(temppath);
                    return temppath;
                }
                catch (Exception)
                {
                    return Directory.GetCurrentDirectory()+"\\";
                }
            }
        }
    }
}
