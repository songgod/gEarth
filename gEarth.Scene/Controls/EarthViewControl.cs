using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.Integration;
using gEarthPack;
using System.Windows.Forms;

namespace gEarth.Scene.Controls
{
    public delegate void EarthViewReady(bool bready);
    public class EarthViewControl : WindowsFormsHost
    {
        private Render render { get; set; }

        public EarthViewControl()
        {
            Child = new PictureBox() { Width = 800, Height = 800 };
            Child.Paint += Child_Paint;
            Unloaded += EarthViewControl_Unloaded;
        }

        public event EarthViewReady OnEarthViewReady;

        private void Child_Paint(object sender, PaintEventArgs e)
        {
            if (render != null)
                return;

            render = new Render();
            IntPtr res = Child.Handle;
            render.Start(res);
            if (OnEarthViewReady != null)
                OnEarthViewReady.Invoke(true);
        }

        public bool OpenMap(oepMap map)
        {
            if (map == null || render==null)
                return false;
            return render.Open(map);
        }

        private void EarthViewControl_Unloaded(object sender, System.Windows.RoutedEventArgs e)
        {
            Child.Paint -= Child_Paint;
            render.End();
        }
    }
}
