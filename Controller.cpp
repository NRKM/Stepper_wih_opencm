#include "Common.h"
int cur_step;

void initMotors(int Rotation, int SpeedDown);
void TapingStart(void);
void startTaping(void);
void startTaping2(void);
void moveLinear(void);
void stopLinear(void);
void speedDownChecker(void);
void checkState(void);
int  isStopped(void);

void initMotors(int SettingPulse, int SpeedDown) {
	initT(SettingPulse, SpeedDown);
}

void TapingStart(void){
	Change_LoopConditions();
    SerialUSB.println(microsec);
    digitalWrite(AO_TapingFinished, LOW);

    digitalWrite(M_MotorOnSignal, HIGH);
    delay(200);
    Running_Status = START_TAPING;
    loopCount2++;
}

void startTaping(void) {
	startMotorT();
}

void startTaping2(void) {
	startMotorT2();
}

void speedDownChecker(void) {
	speedDownCheckerT();
}

void checkState(void) {
	speedDownChecker();
}

int isStopped(void) {
	if(t_is_stopped) return 1;
	return 0;
}
