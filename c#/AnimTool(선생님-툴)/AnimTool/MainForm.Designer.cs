namespace AnimTool
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
            this.ui_scSplitter = new System.Windows.Forms.SplitContainer();
            this.ui_trAnimInterval = new System.Windows.Forms.TrackBar();
            this.ui_pnTransParentColor = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.ui_msMainMenu = new System.Windows.Forms.MenuStrip();
            this.파일ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.열기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.애니매이션ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.시작ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.정지ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ui_dlgOpenFile = new System.Windows.Forms.OpenFileDialog();
            this.label2 = new System.Windows.Forms.Label();
            this.ui_rbFrameSelect = new System.Windows.Forms.RadioButton();
            this.ui_rbGroup = new System.Windows.Forms.RadioButton();
            this.ui_cbAnimGroup = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.ui_ucAnimPanel = new AnimTool.AnimPanel();
            this.ui_ucEditPanel = new AnimTool.EditPanel();
            this.button1 = new System.Windows.Forms.Button();
            this.저장ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.ui_scSplitter)).BeginInit();
            this.ui_scSplitter.Panel1.SuspendLayout();
            this.ui_scSplitter.Panel2.SuspendLayout();
            this.ui_scSplitter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ui_trAnimInterval)).BeginInit();
            this.ui_msMainMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // ui_scSplitter
            // 
            this.ui_scSplitter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ui_scSplitter.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.ui_scSplitter.IsSplitterFixed = true;
            this.ui_scSplitter.Location = new System.Drawing.Point(0, 24);
            this.ui_scSplitter.Name = "ui_scSplitter";
            // 
            // ui_scSplitter.Panel1
            // 
            this.ui_scSplitter.Panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ui_scSplitter.Panel1.Controls.Add(this.button1);
            this.ui_scSplitter.Panel1.Controls.Add(this.label3);
            this.ui_scSplitter.Panel1.Controls.Add(this.ui_cbAnimGroup);
            this.ui_scSplitter.Panel1.Controls.Add(this.ui_rbGroup);
            this.ui_scSplitter.Panel1.Controls.Add(this.ui_rbFrameSelect);
            this.ui_scSplitter.Panel1.Controls.Add(this.label2);
            this.ui_scSplitter.Panel1.Controls.Add(this.ui_trAnimInterval);
            this.ui_scSplitter.Panel1.Controls.Add(this.ui_ucAnimPanel);
            this.ui_scSplitter.Panel1.Controls.Add(this.ui_pnTransParentColor);
            this.ui_scSplitter.Panel1.Controls.Add(this.label1);
            // 
            // ui_scSplitter.Panel2
            // 
            this.ui_scSplitter.Panel2.Controls.Add(this.ui_ucEditPanel);
            this.ui_scSplitter.Size = new System.Drawing.Size(1119, 680);
            this.ui_scSplitter.SplitterDistance = 249;
            this.ui_scSplitter.TabIndex = 0;
            // 
            // ui_trAnimInterval
            // 
            this.ui_trAnimInterval.Location = new System.Drawing.Point(122, 37);
            this.ui_trAnimInterval.Minimum = 1;
            this.ui_trAnimInterval.Name = "ui_trAnimInterval";
            this.ui_trAnimInterval.Size = new System.Drawing.Size(124, 45);
            this.ui_trAnimInterval.TabIndex = 3;
            this.ui_trAnimInterval.Value = 1;
            this.ui_trAnimInterval.ValueChanged += new System.EventHandler(this.ui_trAnimInterval_ValueChanged);
            // 
            // ui_pnTransParentColor
            // 
            this.ui_pnTransParentColor.BackColor = System.Drawing.Color.Fuchsia;
            this.ui_pnTransParentColor.Location = new System.Drawing.Point(122, 19);
            this.ui_pnTransParentColor.Name = "ui_pnTransParentColor";
            this.ui_pnTransParentColor.Size = new System.Drawing.Size(124, 12);
            this.ui_pnTransParentColor.TabIndex = 1;
            this.ui_pnTransParentColor.Click += new System.EventHandler(this.ui_pnTransParentColor_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "TransparentColor";
            // 
            // ui_msMainMenu
            // 
            this.ui_msMainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일ToolStripMenuItem,
            this.애니매이션ToolStripMenuItem});
            this.ui_msMainMenu.Location = new System.Drawing.Point(0, 0);
            this.ui_msMainMenu.Name = "ui_msMainMenu";
            this.ui_msMainMenu.Size = new System.Drawing.Size(1119, 24);
            this.ui_msMainMenu.TabIndex = 1;
            this.ui_msMainMenu.Text = "ui_msMainMenu";
            // 
            // 파일ToolStripMenuItem
            // 
            this.파일ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.열기ToolStripMenuItem,
            this.저장ToolStripMenuItem});
            this.파일ToolStripMenuItem.Name = "파일ToolStripMenuItem";
            this.파일ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.파일ToolStripMenuItem.Text = "파일";
            // 
            // 열기ToolStripMenuItem
            // 
            this.열기ToolStripMenuItem.Name = "열기ToolStripMenuItem";
            this.열기ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.열기ToolStripMenuItem.Text = "열기";
            this.열기ToolStripMenuItem.Click += new System.EventHandler(this.파일_열기_Click);
            // 
            // 애니매이션ToolStripMenuItem
            // 
            this.애니매이션ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.시작ToolStripMenuItem,
            this.정지ToolStripMenuItem});
            this.애니매이션ToolStripMenuItem.Name = "애니매이션ToolStripMenuItem";
            this.애니매이션ToolStripMenuItem.Size = new System.Drawing.Size(79, 20);
            this.애니매이션ToolStripMenuItem.Text = "애니매이션";
            // 
            // 시작ToolStripMenuItem
            // 
            this.시작ToolStripMenuItem.Name = "시작ToolStripMenuItem";
            this.시작ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.시작ToolStripMenuItem.Text = "시작";
            this.시작ToolStripMenuItem.Click += new System.EventHandler(this.시작ToolStripMenuItem_Click);
            // 
            // 정지ToolStripMenuItem
            // 
            this.정지ToolStripMenuItem.Name = "정지ToolStripMenuItem";
            this.정지ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.정지ToolStripMenuItem.Text = "정지";
            this.정지ToolStripMenuItem.Click += new System.EventHandler(this.정지ToolStripMenuItem_Click);
            // 
            // ui_dlgOpenFile
            // 
            this.ui_dlgOpenFile.FileName = "openFileDialog1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(42, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "AnimInterval";
            // 
            // ui_rbFrameSelect
            // 
            this.ui_rbFrameSelect.AutoSize = true;
            this.ui_rbFrameSelect.Checked = true;
            this.ui_rbFrameSelect.Location = new System.Drawing.Point(56, 88);
            this.ui_rbFrameSelect.Name = "ui_rbFrameSelect";
            this.ui_rbFrameSelect.Size = new System.Drawing.Size(87, 16);
            this.ui_rbFrameSelect.TabIndex = 5;
            this.ui_rbFrameSelect.TabStop = true;
            this.ui_rbFrameSelect.Text = "프레임 선택";
            this.ui_rbFrameSelect.UseVisualStyleBackColor = true;
            this.ui_rbFrameSelect.CheckedChanged += new System.EventHandler(this.ui_rbFrameSelect_CheckedChanged);
            // 
            // ui_rbGroup
            // 
            this.ui_rbGroup.AutoSize = true;
            this.ui_rbGroup.Location = new System.Drawing.Point(154, 88);
            this.ui_rbGroup.Name = "ui_rbGroup";
            this.ui_rbGroup.Size = new System.Drawing.Size(75, 16);
            this.ui_rbGroup.TabIndex = 6;
            this.ui_rbGroup.Text = "그룹 지정";
            this.ui_rbGroup.UseVisualStyleBackColor = true;
            this.ui_rbGroup.CheckedChanged += new System.EventHandler(this.ui_rbGroup_CheckedChanged);
            // 
            // ui_cbAnimGroup
            // 
            this.ui_cbAnimGroup.FormattingEnabled = true;
            this.ui_cbAnimGroup.Location = new System.Drawing.Point(122, 119);
            this.ui_cbAnimGroup.Name = "ui_cbAnimGroup";
            this.ui_cbAnimGroup.Size = new System.Drawing.Size(124, 20);
            this.ui_cbAnimGroup.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(23, 122);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(93, 12);
            this.label3.TabIndex = 8;
            this.label3.Text = "애니매이션 그룹";
            // 
            // ui_ucAnimPanel
            // 
            this.ui_ucAnimPanel.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ui_ucAnimPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.ui_ucAnimPanel.Location = new System.Drawing.Point(0, 398);
            this.ui_ucAnimPanel.Name = "ui_ucAnimPanel";
            this.ui_ucAnimPanel.Size = new System.Drawing.Size(249, 282);
            this.ui_ucAnimPanel.TabIndex = 2;
            // 
            // ui_ucEditPanel
            // 
            this.ui_ucEditPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ui_ucEditPanel.EditImage = null;
            this.ui_ucEditPanel.EditMode = AnimTool.EditPanel.eEditMode.E_FRAME_SELECT;
            this.ui_ucEditPanel.Location = new System.Drawing.Point(0, 0);
            this.ui_ucEditPanel.Name = "ui_ucEditPanel";
            this.ui_ucEditPanel.Size = new System.Drawing.Size(866, 680);
            this.ui_ucEditPanel.TabIndex = 0;
            this.ui_ucEditPanel.TransparentColorEdit = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(34, 0);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(8, 8);
            this.button1.TabIndex = 9;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // 저장ToolStripMenuItem
            // 
            this.저장ToolStripMenuItem.Name = "저장ToolStripMenuItem";
            this.저장ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.저장ToolStripMenuItem.Text = "저장";
            this.저장ToolStripMenuItem.Click += new System.EventHandler(this.저장ToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1119, 704);
            this.Controls.Add(this.ui_scSplitter);
            this.Controls.Add(this.ui_msMainMenu);
            this.MainMenuStrip = this.ui_msMainMenu;
            this.Name = "MainForm";
            this.Text = "AnimTool";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.ui_scSplitter.Panel1.ResumeLayout(false);
            this.ui_scSplitter.Panel1.PerformLayout();
            this.ui_scSplitter.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.ui_scSplitter)).EndInit();
            this.ui_scSplitter.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.ui_trAnimInterval)).EndInit();
            this.ui_msMainMenu.ResumeLayout(false);
            this.ui_msMainMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer ui_scSplitter;
        private System.Windows.Forms.MenuStrip ui_msMainMenu;
        private System.Windows.Forms.ToolStripMenuItem 파일ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 열기ToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog ui_dlgOpenFile;
        private EditPanel ui_ucEditPanel;
        private System.Windows.Forms.Panel ui_pnTransParentColor;
        private System.Windows.Forms.Label label1;
        private AnimPanel ui_ucAnimPanel;
        private System.Windows.Forms.ToolStripMenuItem 애니매이션ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 시작ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 정지ToolStripMenuItem;
        private System.Windows.Forms.TrackBar ui_trAnimInterval;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RadioButton ui_rbGroup;
        private System.Windows.Forms.RadioButton ui_rbFrameSelect;
        private System.Windows.Forms.ComboBox ui_cbAnimGroup;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolStripMenuItem 저장ToolStripMenuItem;
    }
}

