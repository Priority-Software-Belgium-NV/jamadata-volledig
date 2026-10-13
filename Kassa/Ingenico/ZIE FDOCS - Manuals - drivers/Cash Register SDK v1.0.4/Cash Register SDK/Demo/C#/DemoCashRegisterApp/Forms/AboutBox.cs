// =========================================================================================
// =================================== U T I L I T I E S ===================================
// =========================================================================================
//
//		Module: Utilities.Forms
//		File  : AboutBox.cs
//		Author: rdem
//
//		Description:
//		AboutBox form.
//
//
//		Last Modification:
//		$Id:
//
// -------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System;
using System.Reflection;
using System.Windows.Forms;


namespace ChessPt.Utilities.Forms
{
	/// <summary>
	/// AboutBox form.
	/// </summary>
	partial class AboutBox: System.Windows.Forms.Form
	{
		public AboutBox()
		{
			InitializeComponent();

			// Initialise the texts.
			this.Text += String.Format(" {0}", AssemblyProduct);
			this.productNameLabel.Text = AssemblyProduct;
			this.versionLabel.Text += String.Format(" {0}", Application.ProductVersion);
			this.copyrightLabel.Text = AssemblyCopyright;
		}

		#region Assembly Attribute Accessors


		/// <summary>
		/// Retrieve the title of the assembly.
		/// </summary>
		public static string AssemblyTitle
		{
			get
			{
				object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyTitleAttribute), false);
				if (attributes.Length > 0)
				{
					AssemblyTitleAttribute titleAttribute = (AssemblyTitleAttribute)attributes[0];
					if (titleAttribute.Title != "")
					{
						return titleAttribute.Title;
					}
				}
				return System.IO.Path.GetFileNameWithoutExtension(Assembly.GetExecutingAssembly().CodeBase);
			}
		}

		
		/// <summary>
		/// Retrieve the version of the assembly.
		/// </summary>
		public static string AssemblyVersion
		{
			get
			{
				return Assembly.GetExecutingAssembly().GetName().Version.ToString();
			}
		}


		/// <summary>
		/// Retrieve the description of the assembly.
		/// </summary>
		public static string AssemblyDescription
		{
			get
			{
				object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyDescriptionAttribute), false);
				if (attributes.Length == 0)
				{
					return "";
				}
				return ((AssemblyDescriptionAttribute)attributes[0]).Description;
			}
		}


		/// <summary>
		/// Retrieve the product of the assembly.
		/// </summary>
		public static string AssemblyProduct
		{
			get
			{
				object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyProductAttribute), false);
				if (attributes.Length == 0)
				{
					return "";
				}
				return ((AssemblyProductAttribute)attributes[0]).Product;
			}
		}


		/// <summary>
		/// Retrieve the copyright information of the assembly.
		/// </summary>
		public static string AssemblyCopyright
		{
			get
			{
				object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCopyrightAttribute), false);
				if (attributes.Length == 0)
				{
					return "";
				}
				return ((AssemblyCopyrightAttribute)attributes[0]).Copyright;
			}
		}


		/// <summary>
		/// Retrieve the company information of the assembly.
		/// </summary>
		public static string AssemblyCompany
		{
			get
			{
				object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCompanyAttribute), false);
				if (attributes.Length == 0)
				{
					return "";
				}
				return ((AssemblyCompanyAttribute)attributes[0]).Company;
			}
		}

		#endregion
	}
}
