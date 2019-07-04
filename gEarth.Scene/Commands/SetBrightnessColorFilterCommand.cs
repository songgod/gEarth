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
    public class SetBrightnessColorFilterCommand : CommandBinding
    {
        public SetBrightnessColorFilterCommand()
        {
            Command = CommandLib.SetBrightnessColorFilterCommand;
            CanExecute += SetBrightnessColorFilterCommand_CanExecute;
            Executed += SetBrightnessColorFilterCommand_Executed;
        }

        private void SetBrightnessColorFilterCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepBrightnessContrastColorFilter cf = new oepBrightnessContrastColorFilter();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                    imglyr.ColorFilters.Add(cf);
                }
            }
            BrightnessColorFilterOptionsWindow w = new BrightnessColorFilterOptionsWindow() { DataContext = cf };
            w.ShowDialog();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                }
            }
        }

        private void SetBrightnessColorFilterCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
