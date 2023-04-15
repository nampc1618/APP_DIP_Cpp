using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CvToolWrapper;

namespace WfTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Bitmap bmp = new Bitmap("..\\..\\ImageTest\\hotgirl9.jpg");
            pictureBox1.Image = ImageProcessingToolsWrapper.threshold(bmp, 100);
        }
    }
}
