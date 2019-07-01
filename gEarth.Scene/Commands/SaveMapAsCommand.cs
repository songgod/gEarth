using gEarth.Scene.Controls;
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
    public class SaveMapAsCommand : CommandBinding
    {
        public SaveMapAsCommand()
        {
            Command = CommandLib.SaveMapAs;
            CanExecute += SaveMapAsCommand_CanExecute;
            Executed += SaveMapAsCommand_Executed;
        }

        private void SaveMapAsCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                Project.CurrentMap.saveAs(dlg.FileName);
            }
        }

        private void SaveMapAsCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
