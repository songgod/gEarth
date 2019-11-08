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
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (AnalysisProfileWindow.Single != null)
                return;
            AnalysisProfileWindow w = new AnalysisProfileWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void AnalysisProfileCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
