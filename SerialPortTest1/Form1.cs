using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SerialPortTest
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort = null;

        public Form1()
        {
            InitializeComponent();

            // Populate list of available COM ports
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                cbPort.Items.Add(port);
            }
        }

        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Binary files (*.bin)|*.bin";
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                tbFileName.Text = openFileDialog.FileName;
            }
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (serialPort == null || !serialPort.IsOpen)
            {
                MessageBox.Show("Please select a valid serial port and baud rate first.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (!File.Exists(tbFileName.Text))
            {
                MessageBox.Show("Please select a valid binary file first.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                // Open the binary file and get its size in bytes
                using (FileStream fs = new FileStream(tbFileName.Text, FileMode.Open, FileAccess.Read))
                {
                    int fileSize = (int)fs.Length;

                    // Send the file size as the first four bytes
                    byte[] fileSizeBytes = BitConverter.GetBytes(fileSize);
                    serialPort.Write(fileSizeBytes, 0, 4);

                    // Send the rest of the file one byte at a time
                    byte[] buffer = new byte[1];
                    int bytesRead = 0;
                    while ((bytesRead = fs.Read(buffer, 0, buffer.Length)) > 0)
                    {
                        serialPort.Write(buffer, 0, bytesRead);
                    }

                    MessageBox.Show("File sent successfully.", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error sending file: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (cbPort.SelectedIndex == -1)
            {
                MessageBox.Show("Please select a serial port.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                if (serialPort != null && serialPort.IsOpen)
                {
                    serialPort.Close();
                }

                serialPort = new SerialPort(cbPort.SelectedItem.ToString(), int.Parse(tbBaudRate.Text));
                serialPort.Open();

                MessageBox.Show("Serial port connected successfully.", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error connecting to serial port: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
