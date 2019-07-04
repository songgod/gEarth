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
    /// Interaction logic for ChromaKeyColorFilterOptionsWindow.xaml
    /// </summary>
    public partial class ChromaKeyColorFilterOptionsWindow : Window
    {
        public ChromaKeyColorFilterOptionsWindow()
        {
            InitializeComponent();
        }

        private void TextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            float v = 0;
            e.Handled = !float.TryParse(e.Text, out v);
        }
    }
}
