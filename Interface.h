#ifndef	_Interface_H
#define	_Interface_H
#ifdef	__cplusplus
extern	"C"	{
#endif

/////////////////////////I/O_Config/////////////////////////
#define In_TapingStart		18
#define In_BarClose			19
#define In_CableTension		20
#define In_ReturnToOrigin	21
#define In_TapingCheck		22
#define Out_TapingFinished  23
#define Out_BarClosed		24
#define Out_TapingChecked	25

/////////////////////////I/O_Alias_Config/////////////////////////
extern int AI_TapingStart;
extern int AI_BarClose;
extern int AI_CableTension;
extern int AI_ReturnToOrigin;
extern int AI_TapingCheck;
extern int AO_TapingFinished;
extern int AO_BarClosed;
extern int AO_TapingChecked;

/////////////////////////I/O_Logic_Config/////////////////////////
extern int L_TapingStartFromIO;
extern int L_BarCloseFromIO;
extern int L_CableTensionFromIO;
extern int L_StartToOriginFromIO;
extern int L_TapingRemainCheckFromIO;
extern int Small;
extern int Large;

extern void initInterface(void);
extern void initI(void);
extern void IOCheck(void);
extern void USBCheck(void);
extern void SignalsRead(void);

extern void StartToOrigin(void);

#ifdef	__cplusplus
}
#endif
#endif
