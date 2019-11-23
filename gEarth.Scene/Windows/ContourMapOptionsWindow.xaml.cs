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
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Globalization;
using System.IO;
using System.Collections.ObjectModel;

namespace gEarth.Scene.Windows
{
    
    internal class ColorMapConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            Dictionary<float, oepVec4f> cm = (Dictionary<float, oepVec4f>)value;
            if (cm == null)
                return null;

            float minv = cm.Keys.Min();
            float maxv = cm.Keys.Max();
            float len = maxv - minv;

            LinearGradientBrush brush = new LinearGradientBrush();
            brush.StartPoint = new Point(0, 0);
            brush.EndPoint = new Point(1, 0);

            foreach (var c in cm)
            {
                brush.GradientStops.Add(new GradientStop()
                {
                    Offset = (c.Key-minv)/len,
                    Color = Color.FromScRgb(c.Value.a, c.Value.x, c.Value.y, c.Value.z)
                });
            }

            return brush;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    internal static class ColorMapSource
    {
        static ColorMapSource()
        {
            ColorMapList = new ObservableCollection<Dictionary<float, oepVec4f>>();
            ReadFiles();
        }

        static public ObservableCollection<Dictionary<float, oepVec4f>> ColorMapList { get; private set; }

        static private void ReadFiles()
        {
            string path = Directory.GetCurrentDirectory()+"\\config\\colormaps";
            DirectoryInfo TheFolder = new DirectoryInfo(path);
            if (!TheFolder.Exists)
                return;

            
            foreach (FileInfo NextFile in TheFolder.GetFiles())
            {
                if (NextFile.Extension == ".cm")
                {
                    try
                    {
                        Dictionary<float, oepVec4f> cm = new Dictionary<float, oepVec4f>();
                        using (StreamReader sr = new StreamReader(NextFile.FullName))
                        {
                            string line;
                            while ((line = sr.ReadLine()) != null)
                            {
                                var strs = line.Split(' ');
                                float v = 0.0f;
                                float r = 0.0f;
                                float g = 0.0f;
                                float b = 0.0f;
                                float a = 0.0f;
                                if(strs.Length==5 && 
                                    float.TryParse(strs[0], out v) &&
                                    float.TryParse(strs[1], out r) &&
                                    float.TryParse(strs[2], out g) &&
                                    float.TryParse(strs[3], out b) &&
                                    float.TryParse(strs[4], out a))
                                {
                                    cm[v] = new oepVec4f(r, g, b, a);
                                }
                            }
                        }
                        if (cm.Count > 1)
                            ColorMapList.Add(cm);
                    }
                    catch (Exception)
                    {
                        continue;
                    }
                }
            }
            
        }
    }
    /// <summary>
    /// ContourMapOptionsWindow.xaml 的交互逻辑
    /// </summary>
    public partial class ContourMapOptionsWindow : Window
    {
        public ContourMapOptionsWindow()
        {
            InitializeComponent();
            Single = this;
        }

        public static ContourMapOptionsWindow Single { get; private set; }

        private void Window_Closed(object sender, EventArgs e)
        {
            Single = null;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

        }
    }
}
