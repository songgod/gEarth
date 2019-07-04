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
    public class SetChromaKeyColorFilterCommand : CommandBinding
    {
        public SetChromaKeyColorFilterCommand()
        {
            Command = CommandLib.SetChromaKeyColorFilterCommand;
            CanExecute += SetChromaKeyColorFilterCommand_CanExecute;
            Executed += SetChromaKeyColorFilterCommand_Executed;
        }

        private void SetChromaKeyColorFilterCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepChromaKeyColorFilter cf = new oepChromaKeyColorFilter();
            foreach (var layer in Project.CurrentMap.Layers)
            {
                oepImageLayer imglyr = layer as oepImageLayer;
                if (imglyr != null)
                {
                    imglyr.ColorFilters.Clear();
                    imglyr.ColorFilters.Add(cf);
                }
            }
            ChromaKeyColorFilterOptionsWindow w = new ChromaKeyColorFilterOptionsWindow() { DataContext = cf };
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

        private void SetChromaKeyColorFilterCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
