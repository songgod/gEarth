using Fluent;
using gEarth.Scene;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms.Integration;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace gEarthApp
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : RibbonWindow
    {
        //public AxgEarthView EarthView { get; set; }
        public MainWindow()
        {
            InitializeComponent();
            InitStartMap();
            ax.OnEarthViewReady += Ax_OnEarthViewReady;
            mtree.OnSelectObjectChanged += Mtree_OnSelectObjectChanged;
            gEarth.Scene.Project.OnCurrentMapChanged += Project_OnCurrentMapChanged;
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

        private void Mtree_OnSelectObjectChanged(object obj)
        {
            oepViewpoint vp = obj as oepViewpoint;
            if(vp!=null)
            {
                ax.render.Viewpoint = vp;
                return;
            }
            oepLayer lyr = obj as oepLayer;
            if(lyr!=null)
            {
                vp = oepViewFitter.Fitter(lyr, Project.CurrentMap, ax.render);
                ax.render.Viewpoint = vp;
                return;
            }
            oepAnimationPath apth = obj as oepAnimationPath;
            if(apth!=null)
            {
                ax.render.PlayPath(apth);
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
        }
    }
}
