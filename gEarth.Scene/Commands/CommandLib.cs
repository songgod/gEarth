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
            AddArcGISImageLayerCommand = CreateCommand("AddArcGISImageLayerCommand");
            AddBingImageLayerCommand = CreateCommand("AddBingImageLayerCommand");
            SetBrightnessColorFilterCommand = CreateCommand("SetBrightnessColorFilterCommand");
            SetChromaKeyColorFilterCommand = CreateCommand("SetChromaKeyColorFilterCommand");
            SetCMYKColorFilterCommand = CreateCommand("SetCMYKColorFilterCommand");
            SetGammaColorFilterCommand = CreateCommand("SetGammaColorFilterCommand");
            SetHSLColorFilterCommand = CreateCommand("SetHSLColorFilterCommand");
            SetRGBColorFilterCommand = CreateCommand("SetRGBColorFilterCommand");
            SetSimpleSkyOptionsCommand = CreateCommand("SetSimpleSkyOptionsCommand");
            SetSimpleOceanOptionsCommand = CreateCommand("SetSimpleOceanOptionsCommand");
            AddViewpointCommand = CreateCommand("AddViewpointCommand");
            RecordScreenCommand = CreateCommand("RecordScreenCommand");
            EditAnimationPathCommand = CreateCommand("EditAnimationPathCommand");
            MesureDistanceCommand = CreateCommand("MesureDistanceCommand");
            MesureAreaCommand = CreateCommand("MesureAreaCommand");
            MesureVolumeCommand = CreateCommand("MesureVolumeCommand");
            MesureAngleCommand = CreateCommand("MesureAngleCommand");
            MesureHeightCommand = CreateCommand("MesureHeightCommand");
            AnalysisVisbleCommand = CreateCommand("AnalysisVisbleCommand");
            AnalysisProfileCommand = CreateCommand("AnalysisProfileCommand");
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
        public static RoutedUICommand AddArcGISImageLayerCommand { get; set; }
        public static RoutedUICommand AddBingImageLayerCommand { get; set; }
        public static RoutedUICommand SetBrightnessColorFilterCommand { get; set; }
        public static RoutedUICommand SetChromaKeyColorFilterCommand { get; set; }
        public static RoutedUICommand SetCMYKColorFilterCommand { get; set; }
        public static RoutedUICommand SetGammaColorFilterCommand { get; set; }
        public static RoutedUICommand SetHSLColorFilterCommand { get; set; }
        public static RoutedUICommand SetRGBColorFilterCommand { get; set; }
        public static RoutedUICommand SetSimpleSkyOptionsCommand { get; set; }
        public static RoutedUICommand SetSimpleOceanOptionsCommand { get; set; }
        public static RoutedUICommand AddViewpointCommand { get; set; }
        public static RoutedUICommand RecordScreenCommand { get; set; }
        public static RoutedUICommand EditAnimationPathCommand { get; set; }
        public static RoutedUICommand MesureDistanceCommand { get; set; }
        public static RoutedUICommand MesureAreaCommand { get; set; }
        public static RoutedUICommand MesureVolumeCommand { get; set; }
        public static RoutedUICommand MesureAngleCommand { get; set; }
        public static RoutedUICommand MesureHeightCommand { get; set; }
        public static RoutedUICommand AnalysisVisbleCommand { get; set; }
        public static RoutedUICommand AnalysisProfileCommand { get; set; }
    }
}
