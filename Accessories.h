#ifndef	_Accessories_H
#define	_Accessories_H
#ifdef	__cplusplus
extern	"C"	{
#endif

//-----------------Sensors_Config-----------------
#define Sensor_COriginSignal      3
#define Sensor_DeshiroSignal	  4
#define Sensor_ZanryoSignal		  5
//-----------------TapingMachines_Config-----------------
#define Taping_Okuri			  6
#define Taping_OkuriMiddle		  7
#define Taping_Cut1				  8  //#1
#define Taping_Cut2				  9  //#2
#define Taping_HandROpen		  10 //#3
#define Taping_HandRClose		  11 //#4
#define Taping_HandLOpen		  12 //#5
#define Taping_HandLClose		  13 //#6
#define Taping_HandTension1		  14 //#7
#define Taping_HandTension2		  15 //#8
#define Taping_BarOpen			  16 //#9
#define Taping_BarClose			  17 //#10

//-----------------Sensors_Alias_Config-----------------
extern int AS_COriginSignal;
extern int AS_DeshiroSignal;
extern int AS_ZanryoSignal;
//-----------------Sensors_Logic_Config-----------------
extern int L_DeshiroSignal;
extern int L_ZanryoSignal;
//-----------------TapingMachines_Alias_Config-----------------
extern int T_Okuri;
extern int T_OkuriMiddle;
extern int T_Cut1;
extern int T_Cut2;
extern int T_HandROpen;
extern int T_HandRClose;
extern int T_HandLOpen;
extern int T_HandLClose;
extern int T_HandTension1;
extern int T_HandTension2;
extern int T_BarOpen;
extern int T_BarClose;

extern void initAccessories(void);
extern void Cutting_Start(void);
extern void Okuri_Start(int T_Okuri_Time, int T_OkuriMiddle_Time);
extern void Okuri_Start2(int T_Okuri2_Time, int T_OkuriMiddle2_Time);
extern void initA(void);
extern void BarClose(void);
extern void BarOpen(void);
extern void CableTension(void);
extern void TapingRemainCheck(void);
extern void HandsOpen(void);
extern void BarFlat(void);
extern void AirForTape_On(void);
extern void AirForTape_Off(void);

#ifdef	__cplusplus
}
#endif
#endif
