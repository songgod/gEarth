using gEarth.Scene.Controls;
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
    public class NewMapCommand : CommandBinding
    {
        public NewMapCommand()
        {
            Command = CommandLib.NewMap;
            CanExecute += NewMapCommand_CanExecute;
            Executed += NewMapCommand_Executed;
        }

        private void NewMapCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl ax = e.Parameter as EarthViewControl;
            if(ax!=null)
            {
                oepMap map = new oepMap();
                string wdimg = Directory.GetCurrentDirectory() + "\\data\\world\\world.tif";
                string wdelv = Directory.GetCurrentDirectory() + "\\data\\world\\world-dem.tif";
                oepImageLayer wdimglyr = new oepImageLayer(new oepGDALSource() { url = wdimg }) { Name = Path.GetFileNameWithoutExtension(wdimg) };
                oepElevationLayer wdelvlyr = new oepElevationLayer(new oepGDALSource() { url = wdelv }) { Name = Path.GetFileNameWithoutExtension(wdelv) };
                map.Layers.Add(wdimglyr);
                map.Layers.Add(wdelvlyr);
                oepExtension skyext = new oepExtension(new oepSimpleSkyOptions());
                map.Extensions.Add(skyext);
                Project.CurrentMap = map;
            }
        }

        private void NewMapCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }
    }
}
