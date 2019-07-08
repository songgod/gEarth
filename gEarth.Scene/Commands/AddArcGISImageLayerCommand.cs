using gEarth.Scene.Windows;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class AddArcGISImageLayerCommand : CommandBinding
    {
        public AddArcGISImageLayerCommand()
        {
            Command = CommandLib.AddArcGISImageLayerCommand;
            CanExecute += AddArcGISImageLayerCommand_CanExecute;
            Executed += AddArcGISImageLayerCommand_Executed;
        }

        private void AddArcGISImageLayerCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepArcGISSourceOptions src = new oepArcGISSourceOptions();
            ArcGISSourceOptionsWindow window = new ArcGISSourceOptionsWindow() { DataContext = src };
            var res = window.ShowDialog();
            if (res.HasValue && res.Value)
            {
                oepImageLayerOptions options = new oepImageLayerOptions() { driver = src };
                oepImageLayer imglyr = new oepImageLayer(options) { Name = "ArcGISImage" };
                Project.CurrentMap.Layers.Add(imglyr);
                if (!imglyr.IsOK)
                {
                    System.Windows.MessageBox.Show(imglyr.StatusString);
                }
            }
        }

        private void AddArcGISImageLayerCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
