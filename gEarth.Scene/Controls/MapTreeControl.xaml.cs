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
    public delegate void SelectObjectChanged(Object obj);

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

        public event SelectObjectChanged OnSelectObjectChanged;

        public Object SelectObject
        {
            get { return (Object)GetValue(SelectObjectProperty); }
            set { SetValue(SelectObjectProperty, value); }
        }

        static void OnSelectObjectChangedCallback(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            MapTreeControl mtc = (MapTreeControl)obj;
            if(mtc.OnSelectObjectChanged!=null)
            {
                mtc.OnSelectObjectChanged.Invoke(mtc.SelectObject);
            }
        }

        // Using a DependencyProperty as the backing store for SelectObject.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SelectObjectProperty =
            DependencyProperty.Register("SelectObject", typeof(Object), typeof(MapTreeControl), new PropertyMetadata(null,new PropertyChangedCallback(OnSelectObjectChangedCallback)));

        private void cc_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            ContentControl cc = sender as ContentControl;
            SelectObject = cc.DataContext;
        }
    }
}
