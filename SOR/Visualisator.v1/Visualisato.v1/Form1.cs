using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Visualisato.v1
{
	public partial class Form1 : Form
	{
        Bitmap bmp;
        Graphics g;
        string fname = @"C:\Users\vadya\OneDrive\Рабочий стол\test.txt";
        public Form1()
		{
			InitializeComponent();

        }

		private void Form1_Load(object sender, EventArgs e)
		{


        }




        private void panel1_Paint(object sender, PaintEventArgs e)
		{
 
        }

		private void openFileToolStripMenuItem_Click(object sender, EventArgs e)
		{
            OpenFileDialog opfd = new OpenFileDialog();
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                fname = openFileDialog1.FileName;
            }
            
		}

		private void button1_Click(object sender, EventArgs e)
		{
            Graphics g = Graphics.FromHwnd(panel1.Handle);

            string[] strs = File.ReadAllText(fname).Split(',','\n', '\r',' ' , '\t');



            List<List<int>> M = new List<List<int>>();
            int k = 4;

            Int32.TryParse(strs[1], out int a);
            for (int i = 0; i < a; i++)
            {
                M.Add(new List<int>());
            }
            int count = 0;
            for (int i = 0; i < M.Count; i++)
            {
                Int32.TryParse(strs[3 + count], out int value2);
                for (int j = 0; j < value2 * 2; j++)
                {
                    Int32.TryParse(strs[k], out int value);
                    M[i].Add(value / 100);
                    k += 2;
                }

                count = M[i].Count * 2 + 1 + count;
                k = count + 4;
            }

            Pen pen = new Pen(Color.FromArgb(255, 0, 0, 0));

            for (int i = 0; i < M.Count; i++)
            {
                for (int j = 0; j < M[i].Count - 2; j += 2)
                {
                    g.DrawLine(pen, M[i][j], this.Height - M[i][j + 1], M[i][j + 2], this.Height - M[i][j + 3]);

                }
            }

        }

		private void button2_Click(object sender, EventArgs e)
		{
            panel1.Invalidate();
		}
	}
}



