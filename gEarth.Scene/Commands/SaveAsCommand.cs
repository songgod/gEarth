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
    public class SaveAsCommand : CommandBinding
    {
        public SaveAsCommand()
        {
            Command = CommandLib.SaveAs;
            CanExecute += SaveAsCommand_CanExecute;
            Executed += SaveAsCommand_Executed;
        }

        private void SaveAsCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                Project.CurrentMap.saveAs(dlg.FileName);
            }
        }

        private void SaveAsCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
