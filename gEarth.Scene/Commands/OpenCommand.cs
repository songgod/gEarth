using gEarth.Scene.View;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class OpenCommand : CommandBinding
    {
        public OpenCommand()
        {
            Command = CommandLib.Open;
            Executed += OpenCommand_Executed;
            CanExecute += OpenCommand_CanExecute;
        }

        private void OpenCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }

        private void OpenCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl ax = e.Parameter as EarthViewControl;
            OpenFileDialog dlg = new OpenFileDialog();
            if(dlg.ShowDialog()==DialogResult.OK)
            {
                if (Project.CurrentMap != null && Project.CurrentMap.Url == dlg.FileName)
                    return;
                oepMap map = new oepMap();
                if (map.load(dlg.FileName))
                {
                    ax.OpenMap(map);
                    Project.CurrentMap = map;
                }
            }
        }
    }
}
