using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarth.Scene.Commands
{
    public static class CommandLib
    {
        static CommandLib()
        {
            OpenMap = CreateCommand("OpenMap");
            NewMap = CreateCommand("NewMap");
            SaveMap = CreateCommand("SaveMap");
            SaveMapAs = CreateCommand("SaveMapAs");
            AddGdalImageLayerCommand = CreateCommand("AddGdalImageLayerCommand");
            AddGdalElevationLayerCommand = CreateCommand("AddGdalEelvationLayerCommand");
        }
        private static RoutedUICommand CreateCommand(string name)
        {
            return new RoutedUICommand(name, name, typeof(CommandLib));
        }
        public static RoutedUICommand OpenMap { get; set; }
        public static RoutedUICommand NewMap { get; set; }
        public static RoutedUICommand SaveMap { get; set; }
        public static RoutedUICommand SaveMapAs { get; set; }
        public static RoutedUICommand AddGdalImageLayerCommand { get; set; }
        public static RoutedUICommand AddGdalElevationLayerCommand { get; set; }
    }
}
