using gEarth.Scene.View;
using gEarthPack;
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class NewCommand : CommandBinding
    {
        public NewCommand()
        {
            Command = CommandLib.New;
            CanExecute += NewCommand_CanExecute;
            Executed += NewCommand_Executed;
        }

        private void NewCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl ax = e.Parameter as EarthViewControl;
            if(ax!=null)
            {
                oepMap map = new oepMap();
                string wdimg = Directory.GetCurrentDirectory() + "\\data\\world\\world.tif";
                string wdelv = Directory.GetCurrentDirectory() + "\\data\\world\\world-dem.tif";
                oepImageLayer wdimglyr = new oepImageLayer(new oepGDALSource() { url = wdimg });
                oepElevationLayer wdelvlyr = new oepElevationLayer(new oepGDALSource() { url = wdelv });
                map.Layers.Add(wdimglyr);
                map.Layers.Add(wdelvlyr);
                oepExtension skyext = new oepExtension(new oepSimpleSkyOptions());
                map.Extensions.Add(skyext);
                ax.OpenMap(map);
                Project.CurrentMap = map;
            }
        }

        private void NewCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }
    }
}
