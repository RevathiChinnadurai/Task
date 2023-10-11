using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Win32;


namespace WindowsFormsApp1
{
    public struct _wfs_devstatus
    {
        [MarshalAs(UnmanagedType.LPStr)] public string lpszPhysicalName;
        [MarshalAs(UnmanagedType.LPStr)] public string lpszWorkstationName;
        public UInt32 dwState;
    }
    public partial class Form1 : Form
    {

        [DllImport("C:\\Users\\FPBFHM2\\source\\repos\\MFCXFSInterface\\Debug\\MFCXFSInterface.dll", CharSet = CharSet.Unicode, ExactSpelling = true)]
        internal static extern IntPtr LoadXFS();
        [DllImport("C:\\Users\\FPBFHM2\\source\\repos\\MFCXFSInterface\\Debug\\MFCXFSInterface.dll", CharSet = CharSet.Unicode, ExactSpelling = true)]
        internal static extern IntPtr CleanXFS();

        [DllImport("C:\\Users\\FPBFHM2\\source\\repos\\MFCXFSInterface\\Debug\\MFCXFSInterface.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr GetDeviceStatus([MarshalAs(UnmanagedType.LPStr)] string devicetype);

        [DllImport("C:\\Users\\FPBFHM2\\source\\repos\\MFCXFSInterface\\Debug\\MFCXFSInterface.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr DeviceInformation([MarshalAs(UnmanagedType.LPStr)] string devicename);

        public Form1()
        {
            InitializeComponent();
            IntPtr res = LoadXFS();
            if (res != IntPtr.Zero)
            {
              //  label2.Text = "Startup";
            }

        }
        

 /*  private void button1_Click(object sender, EventArgs e)
        {    
            IntPtr result = GetDeviceStatus("Camera");
            if(result !=IntPtr.Zero)
            {
                label2.Text = "Camera Online";
            }
            else
            {
                label3.Text = "Camera Offline";
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            IntPtr result = GetDeviceStatus("Printer");
            if (result != IntPtr.Zero)
            {
                label3.Text = "Printer Online";
            }
            else
            {
                label3.Text = "Printer Offline";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {

            IntPtr result = GetDeviceStatus("Pinpad");
            if (result != IntPtr.Zero)
            {
                label4.Text = "Pinpad WFSOpen called";
            }
            else
            {
                label3.Text = "Pinpad Offline";
            }
        }*/

        

         private void Form1_Load(object sender, EventArgs e)
         {
           //  _wfs_devstatus dwstatus = new _wfs_devstatus();


             IntPtr result = GetDeviceStatus("Camera");
             if (result == IntPtr.Zero)
             {
                pictureBox5.Image = Properties.Resources.on;
               
                
            }
            else
            {
                pictureBox5.Image = Properties.Resources.off;
                button1.Enabled = false;
                button1.BackgroundImage = Properties.Resources.infoicon1;
                // label3.ForeColor = Color.Red;
                //  label2.Text = "Camera Offline";
            }

            IntPtr result1 = GetDeviceStatus("Printer");
            if (result1 == IntPtr.Zero)
            {
                pictureBox11.Image = Properties.Resources.on;
               
            }
            else
            {
                pictureBox11.Image = Properties.Resources.off;
                button2.BackgroundImage = Properties.Resources.infoicon1;
                button2.Enabled = false;
            }

            IntPtr result2 = GetDeviceStatus("Pinpad");
             if (result2 == IntPtr.Zero)
             {
                pictureBox6.Image = Properties.Resources.on;
                
            }
            else
            {
                pictureBox6.Image = Properties.Resources.off;
                button3.BackgroundImage = Properties.Resources.infoicon1;
                button3.Enabled = false;
            }
            IntPtr result3 = GetDeviceStatus("Sensor");
            if (result3 == IntPtr.Zero)
            {
                pictureBox12.Image = Properties.Resources.on;

            }
            else
            {
                pictureBox12.Image = Properties.Resources.off;
                button4.Enabled = false;
            
            }
            button5.Enabled = false;
            button6.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            IntPtr result = DeviceInformation("Camera");
            
                
            if (result == IntPtr.Zero)
            {
                //label2.Text = "Status Information";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            IntPtr result = DeviceInformation("Printer");
            if (result == IntPtr.Zero)
            {
                //label2.Text = "Status Information printer";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            IntPtr result = DeviceInformation("Pinpad");
            if (result == IntPtr.Zero)
            {
               // label2.Text = "Status Information Pinpad";
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            
        }

        private void button6_Click(object sender, EventArgs e)
        {

        }
    }
}
