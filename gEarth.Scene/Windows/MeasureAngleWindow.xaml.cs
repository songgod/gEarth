﻿using gEarth.Scene.Controls;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace gEarth.Scene.Windows
{
    /// <summary>
    /// MeasureAngleWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MeasureAngleWindow : Window
    {
        public MeasureAngleWindow()
        {
            InitializeComponent();
            Single = this;
        }

        public static MeasureAngleWindow Single { get; private set; }

        public EarthViewControl EarthViewCtrl { get; set; }

        private oepMeasureAngleHandler Handle { get; set; }

        private void Window_Closed(object sender, EventArgs e)
        {
            Single = null;
            EarthViewCtrl.render.Handlers.Remove(Handle);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Handle = new oepMeasureAngleHandler();
            this.DataContext = Handle;
            EarthViewCtrl.render.Handlers.Add(Handle);
        }
    }
}
