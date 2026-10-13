namespace ChessPt.CashRegister.Properties 
{
	
	
	// This class allows you to handle specific events on the settings class:
	//  The SettingChanging event is raised before a setting's value is changed.
	//  The PropertyChanged event is raised after a setting's value is changed.
	//  The SettingsLoaded event is raised after the setting values are loaded.
	//  The SettingsSaving event is raised before the setting values are saved.
	internal sealed partial class Settings
	{
		
		public Settings() 
		{
			// // To add event handlers for saving and changing settings, uncomment the lines below:
			//
			// this.SettingChanging += this.SettingChangingEventHandler;
			//
			// this.SettingsSaving += this.SettingsSavingEventHandler;
			//
		}
		
		private void SettingChangingEventHandler(object sender, System.Configuration.SettingChangingEventArgs e) 
		{
			// Add code to handle the SettingChangingEvent event here.
		}
		
		private void SettingsSavingEventHandler(object sender, System.ComponentModel.CancelEventArgs e) 
		{
			// Add code to handle the SettingsSaving event here.
		}

		/// <summary>
		/// Upgrade settings in case of new version of the application (The program runs for the first time).
		/// </summary>
		public void UpgradeSettings()
		{
			// Upgrade settings in case of new version of the application (The program runs for the first time).
			if (this.FirstRun)
			{
				// Upgrade and save settings.
				this.Upgrade();
				this.FirstRun = false;
				this.Save();
			}
		}
	}
}
