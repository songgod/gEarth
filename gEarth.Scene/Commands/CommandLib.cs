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
            RecordPathCommand = CreateCommand("RecordPathCommand");
            EditAnimationPathCommand = CreateCommand("EditAnimationPathCommand");
            MeasureDistanceHeightCommand = CreateCommand("MeasureDistanceHeightCommand");
            MeasureAreaCommand = CreateCommand("MeasureAreaCommand");
            MeasureVolumeCommand = CreateCommand("MeasureVolumeCommand");
            MeasureAngleCommand = CreateCommand("MeasureAngleCommand");
            MeasureSlopeAspectCommand = CreateCommand("MeasureSlopeAspectCommand");
            AnalysisVisibleLineCommand = CreateCommand("AnalysisVisibleLineCommand");
            AnalysisVisibleAreaCommand = CreateCommand("AnalysisVisibleAreaCommand");
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
        public static RoutedUICommand RecordPathCommand { get; set; }
        public static RoutedUICommand RecordScreenCommand { get; set; }
        public static RoutedUICommand EditAnimationPathCommand { get; set; }
        public static RoutedUICommand MeasureDistanceHeightCommand { get; set; }
        public static RoutedUICommand MeasureAreaCommand { get; set; }
        public static RoutedUICommand MeasureVolumeCommand { get; set; }
        public static RoutedUICommand MeasureAngleCommand { get; set; }
        public static RoutedUICommand MeasureSlopeAspectCommand { get; set; }
        public static RoutedUICommand AnalysisVisibleLineCommand { get; set; }
        public static RoutedUICommand AnalysisVisibleAreaCommand { get; set; }
        public static RoutedUICommand AnalysisProfileCommand { get; set; }
    }
}
