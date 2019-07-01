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
            throw new NotImplementedException();
        }

        private void AddArcGISImageLayerCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
