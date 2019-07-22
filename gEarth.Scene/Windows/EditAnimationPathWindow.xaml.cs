using gEarth.Scene.Controls;
using gEarthPack;
using System;
using System.Collections.Generic;
using System.IO;
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
    /// Interaction logic for EditAnimationPathWindow.xaml
    /// </summary>
    public partial class EditAnimationPathWindow : Window
    {
        public EditAnimationPathWindow()
        {
            InitializeComponent();
            Single = this;
            init();
        }

        public static EditAnimationPathWindow Single { get; set; }

        public EarthViewControl EarthViewCtrl { get; set; }

        public oepAnimationPath CurrentAnimationPath { get; set; }

        private double Time { get; set; }

        private void btnadd_Click(object sender, RoutedEventArgs e)
        {
            CurrentAnimationPath.ControlPoints.Add(oepControlPoint.MakeControlPoint(EarthViewCtrl.render, Time));
            Time += 2.0;
            btnok.IsEnabled = CurrentAnimationPath.ControlPoints.Count >= 2;
        }

        private void btnok_Click(object sender, RoutedEventArgs e)
        {
            if (CurrentAnimationPath == null)
                return;

            string rcdurl = tbName.Tag as string;
            if (File.Exists(rcdurl))
            {
                string msg = this.Resources["pathexisterr"] as string;
                MessageBox.Show(msg);
                return;
            }
            CurrentAnimationPath.Url = rcdurl;
            CurrentAnimationPath.Name = tbName.Text;
            CurrentAnimationPath.Save();
            Single = null;

            oepAnimationPathExtension ape = null;
            foreach (var es in Project.CurrentMap.Extensions)
            {
                ape = es as oepAnimationPathExtension;
                if (ape != null)
                    break;
            }

            if (ape == null)
            {
                ape = new oepAnimationPathExtension();
                Project.CurrentMap.Extensions.Add(ape);
            }

            ape.AnimationPaths.Add(CurrentAnimationPath);

            this.Close();
        }

        private void init()
        {
            string temppath = Project.TempPath;
            int i = 0;
            string recordName = "Path" + i.ToString();
            string recordUrl = temppath + recordName + ".p";
            while (File.Exists(recordUrl))
            {
                i++;
                recordName = "Record" + i.ToString();
                recordUrl = temppath + recordName + ".p";
            }
            tbName.Text = recordName;
            tbName.Tag = recordUrl;
            CurrentAnimationPath = new oepAnimationPath();
        }
    }
}
