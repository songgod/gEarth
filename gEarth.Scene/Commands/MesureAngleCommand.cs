using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class MesureAngleCommand : CommandBinding
    {
        public MesureAngleCommand()
        {
            Command = CommandLib.MesureAngleCommand;
            CanExecute += MesureAngleCommand_CanExecute;
            Executed += MesureAngleCommand_Executed;
        }

        private void MesureAngleCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void MesureAngleCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
