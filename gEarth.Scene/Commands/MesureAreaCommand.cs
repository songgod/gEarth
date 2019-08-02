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
    public class MesureAreaCommand : CommandBinding
    {
        public MesureAreaCommand()
        {
            Command = CommandLib.MesureAreaCommand;
            CanExecute += MesureAreaCommand_CanExecute;
            Executed += MesureAreaCommand_Executed;
        }

        private void MesureAreaCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;

            if (MeasureAreaWindow.Single != null)
                return;
            MeasureAreaWindow w = new MeasureAreaWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void MesureAreaCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
