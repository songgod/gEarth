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
    /// Interaction logic for MeasureAreaWindow.xaml
    /// </summary>
    public partial class MeasureAreaWindow : Window
    {
        public MeasureAreaWindow()
        {
            InitializeComponent();
            Single = this;
        }

        public static MeasureAreaWindow Single { get; private set; }

        public EarthViewControl EarthViewCtrl { get; set; }

        private oepMeasureAreaHandler Handle { get; set; }

        private void Window_Closed(object sender, EventArgs e)
        {
            Single = null;
            EarthViewCtrl.render.Handlers.Remove(Handle);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Handle = new oepMeasureAreaHandler();
            this.DataContext = Handle;
            EarthViewCtrl.render.Handlers.Add(Handle);
        }
    }
}
