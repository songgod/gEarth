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
    public class EditAnimationPathCommand : CommandBinding
    {
        public EditAnimationPathCommand()
        {
            Command = CommandLib.EditAnimationPathCommand;
            Executed += EditAnimationPathCommand_Executed;
            CanExecute += EditAnimationPathCommand_CanExecute;
        }

        private void EditAnimationPathCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }

        private void EditAnimationPathCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;
            if (EditAnimationPathWindow.Single != null)
                return;

            EditAnimationPathWindow w = new EditAnimationPathWindow() { EarthViewCtrl = evc, Owner = System.Windows.Application.Current.MainWindow };
            w.Show();
        }
    }
}
