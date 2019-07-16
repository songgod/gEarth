using gEarth.Scene.Controls;
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
    public class AddViewpointCommand : CommandBinding
    {
        public AddViewpointCommand()
        {
            Command = CommandLib.AddViewpointCommand;
            CanExecute += AddViewpointCommand_CanExecute;
            Executed += AddViewpointCommand_Executed;
        }

        private void AddViewpointCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EarthViewControl evc = e.Parameter as EarthViewControl;
            if (evc == null)
                return;
            
            oepViewpointsExtension oepve = null;
            foreach (var item in Project.CurrentMap.Extensions)
            {
                if(item is oepViewpointsExtension)
                {
                    oepve = (oepViewpointsExtension)item;
                    break;
                }
            }
            if (oepve == null)
            {
                oepve = new oepViewpointsExtension();
                Project.CurrentMap.Extensions.Add(oepve);
            }
            oepViewpoint vp = evc.render.Viewpoint;
            vp.Name = "Viewpoint";
            oepve.ViewPoints.Add(vp);
            AddViewpointOptionsWindow w = new AddViewpointOptionsWindow() { DataContext = vp };
            w.ShowDialog();
        }

        private void AddViewpointCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
