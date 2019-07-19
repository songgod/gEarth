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
using gEarthPack;
using gEarth.Scene.Controls;
using System.IO;

namespace gEarth.Scene.Windows
{
    /// <summary>
    /// Interaction logic for RecordScreenWindow.xaml
    /// </summary>
    public partial class RecordScreenWindow : Window
    {
        public RecordScreenWindow()
        {
            InitializeComponent();
            Single = this;
            initrecordname();
        }

        public static RecordScreenWindow Single { get; set; }

        public EarthViewControl EarthViewCtrl { get; set; }

        private oepRecordScreenHandler RecordScreenHandler { get; set; }

        private void start_Click(object sender, RoutedEventArgs e)
        {
            string rcdurl = tbName.Tag as string;
            if(File.Exists(rcdurl))
            {
                string msg = this.Resources["recordexisterr"] as string;
                MessageBox.Show(msg);
                return;
            }
            btnstart.IsEnabled = false;
            btnstop.IsEnabled = true;

            RecordScreenHandler = new oepRecordScreenHandler(rcdurl, 25.0f);
            EarthViewCtrl.render.Handlers.Add(RecordScreenHandler);
            RecordScreenHandler.Start();
        }

        private void initrecordname()
        {
            string temppath = Project.TempPath;
            int i = 0;
            string recordName = "Record" + i.ToString();
            string recordUrl = temppath + recordName + ".p";
            while (File.Exists(recordUrl))
            {
                i++;
                recordName = "Record" + i.ToString();
                recordUrl = temppath + recordName + ".p";
            }
            tbName.Text = recordName;
            tbName.Tag = recordUrl;
        }

        private void stop_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Single = null;
            if(RecordScreenHandler!=null)
            {
                RecordScreenHandler.Stop();
                RecordScreenHandler.Save();
                EarthViewCtrl.render.Handlers.Remove(RecordScreenHandler);
                oepAnimationPathExtension ape = null;
                foreach (var es in Project.CurrentMap.Extensions)
                {
                    ape = es as oepAnimationPathExtension;
                    if (ape != null)
                        break;
                }

                if(ape==null)
                {
                    ape = new oepAnimationPathExtension();
                    Project.CurrentMap.Extensions.Add(ape);
                }

                ape.AnimationPaths.Add(new oepAnimationPath() { Name = tbName.Text, Url = tbName.Tag as string });
            }
        }
    }
}
