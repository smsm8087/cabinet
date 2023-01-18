namespace MapEditor
{
    partial class PalletForm
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
            this.ui_msPallet = new System.Windows.Forms.MenuStrip();
            this.파일ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.열기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.설정ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.타일사이즈ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ui_msPallet.SuspendLayout();
            this.SuspendLayout();
            // 
            // ui_msPallet
            // 
            this.ui_msPallet.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일ToolStripMenuItem,
            this.설정ToolStripMenuItem});
            this.ui_msPallet.Location = new System.Drawing.Point(0, 0);
            this.ui_msPallet.Name = "ui_msPallet";
            this.ui_msPallet.Size = new System.Drawing.Size(800, 24);
            this.ui_msPallet.TabIndex = 0;
            this.ui_msPallet.Text = "menuStrip1";
            // 
            // 파일ToolStripMenuItem
            // 
            this.파일ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.열기ToolStripMenuItem});
            this.파일ToolStripMenuItem.Name = "파일ToolStripMenuItem";
            this.파일ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.파일ToolStripMenuItem.Text = "파일";
            // 
            // 열기ToolStripMenuItem
            // 
            this.열기ToolStripMenuItem.Name = "열기ToolStripMenuItem";
            this.열기ToolStripMenuItem.Size = new System.Drawing.Size(98, 22);
            this.열기ToolStripMenuItem.Text = "열기";
            this.열기ToolStripMenuItem.Click += new System.EventHandler(this.열기ToolStripMenuItem_Click);
            // 
            // 설정ToolStripMenuItem
            // 
            this.설정ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.타일사이즈ToolStripMenuItem});
            this.설정ToolStripMenuItem.Name = "설정ToolStripMenuItem";
            this.설정ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.설정ToolStripMenuItem.Text = "설정";
            // 
            // 타일사이즈ToolStripMenuItem
            // 
            this.타일사이즈ToolStripMenuItem.Name = "타일사이즈ToolStripMenuItem";
            this.타일사이즈ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            this.타일사이즈ToolStripMenuItem.Text = "타일 사이즈";
            this.타일사이즈ToolStripMenuItem.Click += new System.EventHandler(this.타일사이즈ToolStripMenuItem_Click);
            // 
            // PalletForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.ui_msPallet);
            this.MainMenuStrip = this.ui_msPallet;
            this.Name = "PalletForm";
            this.Text = "팔레트";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.PalletForm_Paint);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PalletForm_MouseDown);
            this.ui_msPallet.ResumeLayout(false);
            this.ui_msPallet.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip ui_msPallet;
        private System.Windows.Forms.ToolStripMenuItem 파일ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 열기ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 설정ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 타일사이즈ToolStripMenuItem;
    }
}