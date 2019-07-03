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
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                oepGDALSource source = new oepGDALSource() { url = dlg.FileName };
                oepImageLayer imglyr = new oepImageLayer(source) { Name = Path.GetFileNameWithoutExtension(dlg.FileName) };
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
