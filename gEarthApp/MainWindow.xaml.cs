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
            ax.OnEarthViewReady += Ax_OnEarthViewReady;
        }

        private void Ax_OnEarthViewReady(bool bready)
        {
            if (Project.LastMapUrl.Length > 0)
            {
                oepMap map = new oepMap();
                if (map.load(Project.LastMapUrl))
                {
                    ax.OpenMap(map);
                    Project.CurrentMap = map;
                    return;
                }
            }
            if (gEarth.Scene.Commands.CommandLib.New.CanExecute(ax, null))
                gEarth.Scene.Commands.CommandLib.New.Execute(ax, null);
        }
    }
}
