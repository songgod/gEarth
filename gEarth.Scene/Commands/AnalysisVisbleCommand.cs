﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class AnalysisVisbleCommand : CommandBinding
    {
        public AnalysisVisbleCommand()
        {
            Command = CommandLib.AnalysisVisbleCommand;
            CanExecute += AnalysisVisbleCommand_CanExecute;
            Executed += AnalysisVisbleCommand_Executed;
        }

        private void AnalysisVisbleCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void AnalysisVisbleCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}