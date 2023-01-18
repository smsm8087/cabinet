namespace AnimTool
{
    partial class EditPanel
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

        #region 구성 요소 디자이너에서 생성한 코드

        /// <summary> 
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.ui_tmrTick = new System.Windows.Forms.Timer(this.components);
            this.ui_cmRightMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.이름입력ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.피벗포인트설정ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.프레임번호ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ui_cmRightMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // ui_tmrTick
            // 
            this.ui_tmrTick.Interval = 10;
            this.ui_tmrTick.Tick += new System.EventHandler(this.ui_tmrTick_Tick);
            // 
            // ui_cmRightMenu
            // 
            this.ui_cmRightMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.이름입력ToolStripMenuItem,
            this.피벗포인트설정ToolStripMenuItem,
            this.프레임번호ToolStripMenuItem});
            this.ui_cmRightMenu.Name = "ui_cmRightMenu";
            this.ui_cmRightMenu.Size = new System.Drawing.Size(181, 92);
            // 
            // 이름입력ToolStripMenuItem
            // 
            this.이름입력ToolStripMenuItem.Name = "이름입력ToolStripMenuItem";
            this.이름입력ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.이름입력ToolStripMenuItem.Text = "이름 입력";
            this.이름입력ToolStripMenuItem.Click += new System.EventHandler(this.이름입력ToolStripMenuItem_Click);
            // 
            // 피벗포인트설정ToolStripMenuItem
            // 
            this.피벗포인트설정ToolStripMenuItem.Name = "피벗포인트설정ToolStripMenuItem";
            this.피벗포인트설정ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.피벗포인트설정ToolStripMenuItem.Text = "피벗포인트 설정";
            this.피벗포인트설정ToolStripMenuItem.Click += new System.EventHandler(this.피벗포인트설정ToolStripMenuItem_Click);
            // 
            // 프레임번호ToolStripMenuItem
            // 
            this.프레임번호ToolStripMenuItem.Name = "프레임번호ToolStripMenuItem";
            this.프레임번호ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.프레임번호ToolStripMenuItem.Text = "프레임 번호";
            this.프레임번호ToolStripMenuItem.Click += new System.EventHandler(this.프레임번호ToolStripMenuItem_Click);
            // 
            // EditPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "EditPanel";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.EditPanel_Paint);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.EditPanel_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.EditPanel_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.EditPanel_MouseUp);
            this.ui_cmRightMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer ui_tmrTick;
        private System.Windows.Forms.ContextMenuStrip ui_cmRightMenu;
        private System.Windows.Forms.ToolStripMenuItem 이름입력ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 피벗포인트설정ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 프레임번호ToolStripMenuItem;
    }
}
