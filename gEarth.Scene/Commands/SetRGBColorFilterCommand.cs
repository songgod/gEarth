using gEarth.Scene.Windows;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class SetRGBColorFilterCommand : CommandBinding
    {
        public SetRGBColorFilterCommand()
        {
            Command = CommandLib.SetRGBColorFilterCommand;
            CanExecute += SetRGBColorFilterCommand_CanExecute;
            Executed += SetRGBColorFilterCommand_Executed;
        }

        private void SetRGBColorFilterCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepRGBColorFilter cf = new oepRGBColorFilter();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if(imglyr!=null)
                {
                    imglyr.ColorFilters.Clear();
                    imglyr.ColorFilters.Add(cf);
                }
            }
            RGBColorFilterOptionsWindow w = new RGBColorFilterOptionsWindow() { DataContext = cf };
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

        private void SetRGBColorFilterCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
