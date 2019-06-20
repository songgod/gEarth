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
            Open = new RoutedUICommand("Open", "Open", typeof(CommandLib));
            New = new RoutedUICommand("New", "New", typeof(CommandLib));
            Save = new RoutedUICommand("Save", "Save", typeof(CommandLib));
            SaveAs = new RoutedUICommand("SaveAs", "SaveAs", typeof(CommandLib));
        }
        public static RoutedUICommand Open { get; set; }
        public static RoutedUICommand New { get; set; }
        public static RoutedUICommand Save { get; set; }
        public static RoutedUICommand SaveAs { get; set; }
    }
}
