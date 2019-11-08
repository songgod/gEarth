using gEarth.Scene.Controls;
using gEarth.Scene.Windows;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class AnalysisVisbleLineCommand : CommandBinding
    {
        public AnalysisVisbleLineCommand()
        {
            Command = CommandLib.AnalysisVisbleLineCommand;
            CanExecute += AnalysisVisbleCommand_CanExecute;
            Executed += AnalysisVisbleCommand_Executed;
        }

        private void AnalysisVisbleCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (AnalysisVisibilityLineWindow.Single != null)
                return;
            AnalysisVisibilityLineWindow w = new AnalysisVisibilityLineWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void AnalysisVisbleCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
