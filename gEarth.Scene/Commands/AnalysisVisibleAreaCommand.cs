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
    public class AnalysisVisibleAreaCommand : CommandBinding
    {
        public AnalysisVisibleAreaCommand()
        {
            Command = CommandLib.AnalysisVisibleAreaCommand;
            CanExecute += AnalysisVisibleAreaCommand_CanExecute;
            Executed += AnalysisVisibleAreaCommand_Executed;
        }

        private void AnalysisVisibleAreaCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (AnalysisVisibilityAreaWindow.Single != null)
                return;
            AnalysisVisibilityAreaWindow w = new AnalysisVisibilityAreaWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void AnalysisVisibleAreaCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
