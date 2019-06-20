using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class SaveCommand : CommandBinding
    {
        public SaveCommand()
        {
            Command = CommandLib.Save;
            CanExecute += SaveCommand_CanExecute;
            Executed += SaveCommand_Executed;
        }

        private void SaveCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            if(Project.CurrentMap.Url.Length>0)
                Project.CurrentMap.save();
            else
            {
                SaveFileDialog dlg = new SaveFileDialog();
                if(dlg.ShowDialog()==DialogResult.OK)
                {
                    Project.CurrentMap.saveAs(dlg.FileName);
                }
            }
        }

        private void SaveCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap!=null;
            e.Handled = true;
        }
    }
}
