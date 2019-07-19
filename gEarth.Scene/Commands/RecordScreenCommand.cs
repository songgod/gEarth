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
    public class RecordScreenCommand : CommandBinding
    {
        public RecordScreenCommand()
        {
            Command = CommandLib.RecordScreenCommand;
            CanExecute += RecordScreenCommand_CanExecute;
            Executed += RecordScreenCommand_Executed;
        }

        private void RecordScreenCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;
            if (RecordScreenWindow.Single != null)
                return;
            RecordScreenWindow w = new RecordScreenWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }

        private void RecordScreenCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
