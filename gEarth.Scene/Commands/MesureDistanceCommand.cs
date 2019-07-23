using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class MesureDistanceCommand : CommandBinding
    {
        public MesureDistanceCommand()
        {
            Command = CommandLib.MesureDistanceCommand;
            CanExecute += MesureDistanceCommand_CanExecute;
            Executed += MesureDistanceCommand_Executed;
        }

        private void MesureDistanceCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void MesureDistanceCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
