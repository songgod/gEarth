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
    public class SetHSLColorFilterCommand : CommandBinding
    {
        public SetHSLColorFilterCommand()
        {
            Command = CommandLib.SetHSLColorFilterCommand;
            CanExecute += SetHSLColorFilterCommand_CanExecute;
            Executed += SetHSLColorFilterCommand_Executed;
        }

        private void SetHSLColorFilterCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepHSLColorFilter cf = new oepHSLColorFilter();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                    imglyr.ColorFilters.Add(cf);
                }
            }
            HSLColorFilterOptionsWindow w = new HSLColorFilterOptionsWindow() { DataContext = cf, Owner = System.Windows.Application.Current.MainWindow };
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

        private void SetHSLColorFilterCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
