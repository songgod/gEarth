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
    public class AddOgrFeatureLayerCommand : CommandBinding
    {
        public AddOgrFeatureLayerCommand()
        {
            Command = CommandLib.AddOgrFeatureLayerCommand;
            CanExecute += AddOgrFeatureLayerCommand_CanExecute;
            Executed += AddOgrFeatureLayerCommand_Executed;
        }

        private void AddOgrFeatureLayerCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = 
                "Shapefile(*shp)|*shp|" +
                "All files(*.*)|*.*";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                oepOGRFeatureSourceOptions source = new oepOGRFeatureSourceOptions() { Url = dlg.FileName };
                oepFeatureModelLayerOptions options = new oepFeatureModelLayerOptions() { driver = source };
                oepFeatureModelLayer imglyr = new oepFeatureModelLayer(options) { Name = Path.GetFileNameWithoutExtension(dlg.FileName) };
                Project.CurrentMap.Layers.Add(imglyr);
                if (!imglyr.IsOK)
                {
                    MessageBox.Show(imglyr.StatusString);
                }
            }
        }

        private void AddOgrFeatureLayerCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
