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
            this.ui_btNum0 = new System.Windows.Forms.Button();
            this.ui_btNum1 = new System.Windows.Forms.Button();
            this.ui_btNum2 = new System.Windows.Forms.Button();
            this.ui_btNum4 = new System.Windows.Forms.Button();
            this.ui_btNum5 = new System.Windows.Forms.Button();
            this.ui_btNum7 = new System.Windows.Forms.Button();
            this.ui_btNum8 = new System.Windows.Forms.Button();
            this.ui_btNum3 = new System.Windows.Forms.Button();
            this.ui_btNum6 = new System.Windows.Forms.Button();
            this.ui_btNum9 = new System.Windows.Forms.Button();
            this.ui_btNoper_equal = new System.Windows.Forms.Button();
            this.ui_btNoper_plus = new System.Windows.Forms.Button();
            this.ui_btNoper_minus = new System.Windows.Forms.Button();
            this.ui_btNoper_multi = new System.Windows.Forms.Button();
            this.ui_btNoper_divide = new System.Windows.Forms.Button();
            this.ui_btNoper_leftparent = new System.Windows.Forms.Button();
            this.ui_btNoper_rightparent = new System.Windows.Forms.Button();
            this.ui_btN_backspace = new System.Windows.Forms.Button();
            this.ui_btN_allclear = new System.Windows.Forms.Button();
            this.ui_Text_result = new System.Windows.Forms.Label();
            this.ui_textbox = new System.Windows.Forms.TextBox();
            this.ui_btN_dot = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ui_btNum0
            // 
            this.ui_btNum0.Location = new System.Drawing.Point(1, 514);
            this.ui_btNum0.Name = "ui_btNum0";
            this.ui_btNum0.Size = new System.Drawing.Size(155, 54);
            this.ui_btNum0.TabIndex = 0;
            this.ui_btNum0.Text = "0";
            this.ui_btNum0.UseVisualStyleBackColor = true;
            this.ui_btNum0.Click += new System.EventHandler(this.ui_btNum0_Click);
            // 
            // ui_btNum1
            // 
            this.ui_btNum1.Location = new System.Drawing.Point(1, 460);
            this.ui_btNum1.Name = "ui_btNum1";
            this.ui_btNum1.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum1.TabIndex = 1;
            this.ui_btNum1.Text = "1";
            this.ui_btNum1.UseVisualStyleBackColor = true;
            this.ui_btNum1.Click += new System.EventHandler(this.ui_btNum1_Click);
            // 
            // ui_btNum2
            // 
            this.ui_btNum2.Location = new System.Drawing.Point(81, 460);
            this.ui_btNum2.Name = "ui_btNum2";
            this.ui_btNum2.Size = new System.Drawing.Size(75, 48);
            this.ui_btNum2.TabIndex = 2;
            this.ui_btNum2.Text = "2";
            this.ui_btNum2.UseVisualStyleBackColor = true;
            this.ui_btNum2.Click += new System.EventHandler(this.ui_btNum2_Click);
            // 
            // ui_btNum4
            // 
            this.ui_btNum4.Location = new System.Drawing.Point(1, 415);
            this.ui_btNum4.Name = "ui_btNum4";
            this.ui_btNum4.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum4.TabIndex = 3;
            this.ui_btNum4.Text = "4";
            this.ui_btNum4.UseVisualStyleBackColor = true;
            this.ui_btNum4.Click += new System.EventHandler(this.ui_btNum4_Click);
            // 
            // ui_btNum5
            // 
            this.ui_btNum5.Location = new System.Drawing.Point(81, 415);
            this.ui_btNum5.Name = "ui_btNum5";
            this.ui_btNum5.Size = new System.Drawing.Size(75, 48);
            this.ui_btNum5.TabIndex = 4;
            this.ui_btNum5.Text = "5";
            this.ui_btNum5.UseVisualStyleBackColor = true;
            this.ui_btNum5.Click += new System.EventHandler(this.ui_btNum5_Click);
            // 
            // ui_btNum7
            // 
            this.ui_btNum7.Location = new System.Drawing.Point(0, 366);
            this.ui_btNum7.Name = "ui_btNum7";
            this.ui_btNum7.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum7.TabIndex = 5;
            this.ui_btNum7.Text = "7";
            this.ui_btNum7.UseVisualStyleBackColor = true;
            this.ui_btNum7.Click += new System.EventHandler(this.ui_btNum7_Click);
            // 
            // ui_btNum8
            // 
            this.ui_btNum8.Location = new System.Drawing.Point(82, 366);
            this.ui_btNum8.Name = "ui_btNum8";
            this.ui_btNum8.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum8.TabIndex = 6;
            this.ui_btNum8.Text = "8";
            this.ui_btNum8.UseVisualStyleBackColor = true;
            this.ui_btNum8.Click += new System.EventHandler(this.ui_btNum8_Click);
            // 
            // ui_btNum3
            // 
            this.ui_btNum3.Location = new System.Drawing.Point(164, 460);
            this.ui_btNum3.Name = "ui_btNum3";
            this.ui_btNum3.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum3.TabIndex = 8;
            this.ui_btNum3.Text = "3";
            this.ui_btNum3.UseVisualStyleBackColor = true;
            this.ui_btNum3.Click += new System.EventHandler(this.ui_btNum3_Click);
            // 
            // ui_btNum6
            // 
            this.ui_btNum6.Location = new System.Drawing.Point(164, 412);
            this.ui_btNum6.Name = "ui_btNum6";
            this.ui_btNum6.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum6.TabIndex = 9;
            this.ui_btNum6.Text = "6";
            this.ui_btNum6.UseVisualStyleBackColor = true;
            this.ui_btNum6.Click += new System.EventHandler(this.ui_btNum6_Click);
            // 
            // ui_btNum9
            // 
            this.ui_btNum9.Location = new System.Drawing.Point(164, 366);
            this.ui_btNum9.Name = "ui_btNum9";
            this.ui_btNum9.Size = new System.Drawing.Size(74, 48);
            this.ui_btNum9.TabIndex = 10;
            this.ui_btNum9.Text = "9";
            this.ui_btNum9.UseVisualStyleBackColor = true;
            this.ui_btNum9.Click += new System.EventHandler(this.ui_btNum9_Click);
            // 
            // ui_btNoper_equal
            // 
            this.ui_btNoper_equal.Location = new System.Drawing.Point(244, 514);
            this.ui_btNoper_equal.Name = "ui_btNoper_equal";
            this.ui_btNoper_equal.Size = new System.Drawing.Size(151, 54);
            this.ui_btNoper_equal.TabIndex = 11;
            this.ui_btNoper_equal.Text = "=";
            this.ui_btNoper_equal.UseVisualStyleBackColor = true;
            this.ui_btNoper_equal.Click += new System.EventHandler(this.ui_btNoper_equal_Click);
            // 
            // ui_btNoper_plus
            // 
            this.ui_btNoper_plus.Location = new System.Drawing.Point(244, 460);
            this.ui_btNoper_plus.Name = "ui_btNoper_plus";
            this.ui_btNoper_plus.Size = new System.Drawing.Size(151, 47);
            this.ui_btNoper_plus.TabIndex = 12;
            this.ui_btNoper_plus.Text = "+";
            this.ui_btNoper_plus.UseVisualStyleBackColor = true;
            this.ui_btNoper_plus.Click += new System.EventHandler(this.ui_btNoper_plus_Click);
            // 
            // ui_btNoper_minus
            // 
            this.ui_btNoper_minus.Location = new System.Drawing.Point(244, 415);
            this.ui_btNoper_minus.Name = "ui_btNoper_minus";
            this.ui_btNoper_minus.Size = new System.Drawing.Size(151, 45);
            this.ui_btNoper_minus.TabIndex = 13;
            this.ui_btNoper_minus.Text = "-";
            this.ui_btNoper_minus.UseVisualStyleBackColor = true;
            this.ui_btNoper_minus.Click += new System.EventHandler(this.ui_btNoper_minus_Click);
            // 
            // ui_btNoper_multi
            // 
            this.ui_btNoper_multi.Location = new System.Drawing.Point(244, 366);
            this.ui_btNoper_multi.Name = "ui_btNoper_multi";
            this.ui_btNoper_multi.Size = new System.Drawing.Size(151, 48);
            this.ui_btNoper_multi.TabIndex = 14;
            this.ui_btNoper_multi.Text = "*";
            this.ui_btNoper_multi.UseVisualStyleBackColor = true;
            this.ui_btNoper_multi.Click += new System.EventHandler(this.ui_btNoper_multi_Click);
            // 
            // ui_btNoper_divide
            // 
            this.ui_btNoper_divide.Location = new System.Drawing.Point(244, 317);
            this.ui_btNoper_divide.Name = "ui_btNoper_divide";
            this.ui_btNoper_divide.Size = new System.Drawing.Size(151, 48);
            this.ui_btNoper_divide.TabIndex = 15;
            this.ui_btNoper_divide.Text = "/";
            this.ui_btNoper_divide.UseVisualStyleBackColor = true;
            this.ui_btNoper_divide.Click += new System.EventHandler(this.ui_btNoper_divide_Click);
            // 
            // ui_btNoper_leftparent
            // 
            this.ui_btNoper_leftparent.Location = new System.Drawing.Point(0, 263);
            this.ui_btNoper_leftparent.Name = "ui_btNoper_leftparent";
            this.ui_btNoper_leftparent.Size = new System.Drawing.Size(194, 48);
            this.ui_btNoper_leftparent.TabIndex = 16;
            this.ui_btNoper_leftparent.Text = "(";
            this.ui_btNoper_leftparent.UseVisualStyleBackColor = true;
            this.ui_btNoper_leftparent.Click += new System.EventHandler(this.ui_btNoper_leftparent_Click);
            // 
            // ui_btNoper_rightparent
            // 
            this.ui_btNoper_rightparent.Location = new System.Drawing.Point(200, 263);
            this.ui_btNoper_rightparent.Name = "ui_btNoper_rightparent";
            this.ui_btNoper_rightparent.Size = new System.Drawing.Size(194, 48);
            this.ui_btNoper_rightparent.TabIndex = 17;
            this.ui_btNoper_rightparent.Text = ")";
            this.ui_btNoper_rightparent.UseVisualStyleBackColor = true;
            this.ui_btNoper_rightparent.Click += new System.EventHandler(this.ui_btNoper_rightparent_Click);
            // 
            // ui_btN_backspace
            // 
            this.ui_btN_backspace.Location = new System.Drawing.Point(0, 317);
            this.ui_btN_backspace.Name = "ui_btN_backspace";
            this.ui_btN_backspace.Size = new System.Drawing.Size(156, 45);
            this.ui_btN_backspace.TabIndex = 18;
            this.ui_btN_backspace.Text = "<- BackSpace";
            this.ui_btN_backspace.UseVisualStyleBackColor = true;
            this.ui_btN_backspace.Click += new System.EventHandler(this.ui_btN_backspace_Click);
            // 
            // ui_btN_allclear
            // 
            this.ui_btN_allclear.Location = new System.Drawing.Point(163, 317);
            this.ui_btN_allclear.Name = "ui_btN_allclear";
            this.ui_btN_allclear.Size = new System.Drawing.Size(75, 45);
            this.ui_btN_allclear.TabIndex = 19;
            this.ui_btN_allclear.Text = "C";
            this.ui_btN_allclear.UseVisualStyleBackColor = true;
            this.ui_btN_allclear.Click += new System.EventHandler(this.ui_btN_allclear_Click);
            // 
            // ui_Text_result
            // 
            this.ui_Text_result.Font = new System.Drawing.Font("Microsoft Sans Serif", 30F);
            this.ui_Text_result.Location = new System.Drawing.Point(26, 188);
            this.ui_Text_result.Name = "ui_Text_result";
            this.ui_Text_result.Size = new System.Drawing.Size(338, 72);
            this.ui_Text_result.TabIndex = 20;
            this.ui_Text_result.Text = "0";
            this.ui_Text_result.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ui_textbox
            // 
            this.ui_textbox.BackColor = System.Drawing.SystemColors.Info;
            this.ui_textbox.Font = new System.Drawing.Font("돋움체", 35F);
            this.ui_textbox.Location = new System.Drawing.Point(25, 26);
            this.ui_textbox.Multiline = true;
            this.ui_textbox.Name = "ui_textbox";
            this.ui_textbox.Size = new System.Drawing.Size(339, 73);
            this.ui_textbox.TabIndex = 21;
            this.ui_textbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // ui_btN_dot
            // 
            this.ui_btN_dot.Location = new System.Drawing.Point(163, 514);
            this.ui_btN_dot.Name = "ui_btN_dot";
            this.ui_btN_dot.Size = new System.Drawing.Size(75, 54);
            this.ui_btN_dot.TabIndex = 22;
            this.ui_btN_dot.Text = ".";
            this.ui_btN_dot.UseVisualStyleBackColor = true;
            this.ui_btN_dot.Click += new System.EventHandler(this.ui_btN_dot_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Info;
            this.ClientSize = new System.Drawing.Size(399, 570);
            this.Controls.Add(this.ui_btN_dot);
            this.Controls.Add(this.ui_textbox);
            this.Controls.Add(this.ui_Text_result);
            this.Controls.Add(this.ui_btN_allclear);
            this.Controls.Add(this.ui_btN_backspace);
            this.Controls.Add(this.ui_btNoper_rightparent);
            this.Controls.Add(this.ui_btNoper_leftparent);
            this.Controls.Add(this.ui_btNoper_divide);
            this.Controls.Add(this.ui_btNoper_multi);
            this.Controls.Add(this.ui_btNoper_minus);
            this.Controls.Add(this.ui_btNoper_plus);
            this.Controls.Add(this.ui_btNoper_equal);
            this.Controls.Add(this.ui_btNum9);
            this.Controls.Add(this.ui_btNum6);
            this.Controls.Add(this.ui_btNum3);
            this.Controls.Add(this.ui_btNum8);
            this.Controls.Add(this.ui_btNum7);
            this.Controls.Add(this.ui_btNum5);
            this.Controls.Add(this.ui_btNum4);
            this.Controls.Add(this.ui_btNum2);
            this.Controls.Add(this.ui_btNum1);
            this.Controls.Add(this.ui_btNum0);
            this.Name = "MainForm";
            this.Text = "계산기ver.0.1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ui_btNum0;
        private System.Windows.Forms.Button ui_btNum1;
        private System.Windows.Forms.Button ui_btNum2;
        private System.Windows.Forms.Button ui_btNum4;
        private System.Windows.Forms.Button ui_btNum5;
        private System.Windows.Forms.Button ui_btNum7;
        private System.Windows.Forms.Button ui_btNum8;
        private System.Windows.Forms.Button ui_btNum3;
        private System.Windows.Forms.Button ui_btNum6;
        private System.Windows.Forms.Button ui_btNum9;
        private System.Windows.Forms.Button ui_btNoper_equal;
        private System.Windows.Forms.Button ui_btNoper_plus;
        private System.Windows.Forms.Button ui_btNoper_minus;
        private System.Windows.Forms.Button ui_btNoper_multi;
        private System.Windows.Forms.Button ui_btNoper_divide;
        private System.Windows.Forms.Button ui_btNoper_leftparent;
        private System.Windows.Forms.Button ui_btNoper_rightparent;
        private System.Windows.Forms.Button ui_btN_backspace;
        private System.Windows.Forms.Button ui_btN_allclear;
        private System.Windows.Forms.Label ui_Text_result;
        private System.Windows.Forms.TextBox ui_textbox;
        private System.Windows.Forms.Button ui_btN_dot;
    }
}

