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
    public class MeasureAngleCommand : CommandBinding
    {
        public MeasureAngleCommand()
        {
            Command = CommandLib.MeasureAngleCommand;
            CanExecute += MesureAngleCommand_CanExecute;
            Executed += MesureAngleCommand_Executed;
        }

        private void MesureAngleCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (MeasureAngleWindow.Single != null)
                return;
            MeasureAngleWindow w = new MeasureAngleWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void MesureAngleCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
