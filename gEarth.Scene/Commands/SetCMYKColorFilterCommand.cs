using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using gEarthPack;
using gEarth.Scene.Windows;

namespace gEarth.Scene.Commands
{
    public class SetCMYKColorFilterCommand : CommandBinding
    {
        public SetCMYKColorFilterCommand()
        {
            Command = CommandLib.SetCMYKColorFilterCommand;
            CanExecute += SetCMYKColorFilterCommand_CanExecute;
            Executed += SetCMYKColorFilterCommand_Executed;
        }

        private void SetCMYKColorFilterCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepCMYKColorFilter cf = new oepCMYKColorFilter();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                    imglyr.ColorFilters.Add(cf);
                }
            }
           CMYKColorFilterOptionsWindow w = new CMYKColorFilterOptionsWindow() { DataContext = cf };
            w.ShowDialog();
            cf.Reset();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                }
            }
        }

        private void SetCMYKColorFilterCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
