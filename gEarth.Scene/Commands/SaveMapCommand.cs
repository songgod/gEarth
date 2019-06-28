using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class SaveMapCommand : CommandBinding
    {
        public SaveMapCommand()
        {
            Command = CommandLib.SaveMap;
            CanExecute += SaveMapCommand_CanExecute;
            Executed += SaveMapCommand_Executed;
        }

        private void SaveMapCommand_Executed(object sender, ExecutedRoutedEventArgs e)
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

        private void SaveMapCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap!=null;
            e.Handled = true;
        }
    }
}
