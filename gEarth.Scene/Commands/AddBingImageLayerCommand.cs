using gEarth.Scene.Windows;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class AddBingImageLayerCommand : CommandBinding
    {
        public AddBingImageLayerCommand()
        {
            Command = CommandLib.AddBingImageLayerCommand;
            CanExecute += AddBingImageLayerCommand_CanExecute;
            Executed += AddBingImageLayerCommand_Executed;
        }

        private void AddBingImageLayerCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepBingSource src = new oepBingSource();
            BingSourceOptionsWindow window = new BingSourceOptionsWindow() { DataContext = src };
            var res = window.ShowDialog();
            if(res.HasValue && res.Value)
            {
                oepImageLayer imglyr = new oepImageLayer(src);
                Project.CurrentMap.Layers.Add(imglyr);
                if (!imglyr.IsOK)
                {
                    System.Windows.MessageBox.Show(imglyr.StatusString);
                }
            }
        }

        private void AddBingImageLayerCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
