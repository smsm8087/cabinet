﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class MapSizeForm : Form
    {
        public Size MapSize
        {
            get
            {
                return new Size(int.Parse(textBox1.Text), int.Parse(textBox2.Text));
            }
        }
       
        public MapSizeForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }
    }
}
