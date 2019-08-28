using gEarth.Scene.Controls;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class AddGdalElevationLayerCommand : CommandBinding
    {
        public AddGdalElevationLayerCommand()
        {
            Command = CommandLib.AddGdalElevationLayerCommand;
            CanExecute += AddGdalElevationLayerCommand_CanExecute; ;
            Executed += AddGdalElevationLayerCommand_Executed; ;
        }

        private void AddGdalElevationLayerCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "TIFF GeoTIFF(*.tif *.tiff)|*.tif;*.tiff;|" +
                                "Erdas Imaging Images(*img)|*img|" +
                                "Envi Image format(*img)|*img|" +
                                "MS Windows Device Independent Bitmap(*bmp)|*bmp|" +
                                "JPEG JFIF(*jpg *jpeg)|*jpg;*jpeg|" +
                                "All files(*.*)|*.*";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                oepGDALSourceOptions source = new oepGDALSourceOptions() { url = dlg.FileName };
                oepElevationLayerOptions options = new oepElevationLayerOptions() { driver = source };
                oepElevationLayer imglyr = new oepElevationLayer(options) { Name = Path.GetFileNameWithoutExtension(dlg.FileName) };
                Project.CurrentMap.Layers.Add(imglyr);
                if (!imglyr.IsOK)
                {
                    MessageBox.Show(imglyr.StatusString);
                }
            }
        }
        private void AddGdalElevationLayerCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
