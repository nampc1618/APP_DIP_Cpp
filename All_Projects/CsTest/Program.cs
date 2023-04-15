using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using TestWrapper;
using TestCLR;

//using CvToolWrapper;

namespace CsTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Bitmap bmp = new Bitmap("F:\\Nampc\\ComputerVision\\APP_DIP_Cpp\\All_Projects\\ImageTest\\ImageTest\\hotgirl.jepg");
            Wrapper.threshold(bmp, 120);

            Console.WriteLine(Wrapper.Add(10, 5));

            
            Console.WriteLine("Successfully!");
            Console.ReadLine();
        }
    }
}
