namespace _2D_Game_Tool
{
	partial class Form_Main
	{
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		/// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form 디자이너에서 생성한 코드

		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.ui_Tool_Menu_File = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.ui_Tool_Menu_TileSetting = new System.Windows.Forms.ToolStripMenuItem();
			this.ui_Tool_Menu_FloorIndex_Setting = new System.Windows.Forms.ToolStripMenuItem();
			this.myTooltip = new System.Windows.Forms.ToolTip(this.components);
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ui_Tool_Menu_File,
            this.ui_Tool_Menu_TileSetting});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(798, 28);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// ui_Tool_Menu_File
			// 
			this.ui_Tool_Menu_File.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.loadToolStripMenuItem});
			this.ui_Tool_Menu_File.Name = "ui_Tool_Menu_File";
			this.ui_Tool_Menu_File.Size = new System.Drawing.Size(51, 24);
			this.ui_Tool_Menu_File.Text = "파일";
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.BackColor = System.Drawing.Color.White;
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
			this.saveToolStripMenuItem.Text = "Save";
			this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
			// 
			// loadToolStripMenuItem
			// 
			this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
			this.loadToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
			this.loadToolStripMenuItem.Text = "Load";
			this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
			// 
			// ui_Tool_Menu_TileSetting
			// 
			this.ui_Tool_Menu_TileSetting.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ui_Tool_Menu_FloorIndex_Setting});
			this.ui_Tool_Menu_TileSetting.Name = "ui_Tool_Menu_TileSetting";
			this.ui_Tool_Menu_TileSetting.Size = new System.Drawing.Size(81, 24);
			this.ui_Tool_Menu_TileSetting.Text = "타일성정";
			// 
			// ui_Tool_Menu_FloorIndex_Setting
			// 
			this.ui_Tool_Menu_FloorIndex_Setting.Name = "ui_Tool_Menu_FloorIndex_Setting";
			this.ui_Tool_Menu_FloorIndex_Setting.Size = new System.Drawing.Size(144, 26);
			this.ui_Tool_Menu_FloorIndex_Setting.Text = "지형설정";
			this.ui_Tool_Menu_FloorIndex_Setting.Click += new System.EventHandler(this.ui_Tool_Menu_FloorIndex_Setting_Click);
			// 
			// timer1
			// 
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// Form_Main
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(798, 533);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "Form_Main";
			this.Text = "Form_Main";
			this.Load += new System.EventHandler(this.MapEditor_Load);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem ui_Tool_Menu_File;
		private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
		private System.Windows.Forms.ToolTip myTooltip;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.ToolStripMenuItem ui_Tool_Menu_TileSetting;
		private System.Windows.Forms.ToolStripMenuItem ui_Tool_Menu_FloorIndex_Setting;
	}
}

