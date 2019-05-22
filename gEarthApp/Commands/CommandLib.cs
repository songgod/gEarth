using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace gEarthApp.Commands
{
    public static class CommandLib
    {
        static CommandLib()
        {
            Open = new RoutedUICommand("Open", "Open", typeof(CommandLib));
        }
        public static RoutedUICommand Open { get; set; }
    }
}
