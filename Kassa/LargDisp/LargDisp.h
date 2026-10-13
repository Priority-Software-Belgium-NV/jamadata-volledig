
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LargDisp_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LargDisp_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LargDisp_EXPORTS
#define LargDisp_API __declspec(dllexport)
#else
#define LargDisp_API __declspec(dllimport)
#endif

// This class is exported from the LargDisp.dll
class LargDisp_API CLargDisp {
public:
	CLargDisp(void);
	// TODO: add your methods here.
};

extern LargDisp_API int nLargDisp;

LargDisp_API int FindExtraDisplay(char *Name);
LargDisp_API int DisableExtraDisplay(char *Name);


