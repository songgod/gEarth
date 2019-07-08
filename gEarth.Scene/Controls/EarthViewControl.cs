using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.Integration;
using gEarthPack;
using System.Windows.Forms;
using System.Windows;

namespace gEarth.Scene.Controls
{
    public delegate void EarthViewReady(bool bready);
    public class EarthViewControl : WindowsFormsHost
    {
        public Render render { get; private set; }

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

       static void OnViewPointChangedCallback(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            EarthViewControl owner = obj as EarthViewControl;
            oepViewpoint vp = args.NewValue as oepViewpoint;
            owner.render.Flyto(vp);
        }

        public gEarthPack.oepViewpoint ViewPoint
        {
            get { return (gEarthPack.oepViewpoint)GetValue(ViewPointProperty); }
            set { SetValue(ViewPointProperty, value); }
        }

        // Using a DependencyProperty as the backing store for ViewPoint.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty ViewPointProperty =
            DependencyProperty.Register("ViewPoint", typeof(gEarthPack.oepViewpoint), typeof(EarthViewControl), new PropertyMetadata(null,new PropertyChangedCallback(OnViewPointChangedCallback)));


    }
}
