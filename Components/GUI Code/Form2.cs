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
           // List<string> ls = new List<string>();
            String[] words = new String[320];
            OpenFileDialog odf = new OpenFileDialog();
            if (odf.ShowDialog() == DialogResult.OK)
            {
                string[] stringSeparators = new string[] { "\r\n", " " };

                String s = File.ReadAllText(odf.FileName);
                words = s.Split(stringSeparators, StringSplitOptions.None);
                //words = s.Split(' ', '\n');
            }
            Microsoft.Msagl.GraphViewerGdi.GViewer viewer = new Microsoft.Msagl.GraphViewerGdi.GViewer();
            //create a graph object 
            Microsoft.Msagl.Drawing.Graph graph = new Microsoft.Msagl.Drawing.Graph("graph");
            
            int cnt = 2;
            int n = Int32.Parse(words[0]);
            int m = Int32.Parse(words[1]);
            string line;
            int count = 0;
            var mylist = new List<KeyValuePair<string, int>>();

            using (StreamReader sr = new StreamReader("graph_files/centrality.txt"))
            {
                line = sr.ReadLine();
                while (line != null)
                {
                    mylist.Add(new KeyValuePair<string, int>(count.ToString(), Int32.Parse(line)));
                    count++;
                    line = sr.ReadLine();
                }
                sr.Close();
            }
            mylist.Sort((x, y) => (y.Value.CompareTo(x.Value)));


            float diff = 60 / n;
            float rad = 100;
            for (int i = 0; i < n; i++)
            {
                line = mylist[i].Key;
                Microsoft.Msagl.Drawing.Node l = graph.AddNode(line);

                l.Attr.Shape = Microsoft.Msagl.Drawing.Shape.Box;
                l.Attr.XRadius = rad;
                l.Attr.YRadius = rad;
                if (i < n / 3)
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.Green;
                else if (i < 2 * n / 3)
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.PaleGreen;
                else
                    l.Attr.FillColor = Microsoft.Msagl.Drawing.Color.MistyRose;
                rad = rad - diff;
            }
            //create the graph content 
            for (int i = 0; i < m ; i++)
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
            this.ShowDialog();
        
        }
    }
}
