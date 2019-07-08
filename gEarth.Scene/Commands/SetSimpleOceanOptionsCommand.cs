using gEarth.Scene.Windows;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public class SetSimpleOceanOptionsCommand : CommandBinding
    {
        public SetSimpleOceanOptionsCommand()
        {
            Command = CommandLib.SetSimpleOceanOptionsCommand;
            CanExecute += SetSimpleOceanOptionsCommand_CanExecute;
            Executed += SetSimpleOceanOptionsCommand_Executed;
        }

        private void SetSimpleOceanOptionsCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            oepSimpleOceanLayer ol = null;
            foreach (var lyr in Project.CurrentMap.Layers)
            {
                ol = lyr as oepSimpleOceanLayer;
                if (ol != null)
                {
                    break;
                }
            }
            if (ol == null)
            {
                string wmimg = Directory.GetCurrentDirectory() + "\\data\\water_modulate.png";
                if (!File.Exists(wmimg))
                {
                    throw new Exception("water_modulate.png is not exist");
                }
                    
                ol = new oepSimpleOceanLayer(new oepSimpleOceanLayerOptions() { TextureUrl = wmimg });
                Project.CurrentMap.Layers.Add(ol);
            }

            SimpleOceanOptionsWindow sw = new SimpleOceanOptionsWindow() { DataContext = ol };
            sw.ShowDialog();
        }

        private void SetSimpleOceanOptionsCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = Project.CurrentMap != null;
            e.Handled = true;
        }
    }
}
