namespace SerialPortApp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private Label lblProgress;
        private TextBox logBox;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnSelectFile = new System.Windows.Forms.Button();
            this.txtFilePath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cmbComPorts = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtBaudRate = new System.Windows.Forms.ComboBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label4 = new System.Windows.Forms.Label();
            this.dataPacketSize = new System.Windows.Forms.ComboBox();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();

            // 
            // btnSelectFile
            // 
            this.btnSelectFile.Location = new System.Drawing.Point(420, 27);
            this.btnSelectFile.Name = "btnSelectFile";
            this.btnSelectFile.Size = new System.Drawing.Size(75, 23);
            this.btnSelectFile.TabIndex = 0;
            this.btnSelectFile.Text = "Select File";
            this.btnSelectFile.UseVisualStyleBackColor = true;
            this.btnSelectFile.Click += new System.EventHandler(this.btnSelectFile_Click);
            // 
            // txtFilePath
            // 
            this.txtFilePath.Location = new System.Drawing.Point(12, 29);
            this.txtFilePath.Name = "txtFilePath";
            this.txtFilePath.ReadOnly = true;
            this.txtFilePath.Size = new System.Drawing.Size(402, 20);
            this.txtFilePath.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "File Path:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 67);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "COM Port:";
            // 
            // cmbComPorts
            // 
            this.cmbComPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbComPorts.FormattingEnabled = true;
            this.cmbComPorts.Location = new System.Drawing.Point(12, 83);
            this.cmbComPorts.Name = "cmbComPorts";
            this.cmbComPorts.Size = new System.Drawing.Size(121, 21);
            this.cmbComPorts.TabIndex = 4;
			//
			// label3
			//
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 118);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(63, 13);
			this.label3.TabIndex = 5;
			this.label3.Text = "Baud Rate:";
			//
			// txtBaudRate
			//
            this.txtBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.txtBaudRate.FormattingEnabled = true;
            this.txtBaudRate.Location = new System.Drawing.Point(12, 134);
            this.txtBaudRate.Name = "txtBaudRate";
            this.txtBaudRate.Size = new System.Drawing.Size(121, 20);
            this.txtBaudRate.TabIndex = 6;
			//
			// btnSend
			//
			this.btnSend.Location = new System.Drawing.Point(420, 134);
			this.btnSend.Name = "btnSend";
			this.btnSend.Size = new System.Drawing.Size(75, 23);
			this.btnSend.TabIndex = 7;
			this.btnSend.Text = "Flash";
			this.btnSend.UseVisualStyleBackColor = true;
			this.btnSend.Click += new System.EventHandler(this.btnSend_Click);

            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(142, 67);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Data Packet Size:";
            // 
            // dataPacketSize
            // 
            this.dataPacketSize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.dataPacketSize.FormattingEnabled = true;
            this.dataPacketSize.Location = new System.Drawing.Point(142, 83);
            this.dataPacketSize.Name = "dataPacketSize";
            this.dataPacketSize.Size = new System.Drawing.Size(121, 21);
            this.dataPacketSize.TabIndex = 9;

            // Configure the properties of the ProgressBar control
            this.progressBar.Location = new System.Drawing.Point(12, 180);  // Set the desired location
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(350, 15);  // Set the desired size
            this.progressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;  // Set the progress bar style
            this.progressBar.TabIndex = 5;  // Set the desired tab index
            this.progressBar.Visible = false;  // Initially set the visibility to false

            // 
            // % Box
            // 
            lblProgress = new Label();
            lblProgress.Text = "0%";
            lblProgress.Location = new Point(progressBar.Left + progressBar.Width + 10, progressBar.Top);
            this.lblProgress.Visible = false;  // Initially set the visibility to false
            this.Controls.Add(lblProgress);

            // Initialize and configure the logBox control
            logBox = new TextBox();
            logBox.Multiline = true;
            logBox.ReadOnly = true;
            logBox.ScrollBars = ScrollBars.Vertical;
            logBox.Location = new Point(10, progressBar.Bottom + 10);
            logBox.Size = new Size(400, 200);
            this.Controls.Add(logBox);


			//
			// openFileDialog1
			//
			this.openFileDialog1.FileName = "openFileDialog1";
			//
			// Form1
			//
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(512, 512);
			this.Controls.Add(this.btnSend);
			this.Controls.Add(this.txtBaudRate);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.cmbComPorts);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
            this.Controls.Add(this.label4);
			this.Controls.Add(this.dataPacketSize);
			this.Controls.Add(this.txtFilePath);
			this.Controls.Add(this.btnSelectFile);
            this.Controls.Add(this.progressBar);
			this.Name = "Form1";
			this.Text = "Serial Port Application";
			this.ResumeLayout(false);
			this.PerformLayout();


		}

    #endregion

    private System.Windows.Forms.Button btnSelectFile;
    private System.Windows.Forms.TextBox txtFilePath;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.ComboBox cmbComPorts;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.ComboBox txtBaudRate;
    private System.Windows.Forms.Button btnSend;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.ComboBox dataPacketSize;
    private System.Windows.Forms.ProgressBar progressBar;
    private System.Windows.Forms.OpenFileDialog openFileDialog1;
    
	}
}
            
