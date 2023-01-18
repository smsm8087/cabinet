namespace MapEditer
{
    partial class Form1
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
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.Save = new System.Windows.Forms.ToolStripMenuItem();
            this.로드ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.ui_panel = new MapEditer.panelcontrol();
            this.Tap_Map = new System.Windows.Forms.TabControl();
            this.ui_tabpage = new MapEditer.TapControlMapPage1();
            this.ui_panel2 = new MapEditer.panelcontrol();
            this.ui_tabpage2 = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ui_btn_ok = new System.Windows.Forms.Button();
            this.ui_txt_col = new System.Windows.Forms.TextBox();
            this.ui_txt_row = new System.Windows.Forms.TextBox();
            this.ui_lb_col = new System.Windows.Forms.Label();
            this.ui_lb_row = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.Tap_Map.SuspendLayout();
            this.ui_tabpage.SuspendLayout();
            this.ui_tabpage2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1360, 28);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Save,
            this.로드ToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(51, 24);
            this.toolStripMenuItem1.Text = "파일";
            // 
            // Save
            // 
            this.Save.Name = "Save";
            this.Save.Size = new System.Drawing.Size(216, 26);
            this.Save.Text = "저장하기";
            this.Save.Click += new System.EventHandler(this.Save_Click);
            // 
            // 로드ToolStripMenuItem
            // 
            this.로드ToolStripMenuItem.Name = "로드ToolStripMenuItem";
            this.로드ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.로드ToolStripMenuItem.Text = "불러오기";
            this.로드ToolStripMenuItem.Click += new System.EventHandler(this.로드ToolStripMenuItem_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // ui_panel
            // 
            this.ui_panel.AutoScroll = true;
            this.ui_panel.Location = new System.Drawing.Point(12, 31);
            this.ui_panel.Name = "ui_panel";
            this.ui_panel.Size = new System.Drawing.Size(971, 718);
            this.ui_panel.TabIndex = 3;
            this.ui_panel.Paint += new System.Windows.Forms.PaintEventHandler(this.ui_panel_Paint);
            this.ui_panel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.ui_panel_MouseClick);
            this.ui_panel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ui_panel_MouseMove);
            // 
            // Tap_Map
            // 
            this.Tap_Map.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Tap_Map.Controls.Add(this.ui_tabpage);
            this.Tap_Map.Controls.Add(this.ui_tabpage2);
            this.Tap_Map.Font = new System.Drawing.Font("돋움", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.Tap_Map.Location = new System.Drawing.Point(985, 23);
            this.Tap_Map.Name = "Tap_Map";
            this.Tap_Map.SelectedIndex = 0;
            this.Tap_Map.Size = new System.Drawing.Size(363, 726);
            this.Tap_Map.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.Tap_Map.TabIndex = 1;
            // 
            // ui_tabpage
            // 
            this.ui_tabpage.AutoScroll = true;
            this.ui_tabpage.AutoScrollMinSize = new System.Drawing.Size(1000, 1000);
            this.ui_tabpage.BackColor = System.Drawing.Color.White;
            this.ui_tabpage.Controls.Add(this.ui_panel2);
            this.ui_tabpage.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ui_tabpage.Location = new System.Drawing.Point(4, 25);
            this.ui_tabpage.Name = "ui_tabpage";
            this.ui_tabpage.Padding = new System.Windows.Forms.Padding(3);
            this.ui_tabpage.Size = new System.Drawing.Size(355, 697);
            this.ui_tabpage.TabIndex = 0;
            this.ui_tabpage.Text = "이미지";
            // 
            // ui_panel2
            // 
            this.ui_panel2.AutoScroll = true;
            this.ui_panel2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ui_panel2.Location = new System.Drawing.Point(6, 15);
            this.ui_panel2.Name = "ui_panel2";
            this.ui_panel2.Size = new System.Drawing.Size(317, 720);
            this.ui_panel2.TabIndex = 0;
            this.ui_panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.ui_panel2_Paint);
            this.ui_panel2.MouseClick += new System.Windows.Forms.MouseEventHandler(this.ui_panel2_MouseClick);
            this.ui_panel2.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ui_panel2_MouseMove);
            // 
            // ui_tabpage2
            // 
            this.ui_tabpage2.Controls.Add(this.groupBox1);
            this.ui_tabpage2.Location = new System.Drawing.Point(4, 25);
            this.ui_tabpage2.Name = "ui_tabpage2";
            this.ui_tabpage2.Size = new System.Drawing.Size(355, 697);
            this.ui_tabpage2.TabIndex = 1;
            this.ui_tabpage2.Text = "타일설정";
            this.ui_tabpage2.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ui_btn_ok);
            this.groupBox1.Controls.Add(this.ui_txt_col);
            this.groupBox1.Controls.Add(this.ui_txt_row);
            this.groupBox1.Controls.Add(this.ui_lb_col);
            this.groupBox1.Controls.Add(this.ui_lb_row);
            this.groupBox1.Location = new System.Drawing.Point(0, 15);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(345, 261);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "타일행렬";
            // 
            // ui_btn_ok
            // 
            this.ui_btn_ok.Location = new System.Drawing.Point(65, 206);
            this.ui_btn_ok.Name = "ui_btn_ok";
            this.ui_btn_ok.Size = new System.Drawing.Size(111, 33);
            this.ui_btn_ok.TabIndex = 4;
            this.ui_btn_ok.Text = "확인";
            this.ui_btn_ok.UseVisualStyleBackColor = true;
            this.ui_btn_ok.Click += new System.EventHandler(this.ui_btn_ok_Click);
            // 
            // ui_txt_col
            // 
            this.ui_txt_col.Location = new System.Drawing.Point(51, 151);
            this.ui_txt_col.Name = "ui_txt_col";
            this.ui_txt_col.Size = new System.Drawing.Size(139, 25);
            this.ui_txt_col.TabIndex = 3;
            // 
            // ui_txt_row
            // 
            this.ui_txt_row.Location = new System.Drawing.Point(51, 74);
            this.ui_txt_row.Name = "ui_txt_row";
            this.ui_txt_row.Size = new System.Drawing.Size(139, 25);
            this.ui_txt_row.TabIndex = 2;
            // 
            // ui_lb_col
            // 
            this.ui_lb_col.AutoSize = true;
            this.ui_lb_col.Location = new System.Drawing.Point(22, 154);
            this.ui_lb_col.Name = "ui_lb_col";
            this.ui_lb_col.Size = new System.Drawing.Size(23, 15);
            this.ui_lb_col.TabIndex = 1;
            this.ui_lb_col.Text = "렬";
            // 
            // ui_lb_row
            // 
            this.ui_lb_row.AutoSize = true;
            this.ui_lb_row.Location = new System.Drawing.Point(22, 77);
            this.ui_lb_row.Name = "ui_lb_row";
            this.ui_lb_row.Size = new System.Drawing.Size(23, 15);
            this.ui_lb_row.TabIndex = 0;
            this.ui_lb_row.Text = "행";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1360, 753);
            this.Controls.Add(this.ui_panel);
            this.Controls.Add(this.Tap_Map);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.Tap_Map.ResumeLayout(false);
            this.ui_tabpage.ResumeLayout(false);
            this.ui_tabpage2.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem Save;
        private System.Windows.Forms.ToolStripMenuItem 로드ToolStripMenuItem;
        private TapControlMapPage1 ui_tabpage;
        private System.Windows.Forms.TabControl Tap_Map;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TabPage ui_tabpage2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label ui_lb_col;
        private System.Windows.Forms.Label ui_lb_row;
        private System.Windows.Forms.Button ui_btn_ok;
        private System.Windows.Forms.TextBox ui_txt_col;
        private System.Windows.Forms.TextBox ui_txt_row;
        private panelcontrol ui_panel;
        private panelcontrol ui_panel2;
    }
}

