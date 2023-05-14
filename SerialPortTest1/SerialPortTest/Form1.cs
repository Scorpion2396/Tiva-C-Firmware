using System;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;

namespace SerialPortApp
{
    public partial class Form1 : Form
    {
        private SerialPort _serialPort;

        public Form1()
        {
            InitializeComponent();
            // Populate the list of available COM ports
            string[] ports = SerialPort.GetPortNames();
            cmbComPorts.Items.AddRange(ports);
        }

        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            // Set the filter to only show .bin files
            openFileDialog1.Filter = "Binary Files (*.bin)|*.bin";

            // Open a file dialog to select a .bin file
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // Display the selected file name in a text box
                txtFilePath.Text = openFileDialog1.FileName;
            }
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            // Make sure a file is selected
            if (string.IsNullOrEmpty(txtFilePath.Text))
            {
                MessageBox.Show("Please select a file to send.");
                return;
            }

            // Make sure a COM port is selected
            if (string.IsNullOrEmpty(cmbComPorts.Text))
            {
                MessageBox.Show("Please select a COM port.");
                return;
            }

            // Make sure a valid baud rate is entered
            int baudRate;
            if (!int.TryParse(txtBaudRate.Text, out baudRate))
            {
                MessageBox.Show("Please enter a valid baud rate.");
                return;
            }

            // Open the serial port
            _serialPort = new SerialPort(cmbComPorts.Text, baudRate);
            _serialPort.Open();

            // Send test byte 0xAA
            try
            {
                byte[] testBytes = { 0xAA };
                _serialPort.Write(testBytes, 0, testBytes.Length);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error sending test byte over serial port: " + ex.Message);
            }


            // Wait for an ACK back after sending the size of the file
            byte[] ackBufferboot = new byte[1];
            DateTime start = DateTime.Now;

            while ((DateTime.Now - start).TotalMilliseconds < 5000)
            {
                _serialPort.Read(ackBufferboot, 0, 1);
                if (ackBufferboot[0] == 0x55)
                {
                    break;
                }
            }
            if (ackBufferboot[0] != 0x55)
            {
                MessageBox.Show("Error: Did not receive ack back from bootloader.");
                return;
            }




            // Get the size of the file
            long fileSize = new FileInfo(txtFilePath.Text).Length;
    
            // Send the file size as the first 4 bytes
            byte[] sizeBytes = BitConverter.GetBytes(fileSize);
            _serialPort.Write(sizeBytes, 0, 4);
            _serialPort.DiscardOutBuffer(); // Clear the buffer


            // Wait for an ACK back after sending the size of the file
            byte[] ackBuffer = new byte[1];
            DateTime start1 = DateTime.Now;

            while ((DateTime.Now - start1).TotalMilliseconds < 5000)
            {
                _serialPort.Read(ackBuffer, 0, 1);
                if (ackBuffer[0] == 0x55)
                {
                    break;
                }
            }
            if (ackBuffer[0] != 0x55)
            {
                MessageBox.Show("Error: Did not receive ACK back.");
                return;
            }
 


			// Send the file data, 4 bytes at a time
            int packet_size = 1024;
            bool ack_received = false;
            byte[] ackdata = new byte[1];

			// Send the file data, 4 bytes at a time
			using (var reader = new BinaryReader(File.OpenRead(txtFilePath.Text)))
			{
				byte[] buffer = new byte[4];
				for (int i = 0; i < fileSize; i++)
				{
					
                    if((i != 0) && (i % packet_size) == 0)
                    {
                        // Wait for an ACK back after sending the size of the file
                        ack_received = true;

                        while (ack_received)
                        {
                            _serialPort.Read(ackdata, 0, 1);
                            if (ackdata[0] == 0x55)
                            {
                                ack_received = false;
                            }
                        }
                    }

                    reader.Read(buffer, 0, 1);
					_serialPort.Write(buffer, 0, 1);
				}
			}



            // Close the serial port
            _serialPort.Close();

            MessageBox.Show("File sent successfully.");
        }
    }
}


