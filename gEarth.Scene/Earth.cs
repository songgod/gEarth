using AxgEarthViewLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gEarth.Scene
{
    public class Earth
    {
        public Earth()
        {
            HeightLayers = new HeightLayerCollection();
            ImageLayers = new ImageLayerCollection();
            VectorLayers = new VectorLayerCollection();
        }

        public AxgEarthView EarthView { get; set; }

        public string EarthFile { get; protected set; }

        public bool IsOpened { get; protected set; }

        public HeightLayerCollection HeightLayers { get; protected set; }

        public ImageLayerCollection ImageLayers { get; protected set; }

        public VectorLayerCollection VectorLayers { get; protected set; }


        public bool Open(string url)
        {
            if (EarthView.Open(url) < 0)
                return false;
            EarthFile = url;
            IsOpened = true;
            return true;
        }

        public void New()
        {

        }

        public void Save()
        {

        }

        public void SaveAs(string url)
        {

        }

        public void AddDem(string strxml)
        {

        }
    }
}
