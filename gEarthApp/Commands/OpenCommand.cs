using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarthApp.Commands
{
    internal class OpenCommand : CommandBinding
    {
        public OpenCommand()
        {
            Command = CommandLib.Open;
            Executed += OpenCommand_Executed;
            CanExecute += OpenCommand_CanExecute;
        }

        private void OpenCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }

        private void OpenCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}
