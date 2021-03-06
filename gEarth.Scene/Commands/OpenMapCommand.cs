﻿using gEarth.Scene.Controls;
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
    public class OpenMapCommand : CommandBinding
    {
        public OpenMapCommand()
        {
            Command = CommandLib.OpenMap;
            Executed += OpenMapCommand_Executed;
            CanExecute += OpenMapCommand_CanExecute;
        }

        private void OpenMapCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            e.Handled = true;
        }

        private void OpenMapCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            if(dlg.ShowDialog()==DialogResult.OK)
            {
                if (Project.CurrentMap != null && Project.CurrentMap.Url == dlg.FileName)
                    return;
                oepMap map = new oepMap();
                if (map.load(dlg.FileName))
                {
                    Project.CurrentMap = map;
                }
            }
        }
    }
}
