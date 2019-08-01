using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Globalization;

namespace gEarth.Scene.Converter
{
    public class oepVec3f2StringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            oepVec3f input = (oepVec3f)value;
            return input.x.ToString() + " " + input.y.ToString() + " " + input.z.ToString();
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string input = (string)value;
            string[] strs = input.Split(' ');
            if (strs.Count() != 3)
                return null;

            float x;
            if (!float.TryParse(strs[0], out x))
                return null;
            float y;
            if (!float.TryParse(strs[1], out y))
                return null;
            float z;
            if (!float.TryParse(strs[2], out z))
                return null;

            return new oepVec3f(x, y, z);
        }
    }
}
