using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class MesureAreaCommand : CommandBinding
    {
        public MesureAreaCommand()
        {
            Command = CommandLib.MesureAreaCommand;
            CanExecute += MesureAreaCommand_CanExecute;
            Executed += MesureAreaCommand_Executed;
        }

        private void MesureAreaCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void MesureAreaCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
