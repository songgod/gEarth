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
    public class SetGammaColorFilterCommand : CommandBinding
    {
        public SetGammaColorFilterCommand()
        {
            Command = CommandLib.SetGammaColorFilterCommand;
            CanExecute += SetGammaColorFilterCommand_CanExecute;
            Executed += SetGammaColorFilterCommand_Executed;
        }

        private void SetGammaColorFilterCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepGammaColorFilter cf = new oepGammaColorFilter();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                    imglyr.ColorFilters.Add(cf);
                }
            }
            GammaColorFilterOptionsWindow w = new GammaColorFilterOptionsWindow() { DataContext = cf };
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

        private void SetGammaColorFilterCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
