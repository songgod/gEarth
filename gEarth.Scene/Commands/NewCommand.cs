using gEarth.Scene.View;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class NewCommand : CommandBinding
    {
        public NewCommand()
        {
            Command = CommandLib.Open;
            CanExecute += NewCommand_CanExecute;
            Executed += NewCommand_Executed;
        }

        private void NewCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl ax = e.Parameter as EarthViewControl;
            if(ax!=null)
            {
                oepMap map = new oepMap();
                ax.OpenMap(map);
                Project.CurrentMap = map;
            }
        }

        private void NewCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }
    }
}
