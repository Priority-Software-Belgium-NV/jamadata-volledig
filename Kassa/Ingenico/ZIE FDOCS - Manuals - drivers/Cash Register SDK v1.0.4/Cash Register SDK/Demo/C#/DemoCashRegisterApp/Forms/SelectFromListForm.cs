// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//      Module: Forms
//      File  : SelectFromListForm.cs
//      Author: rdem
//
//
//      Description:
//      Form class for selecting a security scheme or acquirer.
//
//
//      Last Modification:
//      $Id:
//
// ----------------------------------------------------------------------------------------- 
//      Modifications:
//      Date		Author  Issue	Comment
//
//
// =========================================================================================
// (C) Chess pT  2015
// =========================================================================================


using System;
using System.Windows.Forms;
using ChessPt.TlvCashRegisterLib;

namespace TeliumCashRegister.Forms
{
    using SecuritySchemeList = System.Collections.Generic.List<SecurityScheme>;
    using AcquirerList = System.Collections.Generic.List<Acquirer>;


    /// <summary>
    /// Form class for selecting a security scheme or acquirer.
    /// </summary>
    public partial class SelectFromListForm: System.Windows.Forms.Form
    {
        // The list with security schemes to choose from.
        private SecuritySchemeList mSecuritySchemes = null;

        // The list with acquires to choose from.
        private AcquirerList mAcquirers = null;

        // The selected ID
        private int mSelectedId = 0;


        /// <summary>
        /// Constructor used for "Clear CTAP database"
        /// </summary>
        /// <param name="Clear options">The list with security schemes to display.</param>
        public SelectFromListForm()
        {
            InitializeComponent();

            this.Text = "Clear CTAP database";

            // Fill options.
            ListViewItem item = listView.Items.Add("0");
            item.SubItems.Add("Just ReBoot");
            item.Tag = 0;

            // Fill options.
            item = listView.Items.Add("1");
            item.SubItems.Add("ClearDatabase Partial");
            item.Tag = 1;

            item = listView.Items.Add("2");
            item.SubItems.Add("ClearDatabase Full");
            item.Tag = 2;

            item = listView.Items.Add("3");
            item.SubItems.Add("Delete CTAP database");
            item.Tag = 3;

            // Select the first item.
            listView.Items[0].Selected = true;
        }


        /// <summary>
        /// Constructor with security schemes.
        /// </summary>
        /// <param name="securitySchemes">The list with security schemes to display.</param>
        public SelectFromListForm(SecuritySchemeList securitySchemes)
        {
            InitializeComponent();

            // Fill security schemes.
            if (securitySchemes != null)
            {
                this.Text = "Select security scheme";
                mSecuritySchemes = securitySchemes;

                foreach (SecurityScheme scheme in mSecuritySchemes)
                {
                    ListViewItem item = listView.Items.Add(scheme.SecurityId.ToString());
                    item.SubItems.Add(scheme.Name);
                    item.Tag = scheme.SecurityId;
                }

                // Select the first item.
                if (listView.Items.Count > 0) listView.Items[0].Selected = true;
                else btnOK.Enabled = false;
            }
        }


        /// <summary>
        /// Constructor with acquirers.
        /// </summary>
        /// <param name="acquirers">The list with acquirers to display.</param>
        public SelectFromListForm(AcquirerList acquirers)
        {
            InitializeComponent();

            // Fill security schemes.
            if (acquirers != null)
            {
                this.Text = "Select acquirer";
                mAcquirers = acquirers;

                foreach (Acquirer acq in mAcquirers)
                {
                    ListViewItem item = listView.Items.Add(acq.AcquirerId.ToString());
                    item.SubItems.Add(acq.Name);
                    item.Tag = acq.AcquirerId;
                }

                // Select the first item.
                if (listView.Items.Count > 0) listView.Items[0].Selected = true;
                else btnOK.Enabled = false;
            }
        }

        
        
        /// <summary>
        /// Retrieve the selected ID.
        /// </summary>
        public int SelectedId
        {
            get { return mSelectedId;  }
        }


        /// <summary>
        /// The selected item changed.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The event arguments.</param>
        private void listView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listView.SelectedItems.Count != 0)
            {
                mSelectedId = (int)listView.SelectedItems[0].Tag;
                btnOK.Enabled = true;
            }
            else btnOK.Enabled = false;
        }


        /// <summary>
        /// List item double clicked.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The event arguments.</param>
        private void listView_DoubleClick(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
