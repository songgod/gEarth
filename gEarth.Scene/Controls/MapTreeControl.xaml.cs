using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

namespace gEarth.Scene.Controls
{
    /// <summary>
    /// Interaction logic for MapTreeControl.xaml
    /// </summary>
    public partial class MapTreeControl : UserControl
    {
        public MapTreeControl()
        {
            Items = new ObservableCollection<object>();
            this.DataContext = this;
            InitializeComponent();
        }

        public void InitMap(gEarthPack.oepMap map)
        {
            if (map == null)
                return;
            Items.Clear();
            Items.Add(map.Layers);
            Items.Add(map.Extensions);
        }

        internal ObservableCollection<Object> Items
        {
            get { return (ObservableCollection<Object>)GetValue(ItemsProperty); }
            set { SetValue(ItemsProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Items.  This enables animation, styling, binding, etc...
        internal static readonly DependencyProperty ItemsProperty =
            DependencyProperty.Register("Items", typeof(ObservableCollection<Object>), typeof(MapTreeControl), new PropertyMetadata(null));



        public gEarthPack.oepViewpoint SelectViewpoint
        {
            get { return (gEarthPack.oepViewpoint)GetValue(SelectViewpointProperty); }
            set { SetValue(SelectViewpointProperty, value); }
        }

        // Using a DependencyProperty as the backing store for SelectViewpoint.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SelectViewpointProperty =
            DependencyProperty.Register("SelectViewpoint", typeof(gEarthPack.oepViewpoint), typeof(MapTreeControl), new PropertyMetadata(null));



        private void ContentControl_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            ContentControl cc = sender as ContentControl;
            gEarthPack.oepViewpoint vp = cc.DataContext as gEarthPack.oepViewpoint;
            SelectViewpoint = vp;
        }
    }
}
