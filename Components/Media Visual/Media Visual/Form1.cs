using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace Media_Visual
{
    public partial class Form1 : Form
    {
        string FilePath = String.Empty, line;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog FileDialog1 = new OpenFileDialog();
            if (FileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                FilePath = FileDialog1.FileName;
                FilePath = FilePath.Replace(@"\", "/");
                button1.Enabled = false;
                button2.Enabled = true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("graph_files/Input_Data.txt"))
            {
                if (radioButton1.Checked)
                    sw.WriteLine("Degree");
                else if (radioButton2.Checked)
                    sw.WriteLine("Closeness");
                else
                    sw.WriteLine("Betweenness");

                sw.WriteLine(FilePath);
            }
            //Process p = Process.Start(@"Media Analysis.exe");
            Process p = new Process();
            p.StartInfo = new ProcessStartInfo("Media Analysis.exe");
            //p.StartInfo.WorkingDirectory = @"C:\Program Files\Chrome";
            p.StartInfo.CreateNoWindow = true;
            p.StartInfo.UseShellExecute = false;
            p.Start();
            listBox1.Items.Clear();
            string content = String.Empty;
            p.WaitForExit();
            p.Close();
            using (StreamReader sr = new StreamReader("graph_files/centrality.txt"))
            {
                while ((line = sr.ReadLine()) != null)
                {
                    listBox1.Items.Add(line);
                }
                sr.Close();
            }
            button1.Enabled = true;
            button2.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button2.Enabled = false;
        }
    }
}
