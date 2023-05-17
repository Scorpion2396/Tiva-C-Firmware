using System;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;

namespace SerialPortApp
{
    public partial class Form1 : Form
    {
        private SerialPort _serialPort;
        private int PacketSize;

        private int baudRate;
        

        public Form1()
        {
            InitializeComponent();
            
            // Populate the list of available COM ports
            string[] ports = SerialPort.GetPortNames();
            cmbComPorts.Items.AddRange(ports);
            // Set the default comm port
            //cmbComPorts.SelectedIndex = 0;

            // Populate the list of Baud rate
            txtBaudRate.Items.Add("9600");
            txtBaudRate.Items.Add("115200");
            txtBaudRate.Items.Add("230400");
            // Set the default baud rate to 115200
            txtBaudRate.SelectedIndex = 1;
            
            // Populate the list of Data packets
            dataPacketSize.Items.Add("512b");
            dataPacketSize.Items.Add("1Kb");
            dataPacketSize.Items.Add("2Kb");
            dataPacketSize.Items.Add("4Kb");
             // Set the default packet size to 1KB
            dataPacketSize.SelectedIndex = 1;
        }



        private void UpdateProgress(int percentage)
        {
            lblProgress.Text = $"{percentage}%";
            lblProgress.Refresh(); // Force an immediate update of the label's display
        }

        private void LogMessage(string message)
        {
            logBox.AppendText(message + Environment.NewLine);
        }

       
        private void WaitForAck()
        {

            // Check if the serial port is open
            if (!_serialPort.IsOpen)
            {
                LogMessage("Error: Serial port is not open.\n");
                MessageBox.Show("Serial port is not open. Please connect the device and try again.");
                return;
            }
            // Wait for an ACK back after sending the size of the file
            byte[] ackBuffer = new byte[1];
            DateTime start1 = DateTime.Now;
            int timeout_time_ms = 2000;  // Set the read timeout to 2000 milliseconds

            _serialPort.ReadTimeout = timeout_time_ms; 

            try
            {
                while ((DateTime.Now - start1).TotalMilliseconds < timeout_time_ms)
                {
                        _serialPort.Read(ackBuffer, 0, 1);
                        try
                        {
                            if (ackBuffer[0] == 0x55)
                            {
                            //    LogMessage("ACK back received.\n");
                                return;
                            }
                        }
                        catch(Exception ex)
                        {
                            LogMessage("Error reading from serial port: " + ex.Message + "\n");
                        }
                        

                }
            }
            catch (Exception ex)
            {
                LogMessage("Error: Did not receive ACK back.\n" + ex.Message + "\n");
            }

            // Close the serial port
            //_serialPort.Close();

            MessageBox.Show("Error: Did not receive ACK back.\n");
            Application.Restart();
            Environment.Exit(1);
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
            LogMessage("Flashing process started.\n");
            progressBar.Visible = true;
            lblProgress.Visible = true;

            // Make sure a file is selected
            if (string.IsNullOrEmpty(txtFilePath.Text))
            {
                LogMessage("Please select a file to send.\n");
                return;
            }

            // Make sure a COM port is selected
            if (string.IsNullOrEmpty(cmbComPorts.Text))
            {
                LogMessage("Please select a COM port.\n");
                return;
            }


            // Make sure a Data packet size  is selected
            if (string.IsNullOrEmpty(dataPacketSize.Text))
            {
                LogMessage("Please select a data packet size.\n");
                return;
            }
            else
            {
                switch (dataPacketSize.SelectedIndex)
                {
                    case 0:
                        PacketSize = 512;
                        break;

                    case 1:
                        PacketSize = 1024;
                        break;

                    case 2:
                        PacketSize = 2048;
                        break;

                    case 3:
                        PacketSize = 4096;
                        break;

                }
            }

            // Make sure a Data packet size  is selected
            if (string.IsNullOrEmpty(txtBaudRate.Text))
            {
                LogMessage("Please select the baud rate.\n");
                return;
            }
            else
            {
                switch (txtBaudRate.SelectedIndex)
                {
                    case 0:
                        baudRate = 9600;
                        break;

                    case 1:
                        baudRate = 115200;
                        break;

                    case 2:
                        baudRate = 230400;
                        break;
                }
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
                LogMessage("Error sending test byte over serial port: \n" + ex.Message);
            }


            // Wait for an ACK back after sending the hand shaking data
            WaitForAck();

            LogMessage("Hand shaking done with bootloader\n");


            // Get the size of the file
            long fileSize = new FileInfo(txtFilePath.Text).Length;
    
            // Send the file size as the first 4 bytes
            byte[] sizeBytes = BitConverter.GetBytes(fileSize);
            _serialPort.Write(sizeBytes, 0, 4);
            _serialPort.DiscardOutBuffer(); // Clear the buffer


            // Wait for an ACK back after sending the size of the file
            WaitForAck();
 


			// Send the file data, a bytes at a time
            int progressPercentage;

			// Send the file data, 4 bytes at a time
			using (var reader = new BinaryReader(File.OpenRead(txtFilePath.Text)))
			{
				byte[] buffer = new byte[4];
				for (int i = 0; i < fileSize; i++)
				{
					
                    if((i != 0) && (i % PacketSize) == 0)
                    {
                        // Wait for an ACK back after sending the size of the file
                        byte[] data_ackBuffer = new byte[1];
                        WaitForAck();
                    }

                    reader.Read(buffer, 0, 1);
					_serialPort.Write(buffer, 0, 1);

                    // Calculate the progress percentage
                    progressPercentage = (int)(((double)i / fileSize) * 100);
                    // Update the progress bar value
                    progressBar.Value = progressPercentage;
                    // Update the label text
                    UpdateProgress(progressPercentage);
				}

                // Update the progress bar value to 100%
                    progressBar.Value = 100;
                    UpdateProgress(100);

			}

            // Close the serial port
            _serialPort.Close();

            LogMessage("Flashing completed!!!\n");
        }
    }
}


