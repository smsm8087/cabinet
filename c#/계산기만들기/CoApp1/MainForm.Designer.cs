namespace CoApp1
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
            this.texbox_result = new System.Windows.Forms.TextBox();
            this.texbox_num = new System.Windows.Forms.TextBox();
            this.btn_backspace = new System.Windows.Forms.Button();
            this.btn_clear = new System.Windows.Forms.Button();
            this.btn_0 = new System.Windows.Forms.Button();
            this.btn_1 = new System.Windows.Forms.Button();
            this.btn_2 = new System.Windows.Forms.Button();
            this.btn_3 = new System.Windows.Forms.Button();
            this.btn_4 = new System.Windows.Forms.Button();
            this.btn_5 = new System.Windows.Forms.Button();
            this.btn_6 = new System.Windows.Forms.Button();
            this.btn_7 = new System.Windows.Forms.Button();
            this.btn_8 = new System.Windows.Forms.Button();
            this.btn_9 = new System.Windows.Forms.Button();
            this.btn_div = new System.Windows.Forms.Button();
            this.btn_mul = new System.Windows.Forms.Button();
            this.btn_sub = new System.Windows.Forms.Button();
            this.btn_puls = new System.Windows.Forms.Button();
            this.btn_result = new System.Windows.Forms.Button();
            this.btn_dot = new System.Windows.Forms.Button();
            this.btn_open = new System.Windows.Forms.Button();
            this.btn_close = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // texbox_result
            // 
            this.texbox_result.BackColor = System.Drawing.SystemColors.Info;
            this.texbox_result.Location = new System.Drawing.Point(14, 15);
            this.texbox_result.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.texbox_result.Name = "texbox_result";
            this.texbox_result.Size = new System.Drawing.Size(323, 25);
            this.texbox_result.TabIndex = 1;
            this.texbox_result.Text = "-2*7+7-4*2*(-4)+8*(((5+2)-(4+6)*2-5)+(6-1.5)-99)";
            this.texbox_result.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // texbox_num
            // 
            this.texbox_num.BackColor = System.Drawing.SystemColors.Info;
            this.texbox_num.Location = new System.Drawing.Point(15, 50);
            this.texbox_num.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.texbox_num.Name = "texbox_num";
            this.texbox_num.Size = new System.Drawing.Size(322, 25);
            this.texbox_num.TabIndex = 3;
            this.texbox_num.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // btn_backspace
            // 
            this.btn_backspace.Location = new System.Drawing.Point(14, 84);
            this.btn_backspace.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_backspace.Name = "btn_backspace";
            this.btn_backspace.Size = new System.Drawing.Size(187, 62);
            this.btn_backspace.TabIndex = 4;
            this.btn_backspace.Text = "<----";
            this.btn_backspace.UseVisualStyleBackColor = true;
            this.btn_backspace.Click += new System.EventHandler(this.btn_backspace_Click);
            this.btn_backspace.MouseEnter += new System.EventHandler(this.btn_backspace_MouseEnter);
            this.btn_backspace.MouseLeave += new System.EventHandler(this.btn_backspace_MouseLeave);
            // 
            // btn_clear
            // 
            this.btn_clear.Location = new System.Drawing.Point(207, 83);
            this.btn_clear.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_clear.Name = "btn_clear";
            this.btn_clear.Size = new System.Drawing.Size(121, 62);
            this.btn_clear.TabIndex = 5;
            this.btn_clear.Text = "C";
            this.btn_clear.UseVisualStyleBackColor = true;
            this.btn_clear.Click += new System.EventHandler(this.btn_clear_Click);
            // 
            // btn_0
            // 
            this.btn_0.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_0.Location = new System.Drawing.Point(15, 364);
            this.btn_0.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_0.Name = "btn_0";
            this.btn_0.Size = new System.Drawing.Size(121, 62);
            this.btn_0.TabIndex = 6;
            this.btn_0.Text = "0";
            this.btn_0.UseVisualStyleBackColor = true;
            this.btn_0.Click += new System.EventHandler(this.btn_0_Click);
            // 
            // btn_1
            // 
            this.btn_1.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_1.Location = new System.Drawing.Point(15, 294);
            this.btn_1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_1.Name = "btn_1";
            this.btn_1.Size = new System.Drawing.Size(57, 62);
            this.btn_1.TabIndex = 7;
            this.btn_1.Text = "1";
            this.btn_1.UseVisualStyleBackColor = true;
            this.btn_1.Click += new System.EventHandler(this.btn_1_Click);
            // 
            // btn_2
            // 
            this.btn_2.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_2.Location = new System.Drawing.Point(79, 294);
            this.btn_2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_2.Name = "btn_2";
            this.btn_2.Size = new System.Drawing.Size(57, 62);
            this.btn_2.TabIndex = 8;
            this.btn_2.Text = "2";
            this.btn_2.UseVisualStyleBackColor = true;
            this.btn_2.Click += new System.EventHandler(this.btn_2_Click);
            // 
            // btn_3
            // 
            this.btn_3.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_3.Location = new System.Drawing.Point(143, 294);
            this.btn_3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_3.Name = "btn_3";
            this.btn_3.Size = new System.Drawing.Size(57, 62);
            this.btn_3.TabIndex = 9;
            this.btn_3.Text = "3";
            this.btn_3.UseVisualStyleBackColor = true;
            this.btn_3.Click += new System.EventHandler(this.btn_3_Click);
            // 
            // btn_4
            // 
            this.btn_4.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_4.Location = new System.Drawing.Point(15, 224);
            this.btn_4.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_4.Name = "btn_4";
            this.btn_4.Size = new System.Drawing.Size(57, 62);
            this.btn_4.TabIndex = 10;
            this.btn_4.Text = "4";
            this.btn_4.UseVisualStyleBackColor = true;
            this.btn_4.Click += new System.EventHandler(this.btn_4_Click);
            // 
            // btn_5
            // 
            this.btn_5.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_5.Location = new System.Drawing.Point(79, 224);
            this.btn_5.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_5.Name = "btn_5";
            this.btn_5.Size = new System.Drawing.Size(57, 62);
            this.btn_5.TabIndex = 11;
            this.btn_5.Text = "5";
            this.btn_5.UseVisualStyleBackColor = true;
            this.btn_5.Click += new System.EventHandler(this.btn_5_Click);
            // 
            // btn_6
            // 
            this.btn_6.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_6.Location = new System.Drawing.Point(143, 224);
            this.btn_6.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_6.Name = "btn_6";
            this.btn_6.Size = new System.Drawing.Size(57, 62);
            this.btn_6.TabIndex = 12;
            this.btn_6.Text = "6";
            this.btn_6.UseVisualStyleBackColor = true;
            this.btn_6.Click += new System.EventHandler(this.btn_6_Click);
            // 
            // btn_7
            // 
            this.btn_7.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_7.Location = new System.Drawing.Point(14, 154);
            this.btn_7.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_7.Name = "btn_7";
            this.btn_7.Size = new System.Drawing.Size(57, 62);
            this.btn_7.TabIndex = 13;
            this.btn_7.Text = "7";
            this.btn_7.UseVisualStyleBackColor = true;
            this.btn_7.Click += new System.EventHandler(this.btn_7_Click);
            // 
            // btn_8
            // 
            this.btn_8.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_8.Location = new System.Drawing.Point(79, 154);
            this.btn_8.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_8.Name = "btn_8";
            this.btn_8.Size = new System.Drawing.Size(57, 62);
            this.btn_8.TabIndex = 14;
            this.btn_8.Text = "8";
            this.btn_8.UseVisualStyleBackColor = true;
            this.btn_8.Click += new System.EventHandler(this.btn_8_Click);
            // 
            // btn_9
            // 
            this.btn_9.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_9.Location = new System.Drawing.Point(143, 154);
            this.btn_9.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_9.Name = "btn_9";
            this.btn_9.Size = new System.Drawing.Size(57, 62);
            this.btn_9.TabIndex = 15;
            this.btn_9.Text = "9";
            this.btn_9.UseVisualStyleBackColor = true;
            this.btn_9.Click += new System.EventHandler(this.btn_9_Click);
            // 
            // btn_div
            // 
            this.btn_div.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_div.Location = new System.Drawing.Point(207, 154);
            this.btn_div.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_div.Name = "btn_div";
            this.btn_div.Size = new System.Drawing.Size(57, 62);
            this.btn_div.TabIndex = 16;
            this.btn_div.Text = "/";
            this.btn_div.UseVisualStyleBackColor = true;
            this.btn_div.Click += new System.EventHandler(this.btn_div_Click);
            // 
            // btn_mul
            // 
            this.btn_mul.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_mul.Location = new System.Drawing.Point(207, 224);
            this.btn_mul.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_mul.Name = "btn_mul";
            this.btn_mul.Size = new System.Drawing.Size(57, 62);
            this.btn_mul.TabIndex = 17;
            this.btn_mul.Text = "*";
            this.btn_mul.UseVisualStyleBackColor = true;
            this.btn_mul.Click += new System.EventHandler(this.btn_mul_Click);
            // 
            // btn_sub
            // 
            this.btn_sub.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_sub.Location = new System.Drawing.Point(207, 294);
            this.btn_sub.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_sub.Name = "btn_sub";
            this.btn_sub.Size = new System.Drawing.Size(57, 62);
            this.btn_sub.TabIndex = 18;
            this.btn_sub.Text = "-";
            this.btn_sub.UseVisualStyleBackColor = true;
            this.btn_sub.Click += new System.EventHandler(this.btn_sub_Click);
            // 
            // btn_puls
            // 
            this.btn_puls.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_puls.Location = new System.Drawing.Point(207, 364);
            this.btn_puls.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_puls.Name = "btn_puls";
            this.btn_puls.Size = new System.Drawing.Size(57, 62);
            this.btn_puls.TabIndex = 19;
            this.btn_puls.Text = "+";
            this.btn_puls.UseVisualStyleBackColor = true;
            this.btn_puls.Click += new System.EventHandler(this.btn_puls_Click);
            // 
            // btn_result
            // 
            this.btn_result.Font = new System.Drawing.Font("굴림", 30F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_result.Location = new System.Drawing.Point(271, 294);
            this.btn_result.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_result.Name = "btn_result";
            this.btn_result.Size = new System.Drawing.Size(57, 132);
            this.btn_result.TabIndex = 20;
            this.btn_result.Text = "=";
            this.btn_result.UseVisualStyleBackColor = true;
            this.btn_result.Click += new System.EventHandler(this.btn_result_Click);
            // 
            // btn_dot
            // 
            this.btn_dot.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_dot.Location = new System.Drawing.Point(143, 364);
            this.btn_dot.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_dot.Name = "btn_dot";
            this.btn_dot.Size = new System.Drawing.Size(57, 62);
            this.btn_dot.TabIndex = 21;
            this.btn_dot.Text = ".";
            this.btn_dot.UseVisualStyleBackColor = true;
            this.btn_dot.Click += new System.EventHandler(this.btn_dot_Click);
            // 
            // btn_open
            // 
            this.btn_open.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_open.Location = new System.Drawing.Point(271, 154);
            this.btn_open.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(57, 62);
            this.btn_open.TabIndex = 22;
            this.btn_open.Text = "(";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // btn_close
            // 
            this.btn_close.Font = new System.Drawing.Font("굴림", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.btn_close.Location = new System.Drawing.Point(271, 224);
            this.btn_close.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_close.Name = "btn_close";
            this.btn_close.Size = new System.Drawing.Size(57, 62);
            this.btn_close.TabIndex = 23;
            this.btn_close.Text = ")";
            this.btn_close.UseVisualStyleBackColor = true;
            this.btn_close.Click += new System.EventHandler(this.btn_close_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Info;
            this.ClientSize = new System.Drawing.Size(344, 434);
            this.Controls.Add(this.btn_close);
            this.Controls.Add(this.btn_open);
            this.Controls.Add(this.btn_dot);
            this.Controls.Add(this.btn_result);
            this.Controls.Add(this.btn_puls);
            this.Controls.Add(this.btn_sub);
            this.Controls.Add(this.btn_mul);
            this.Controls.Add(this.btn_div);
            this.Controls.Add(this.btn_9);
            this.Controls.Add(this.btn_8);
            this.Controls.Add(this.btn_7);
            this.Controls.Add(this.btn_6);
            this.Controls.Add(this.btn_5);
            this.Controls.Add(this.btn_4);
            this.Controls.Add(this.btn_3);
            this.Controls.Add(this.btn_2);
            this.Controls.Add(this.btn_1);
            this.Controls.Add(this.btn_0);
            this.Controls.Add(this.btn_clear);
            this.Controls.Add(this.btn_backspace);
            this.Controls.Add(this.texbox_num);
            this.Controls.Add(this.texbox_result);
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox texbox_result;
        private System.Windows.Forms.TextBox texbox_num;
        private System.Windows.Forms.Button btn_backspace;
        private System.Windows.Forms.Button btn_clear;
        private System.Windows.Forms.Button btn_0;
        private System.Windows.Forms.Button btn_1;
        private System.Windows.Forms.Button btn_2;
        private System.Windows.Forms.Button btn_3;
        private System.Windows.Forms.Button btn_4;
        private System.Windows.Forms.Button btn_5;
        private System.Windows.Forms.Button btn_6;
        private System.Windows.Forms.Button btn_7;
        private System.Windows.Forms.Button btn_8;
        private System.Windows.Forms.Button btn_9;
        private System.Windows.Forms.Button btn_div;
        private System.Windows.Forms.Button btn_mul;
        private System.Windows.Forms.Button btn_sub;
        private System.Windows.Forms.Button btn_puls;
        private System.Windows.Forms.Button btn_result;
        private System.Windows.Forms.Button btn_dot;
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.Button btn_close;
    }
}

