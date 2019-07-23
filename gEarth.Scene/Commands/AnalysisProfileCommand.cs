using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class AnalysisProfileCommand : CommandBinding
    {
        public AnalysisProfileCommand()
        {
            Command = CommandLib.AnalysisProfileCommand;
            CanExecute += AnalysisProfileCommand_CanExecute;
            Executed += AnalysisProfileCommand_Executed;
        }

        private void AnalysisProfileCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void AnalysisProfileCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
