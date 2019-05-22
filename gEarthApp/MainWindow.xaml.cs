using AxgEarthViewLib;
using Fluent;
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

            //WindowsFormsHost host = new WindowsFormsHost();
            //AxgEarthView ax = new AxgEarthView();
            //ax.BeginInit();
            //host.Child = ax;
            //panel.Children.Add(host);
            //ax.EndInit();
            //EarthView = ax;
        }

        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            ax.Open(@"E:\work\project\gwaldron-osgearth-1faf43a\tests\clouds.earth");
        }
    }
}
