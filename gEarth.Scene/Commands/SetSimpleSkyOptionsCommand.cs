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
    public class SetSimpleSkyOptionsCommand : CommandBinding
    {
        public SetSimpleSkyOptionsCommand()
        {
            Command = CommandLib.SetSimpleSkyOptionsCommand;
            CanExecute += SetSimpleSkyOptionsCommand_CanExecute;
            Executed += SetSimpleSkyOptionsCommand_Executed;
        }

        private void SetSimpleSkyOptionsCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepSimpleSkyExtension se = null;
            foreach (var extension in Project.CurrentMap.Extensions)
            {
                se = extension as oepSimpleSkyExtension;
                if (se != null)
                {
                    break;
                }
            }
            if(se==null)
            {
                se = new oepSimpleSkyExtension();
                Project.CurrentMap.Extensions.Add(se);
            }

            SimpleSkyOptionsWindow sw = new SimpleSkyOptionsWindow() { DataContext = se, Owner = System.Windows.Application.Current.MainWindow };
            sw.ShowDialog();
        }

        private void SetSimpleSkyOptionsCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
