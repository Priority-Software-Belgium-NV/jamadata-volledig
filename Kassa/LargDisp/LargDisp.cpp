// LargDisp.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "LargDisp.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
LargDisp_API int nLargDisp=0;

// This is an example of an exported function.
LargDisp_API int FindExtraDisplay(char *Name)
{
	int DispNr;
	DISPLAY_DEVICE DispDevice;
  DEVMODE   defaultMode;

	DispDevice.cb=sizeof(DispDevice);
  ZeroMemory(&defaultMode, sizeof(DEVMODE));
  defaultMode.dmSize = sizeof(DEVMODE);
 
	for (DispNr=0; DispNr<100; DispNr++) {
    if (!EnumDisplayDevices(NULL,DispNr,&DispDevice, NULL)) break;
    if (!(DispDevice.StateFlags&DISPLAY_DEVICE_MIRRORING_DRIVER) &&
			!(DispDevice.StateFlags&DISPLAY_DEVICE_PRIMARY_DEVICE)) {

 			strcpy(Name,DispDevice.DeviceName); // .DeviceString; //.DeviceName; // 
			if (!(DispDevice.StateFlags&DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)) {
        EnumDisplaySettings((LPSTR)DispDevice.DeviceName, ENUM_REGISTRY_SETTINGS, &defaultMode);
				defaultMode.dmFields|=DM_POSITION;
				ChangeDisplaySettingsEx((LPSTR)DispDevice.DeviceName, &defaultMode, NULL, CDS_UPDATEREGISTRY, NULL);
        ChangeDisplaySettingsEx((LPSTR)DispDevice.DeviceName, &defaultMode, NULL, CDS_UPDATEREGISTRY, NULL);
			}
			return 1;
		}
	}
	return 0;
}


LargDisp_API int DisableExtraDisplay(char *Name)
{
	int DispNr;
	DISPLAY_DEVICE DispDevice;
  DEVMODE   defaultMode;

	DispDevice.cb=sizeof(DispDevice);
  ZeroMemory(&defaultMode, sizeof(DEVMODE));
  defaultMode.dmSize = sizeof(DEVMODE);
 
	for (DispNr=0; DispNr<100; DispNr++) {
    if (!EnumDisplayDevices(NULL,DispNr,&DispDevice, NULL)) break;
		if (strcmp(Name,DispDevice.DeviceName)==0) {
      EnumDisplaySettings((LPSTR)DispDevice.DeviceName, ENUM_REGISTRY_SETTINGS, &defaultMode);
			defaultMode.dmFields=DM_POSITION | DM_PELSWIDTH | DM_PELSHEIGHT;
			defaultMode.dmPosition.x=0;
			defaultMode.dmPosition.y=0;
			defaultMode.dmPelsHeight=0;
			defaultMode.dmPelsWidth=0;
			ChangeDisplaySettingsEx((LPSTR)DispDevice.DeviceName, &defaultMode, NULL, CDS_GLOBAL | CDS_UPDATEREGISTRY, NULL);
//	  	ChangeDisplaySettingsEx((LPSTR)DispDevice.DeviceName, &defaultMode, NULL, CDS_UPDATEREGISTRY, NULL);
			return 1;
		}
	}
	return 0;
}


// This is the constructor of a class that has been exported.
// see LargDisp.h for the class definition
CLargDisp::CLargDisp()
{ 
	return; 
}


