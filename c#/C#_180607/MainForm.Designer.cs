namespace StackCalcCS
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
            this.components = new System.ComponentModel.Container();
            this.ui_lbCalc = new System.Windows.Forms.Label();
            this.ui_tmrTick = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // ui_lbCalc
            // 
            this.ui_lbCalc.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ui_lbCalc.Font = new System.Drawing.Font("굴림", 19F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.ui_lbCalc.Location = new System.Drawing.Point(6, 6);
            this.ui_lbCalc.Name = "ui_lbCalc";
            this.ui_lbCalc.Size = new System.Drawing.Size(355, 50);
            this.ui_lbCalc.TabIndex = 0;
            this.ui_lbCalc.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ui_tmrTick
            // 
            this.ui_tmrTick.Interval = 10;
            this.ui_tmrTick.Tick += new System.EventHandler(this.ui_tmrTick_Tick);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(375, 630);
            this.Controls.Add(this.ui_lbCalc);
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label ui_lbCalc;
        private System.Windows.Forms.Timer ui_tmrTick;
    }
}

