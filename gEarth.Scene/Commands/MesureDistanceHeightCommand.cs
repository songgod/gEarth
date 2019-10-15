using gEarth.Scene.Controls;
using gEarth.Scene.Windows;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class MesureDistanceHeightCommand : CommandBinding
    {
        public MesureDistanceHeightCommand()
        {
            Command = CommandLib.MesureDistanceHeightCommand;
            CanExecute += MesureDistanceCommand_CanExecute;
            Executed += MesureDistanceCommand_Executed;
        }

        private void MesureDistanceCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (MeasureDistanceWindow.Single != null)
                return;
            MeasureDistanceWindow w = new MeasureDistanceWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void MesureDistanceCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
