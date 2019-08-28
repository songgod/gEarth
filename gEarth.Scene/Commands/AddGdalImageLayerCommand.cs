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
    public class AddGdalImageLayerCommand : CommandBinding
    {
        public AddGdalImageLayerCommand()
        {
            Command = CommandLib.AddGdalImageLayerCommand;
            CanExecute += AddGdalImageLayerCommand_CanExecute; ;
            Executed += AddGdalImageLayerCommand_Executed; ;
        }

        private void AddGdalImageLayerCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "TIFF GeoTIFF(*.tif *.tiff)|*.tif;*.tiff;|"+
                "Erdas Imaging Images(*img)|*img|"+
                "Envi Image format(*img)|*img|"+
                "MS Windows Device Independent Bitmap(*bmp)|*bmp|"+
                "JPEG JFIF(*jpg *jpeg)|*jpg;*jpeg|" +
                "All files(*.*)|*.*";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                oepGDALSourceOptions source = new oepGDALSourceOptions() { url = dlg.FileName };
                oepImageLayerOptions options = new oepImageLayerOptions() { driver = source };
                oepImageLayer imglyr = new oepImageLayer(options) { Name = Path.GetFileNameWithoutExtension(dlg.FileName) };
                Project.CurrentMap.Layers.Add(imglyr);
                if(!imglyr.IsOK)
                {
                    MessageBox.Show(imglyr.StatusString);
                }
            }
        }
        private void AddGdalImageLayerCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
