namespace _2D_Game_Tool.Forms
{
	partial class Form_FloorIndexSetting
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

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
			this.components = new System.ComponentModel.Container();
			this.btn_Save = new System.Windows.Forms.Button();
			this.btn_Close = new System.Windows.Forms.Button();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.btn_Load = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btn_Save
			// 
			this.btn_Save.Location = new System.Drawing.Point(713, 46);
			this.btn_Save.Name = "btn_Save";
			this.btn_Save.Size = new System.Drawing.Size(75, 23);
			this.btn_Save.TabIndex = 2;
			this.btn_Save.Text = "저장";
			this.btn_Save.UseVisualStyleBackColor = true;
			this.btn_Save.Click += new System.EventHandler(this.btn_Save_Click);
			// 
			// btn_Close
			// 
			this.btn_Close.ForeColor = System.Drawing.Color.DarkSlateGray;
			this.btn_Close.Location = new System.Drawing.Point(713, 77);
			this.btn_Close.Name = "btn_Close";
			this.btn_Close.Size = new System.Drawing.Size(75, 23);
			this.btn_Close.TabIndex = 3;
			this.btn_Close.Text = "취소";
			this.btn_Close.UseVisualStyleBackColor = true;
			this.btn_Close.Click += new System.EventHandler(this.btn_Close_Click);
			// 
			// timer1
			// 
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			// 
			// btn_Load
			// 
			this.btn_Load.ForeColor = System.Drawing.Color.DarkSlateGray;
			this.btn_Load.Location = new System.Drawing.Point(713, 107);
			this.btn_Load.Name = "btn_Load";
			this.btn_Load.Size = new System.Drawing.Size(75, 23);
			this.btn_Load.TabIndex = 4;
			this.btn_Load.Text = "불러오기";
			this.btn_Load.UseVisualStyleBackColor = true;
			this.btn_Load.Click += new System.EventHandler(this.btn_Load_Click);
			this.btn_Load.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_Load_MouseDown);
			this.btn_Load.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btn_Load_MouseMove);
			this.btn_Load.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_Load_MouseUp);
			// 
			// Form_FloorIndexSetting
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.btn_Load);
			this.Controls.Add(this.btn_Close);
			this.Controls.Add(this.btn_Save);
			this.Name = "Form_FloorIndexSetting";
			this.Text = "Form_FloorIndexSetting";
			this.ResumeLayout(false);

		}

		#endregion
		private System.Windows.Forms.Button btn_Save;
		private System.Windows.Forms.Button btn_Close;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private System.Windows.Forms.Button btn_Load;
	}
}