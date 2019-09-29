using gEarth.Scene.Controls;
using gEarth.Scene.Windows;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
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
            var obj = System.Diagnostics.Process.GetProcessesByName("ScreenRecorder").ToList();
            if (obj.Count == 0)
            {
                StartProcess();
            }
        }

        public void StartProcess()
        {
            ProcessStartInfo info = new ProcessStartInfo();
            string path = Directory.GetCurrentDirectory() + "\\ScreenRecorder.exe";
            info.FileName = path;
            info.Arguments = "";
            info.WindowStyle = ProcessWindowStyle.Normal;
            Process pro = Process.Start(info);
        }

        private void RecordScreenCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }
    }
}
