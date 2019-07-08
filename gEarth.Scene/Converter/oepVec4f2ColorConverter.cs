using gEarthPack;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media;

namespace gEarth.Scene.Converter
{
    public class oepVec4f2ColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            oepVec4f input = (oepVec4f)value;
            return Color.FromScRgb(input.a, input.x, input.y, input.z);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            Color c = (Color)value;
            return new oepVec4f(c.ScR, c.ScG, c.ScB, c.ScA);
        }
    }
}
