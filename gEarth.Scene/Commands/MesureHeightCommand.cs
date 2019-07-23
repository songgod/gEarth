using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class MesureHeightCommand : CommandBinding
    {
        public MesureHeightCommand()
        {
            Command = CommandLib.MesureHeightCommand;
            CanExecute += MesureHeightCommand_CanExecute;
            Executed += MesureHeightCommand_Executed;
        }

        private void MesureHeightCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void MesureHeightCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
