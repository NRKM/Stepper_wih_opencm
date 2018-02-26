#ifndef	_Controller_H
#define	_Controller_H
#ifdef	__cplusplus
extern	"C"	{
#endif


extern void initMotors(int SettingPulse, int SpeedDown);
extern void TapingStart(void);
extern void startTaping(void);
extern void startTaping2(void);
extern void moveLinear(void);
extern void stopLinear(void);
extern void speedDownChecker(void);
extern void checkState(void);
extern int  isStopped(void);

#ifdef	__cplusplus
}
#endif
#endif
