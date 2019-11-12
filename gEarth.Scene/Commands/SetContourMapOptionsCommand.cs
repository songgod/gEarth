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
    public class SetContourMapOptionsCommand : CommandBinding
    {
        public SetContourMapOptionsCommand()
        {
            Command = CommandLib.SetContourMapOptionsCommand;
            CanExecute += SetContourMapOptionsCommand_CanExecute;
            Executed += SetContourMapOptionsCommand_Executed;
        }

        private void SetContourMapOptionsCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            if (ContourMapOptionsWindow.Single != null)
                return;

            oepContourMapExtension cm = null;
            foreach (var extension in Project.CurrentMap.Extensions)
            {
                cm = extension as oepContourMapExtension;
                if (cm != null)
                {
                    break;
                }
            }
            if (cm == null)
            {
                cm = new oepContourMapExtension();
                Project.CurrentMap.Extensions.Add(cm);
            }

            ContourMapOptionsWindow sw = new ContourMapOptionsWindow() { DataContext = cm, Owner = System.Windows.Application.Current.MainWindow };
            sw.Show();
        }

        private void SetContourMapOptionsCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
