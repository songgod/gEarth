using System;
using gEarth.Scene;
using gEarthPack;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace gEarth.Scene.Controls
{
    /// <summary>
    /// ProjectControl.xaml 的交互逻辑
    /// </summary>
    public partial class ProjectControl : UserControl
    {
        public ProjectControl()
        {
            InitializeComponent();
            InitStartMap();
            InstallEvent();
        }

        private oepMap StartMap { get; set; }

        private void InitStartMap()
        {
            //if (Project.LastMapUrl!=null && Project.LastMapUrl.Length > 0)
            //{
            //    oepMap map = new oepMap();
            //    if (map.load(Project.LastMapUrl))
            //    {
            //        StartMap = map;
            //    }
            //}
            //if (StartMap == null)
            //{
            StartMap = gEarth.Scene.Commands.NewMapCommand.NewMap();
            //}
        }

        private void InstallEvent()
        {
            ax.OnEarthViewReady += Ax_OnEarthViewReady;
            mtree.OnSelectObjectChanged += Mtree_OnSelectObjectChanged;
            Project.OnCurrentMapChanged += Project_OnCurrentMapChanged;
        }

        private void Mtree_OnSelectObjectChanged(object obj)
        {
            oepViewpoint vp = obj as oepViewpoint;
            if (vp != null)
            {
                ax.render.Viewpoint = vp;
                return;
            }
            oepLayer lyr = obj as oepLayer;
            if (lyr != null)
            {
                vp = oepViewFitter.Fitter(lyr, Project.CurrentMap, ax.render);
                ax.render.Viewpoint = vp;
                return;
            }
            oepAnimationPath apth = obj as oepAnimationPath;
            if (apth != null)
            {
                oepAnimationPath.PlayPath(apth, ax.render);
                return;
            }
        }

        private void Project_OnCurrentMapChanged(oepMap oldmap, oepMap newmap)
        {
            ax.render.Open(newmap);
            mtree.InitMap(newmap);
        }

        private void Ax_OnEarthViewReady(bool bready)
        {
            Project.CurrentMap = StartMap;
            oepMouseEventHandler mh = new oepMouseEventHandler();
            mh.Keep = true;
            mh.OnMouseMove += Mh_OnMouseMove;
            ax.render.Handlers.Add(mh);
        }

        private void Mh_OnMouseMove(oepMouseEventHandler handle, oepVec3f p, int keybutton)
        {
            string lat = this.Resources["lat"] as string;
            string lng = this.Resources["lat"] as string;
            string alt = this.Resources["lat"] as string;
            this.coords.Dispatcher.Invoke(new Action(() => { this.coords.Text = lat + p.x.ToString() + lng + p.y.ToString() + alt + p.z.ToString(); }));
        }
    }
}
