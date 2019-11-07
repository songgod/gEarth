using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class MeasureVolumeCommand : CommandBinding
    {
        public MeasureVolumeCommand()
        {
            Command = CommandLib.MeasureVolumeCommand;
            CanExecute += MesureVolumeCommand_CanExecute;
            Executed += MesureVolumeCommand_Executed;
        }

        private void MesureVolumeCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void MesureVolumeCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
