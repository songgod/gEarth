using gEarth.Scene.Controls;
using gEarthPack;
using System;
using System.Collections.Generic;
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
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                oepGDALSource source = new oepGDALSource() { url = dlg.FileName };
                oepElevationLayer imglyr = new oepElevationLayer(source);
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
