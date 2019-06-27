using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String[] words = new String[30];
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
            int cnt = 0;
            //create the graph content 
            for (int i = 0; i < 10; i++)
            {
                Microsoft.Msagl.Drawing.Edge x = graph.AddEdge(words[cnt], words[cnt + 2], words[cnt + 1]);
                x.Attr.ArrowheadAtTarget = Microsoft.Msagl.Drawing.ArrowStyle.None;
                cnt = cnt + 3;   
            }
            /*graph.AddEdge("B", "10", "C");
            graph.AddEdge("A", "C").Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
            graph.Directed = false;
            // =  Microsoft.Msagl.Drawing.ArrowStyle.None;
            graph.FindNode("A").Attr.FillColor = Microsoft.Msagl.Drawing.Color.Magenta;
            graph.FindNode("B").Attr.FillColor = Microsoft.Msagl.Drawing.Color.MistyRose;
            Microsoft.Msagl.Drawing.Node c = graph.FindNode("C");

            Microsoft.Msagl.Drawing.Edge x = graph.AddEdge("C", "D");
            x.Attr.ArrowheadAtTarget = Microsoft.Msagl.Drawing.ArrowStyle.None;
            c.Attr.FillColor = Microsoft.Msagl.Drawing.Color.PaleGreen;
            c.Attr.Shape = Microsoft.Msagl.Drawing.Shape.Diamond;*/
            //bind the graph to the viewer 
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
