using gEarth.Scene.Controls;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Globalization;
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

namespace gEarth.Scene.Windows
{
    internal class ProfilePointsConverter : IMultiValueConverter
    {
        public ProfilePointsConverter()
        {

        }

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (values[3] == DependencyProperty.UnsetValue)
                return null;
            List<oepVec2f> profile = (List<oepVec2f>)values[3];
            if (profile == null || profile.Count==0)
                return null;

            double dis = (double)(values[0]);
            if (dis == 0)
                return null;
            double minelv = (double)(values[1]);
            if (minelv == double.MinValue)
                return null;
            double maxelv = (double)(values[2]);
            if (maxelv == double.MaxValue)
                return null;
            if (minelv > maxelv)
                return null;
            double leny = maxelv - minelv;
            double w = (double)(values[4]);
            double h = (double)(values[5]);

            PointCollection res = new PointCollection();
            foreach (var p in profile)
            {
                res.Add(new Point(p.x / dis * w, leny==0.0 ? h : (p.y - minelv) / leny * h*-1+h));
            }
            return res;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    /// <summary>
    /// AnalysisProfileWindow.xaml 的交互逻辑
    /// </summary>
    public partial class AnalysisProfileWindow : Window
    {
        public AnalysisProfileWindow()
        {
            InitializeComponent();
        }

        public static AnalysisProfileWindow Single { get; private set; }

        public EarthViewControl EarthViewCtrl { get; set; }

        private oepMeasureProfileHandler Handle { get; set; }

        private void Window_Closed(object sender, EventArgs e)
        {
            Single = null;
            EarthViewCtrl.render.Handlers.Remove(Handle);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Handle = new oepMeasureProfileHandler();
            this.DataContext = Handle;
            EarthViewCtrl.render.Handlers.Add(Handle);
        }
    }
}
