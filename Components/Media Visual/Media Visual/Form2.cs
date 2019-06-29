using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;


namespace Media_Visual
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            String[] words = new String[320];
            string[] stringSeparators = new string[] { "\r\n", " " };

            String s = File.ReadAllText(Form1.FilePath);
            words = s.Split(stringSeparators, StringSplitOptions.None);
            //words = s.Split(' ', '\n');
            Microsoft.Msagl.GraphViewerGdi.GViewer viewer = new Microsoft.Msagl.GraphViewerGdi.GViewer();
            //create a graph object 
            Microsoft.Msagl.Drawing.Graph graph = new Microsoft.Msagl.Drawing.Graph("graph");
            int cnt = 2;
            int n = Int32.Parse(words[0]);
            int m = Int32.Parse(words[1]);
            string line;
            int count = 0;
            var mylist = new List<KeyValuePair<string, double>>();
            using (StreamReader sr = new StreamReader("graph_files/centrality.txt"))
            {
                line = sr.ReadLine();
                while (line != null)
                {
                    mylist.Add(new KeyValuePair<string, double>(count.ToString(), double.Parse(line, System.Globalization.CultureInfo.InvariantCulture)));
                    count++;
                    line = sr.ReadLine();
                }
                sr.Close();
            }
            mylist.Sort((x, y) => (y.Value.CompareTo(x.Value)));
            byte green=70;
            int div = n;
            for (int i = 0; i < n; i++)
            {
                line = mylist[i].Key;
                Microsoft.Msagl.Drawing.Node l = graph.AddNode(line);
                l.Attr.Shape = Microsoft.Msagl.Drawing.Shape.Circle;
                l.Attr.FillColor = new Microsoft.Msagl.Drawing.Color(0, green, 0);
                /*if (i < n / 4)
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.FromArgb(0x479DEE);
                else if (i < 2 * n / 4)
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.SeaGreen;
                else if (i < 3 * n / 4)
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.PaleGreen;
                else
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.MistyRose;*/

                if (i < 1)
                {
                    green = (byte)(green + (180 / div));
                    
                }
                else if (mylist[i].Value < mylist[i - 1].Value)
                {
                    div--;
                    green = (byte)(green + (180 / div));
                    
                }
            }//create the graph content 
            for (int i = 0; i < m; i++)
            {
                Microsoft.Msagl.Drawing.Edge x = graph.AddEdge(words[cnt], words[cnt + 2], words[cnt + 1]);
                x.Attr.ArrowheadAtTarget = Microsoft.Msagl.Drawing.ArrowStyle.None;
                cnt = cnt + 3;
            }
            //float range = 20;
            viewer.Graph = graph;
            //associate the viewer with the form 
            this.SuspendLayout();
            viewer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Controls.Add(viewer);
            this.ResumeLayout();
            //show the form 
            this.Visible = false;
        }
    }
}
