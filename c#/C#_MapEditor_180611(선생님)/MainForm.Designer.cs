namespace MapEditor
{
    partial class MainForm
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
            this.ui_msMainMenu = new System.Windows.Forms.MenuStrip();
            this.도구ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.팔레트열기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileMap = new MapEditor.TileMap();
            this.설정ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.맵크기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ui_msMainMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // ui_msMainMenu
            // 
            this.ui_msMainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.도구ToolStripMenuItem,
            this.설정ToolStripMenuItem});
            this.ui_msMainMenu.Location = new System.Drawing.Point(0, 0);
            this.ui_msMainMenu.Name = "ui_msMainMenu";
            this.ui_msMainMenu.Size = new System.Drawing.Size(800, 24);
            this.ui_msMainMenu.TabIndex = 0;
            this.ui_msMainMenu.Text = "menuStrip1";
            // 
            // 도구ToolStripMenuItem
            // 
            this.도구ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.팔레트열기ToolStripMenuItem});
            this.도구ToolStripMenuItem.Name = "도구ToolStripMenuItem";
            this.도구ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.도구ToolStripMenuItem.Text = "도구";
            // 
            // 팔레트열기ToolStripMenuItem
            // 
            this.팔레트열기ToolStripMenuItem.Name = "팔레트열기ToolStripMenuItem";
            this.팔레트열기ToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
            this.팔레트열기ToolStripMenuItem.Text = "팔레트열기";
            this.팔레트열기ToolStripMenuItem.Click += new System.EventHandler(this.팔레트열기ToolStripMenuItem_Click);
            // 
            // tileMap
            // 
            this.tileMap.Location = new System.Drawing.Point(0, 27);
            this.tileMap.Name = "tileMap";
            this.tileMap.Size = new System.Drawing.Size(773, 402);
            this.tileMap.TabIndex = 1;
            // 
            // 설정ToolStripMenuItem
            // 
            this.설정ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.맵크기ToolStripMenuItem});
            this.설정ToolStripMenuItem.Name = "설정ToolStripMenuItem";
            this.설정ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.설정ToolStripMenuItem.Text = "설정";
            // 
            // 맵크기ToolStripMenuItem
            // 
            this.맵크기ToolStripMenuItem.Name = "맵크기ToolStripMenuItem";
            this.맵크기ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.맵크기ToolStripMenuItem.Text = "맵크기";
            this.맵크기ToolStripMenuItem.Click += new System.EventHandler(this.맵크기ToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 527);
            this.Controls.Add(this.tileMap);
            this.Controls.Add(this.ui_msMainMenu);
            this.MainMenuStrip = this.ui_msMainMenu;
            this.Name = "MainForm";
            this.Text = "MapEditor";
            this.ui_msMainMenu.ResumeLayout(false);
            this.ui_msMainMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip ui_msMainMenu;
        private System.Windows.Forms.ToolStripMenuItem 도구ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 팔레트열기ToolStripMenuItem;
        private TileMap tileMap;
        private System.Windows.Forms.ToolStripMenuItem 설정ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 맵크기ToolStripMenuItem;
    }
}

