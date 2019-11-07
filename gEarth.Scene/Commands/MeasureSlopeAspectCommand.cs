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
    public class MeasureSlopeAspectCommand : CommandBinding
    {
        public MeasureSlopeAspectCommand()
        {
            Command = CommandLib.MeasureSlopeAspectCommand;
            CanExecute += MeasureSlopeAspectCommand_CanExecute;
            Executed += MeasureSlopeAspectCommand_Executed;
        }

        private void MeasureSlopeAspectCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (MeasureSlopeAspectWindow.Single != null)
                return;
            MeasureSlopeAspectWindow w = new MeasureSlopeAspectWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void MeasureSlopeAspectCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
