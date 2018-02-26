#include "Common.h"

HardwareTimer t_timer(1);

int t_positive_port;
int M_MotorOnSignal;
int M_AlarmResetSignal;

int t_steps_num;
int t_is_stopped = 1;
int t_is_ready;
int t_is_counting;
int t_is_speed_down_started = 0;
int t_on_off;
int t_counter, t_counter_speed_up, t_counter_speed_down;
int t_steps_num_to_stop;
int times;
int t_counter_speed_down_begin;
int T_SPEED_DOWN_STEPS_NUM;
int T_SensorDetected;
int SensorDetection;
int MotorHomeStart;
int CisHome;

void initT(int SettingPulse, int SpeedDown);
void startMotorT(void);
void startMotorT2(void);
void stopMotorT(void);
void speedUpT(int from, int to);
void speedDownT(int from, int to);
void speedDownCheckerT(void);
void handleMotorT(void);
void MotorHome(void);
void CheckCHomePos(void);
void ZeroReturn(void);
void StartToOrigin(void);
void Initialize_LoopConditions(void);
void Change_LoopConditions(void);
void AlarmReset(void);


void initT(int SettingPulse, int SpeedDown) {

	t_positive_port = Motor_CW_P;
	M_MotorOnSignal = Motor_MotorOnSignal;

	times = 0;
    t_steps_num = SettingPulse;
	T_SPEED_DOWN_STEPS_NUM = SpeedDown;

	t_is_stopped = 1;
	t_is_ready = 0;
	t_is_counting = 0;
	t_is_speed_down_started = 0;
	t_on_off = 0;
	t_counter = 0;
	t_counter_speed_up = 0;
	t_counter_speed_down = 0;
	t_steps_num_to_stop = 0;
	t_counter_speed_down_begin = t_steps_num - T_SPEED_DOWN_STEPS_NUM;

	pinMode(t_positive_port, OUTPUT);

	t_timer.pause();
  	t_timer.setPeriod(T_TIMER_FREQ_1); // in microseconds
  	t_timer.setMode(T_TIMER_CHANEL, TIMER_OUTPUT_COMPARE);
  	t_timer.setCompare(T_TIMER_CHANEL, 1);
  	t_timer.attachInterrupt(T_TIMER_CHANEL, handleMotorT);
}

void startMotorT(void) {
	cur_step = STEP_FIRST_2_LAPS;

	t_timer.refresh();
	t_timer.resume();
	t_is_stopped = 0;

	speedUpT(T_TIMER_FREQ_1, T_TIMER_FREQ_2);
}

void startMotorT2(void) {
	cur_step = STEP_FIRST_2_LAPS;

	t_timer.refresh();
	t_timer.resume();
	t_is_stopped = 0;

	speedUpT(S_T_TIMER_FREQ_1, S_T_TIMER_FREQ_2);
}

void stopMotorT(void) {
	
	digitalWrite(t_positive_port, LOW);
	t_timer.pause();
	t_is_stopped = 1;

	cur_step = TAPING_FINISHED;
}

void speedUpT(int from, int to) {

	t_counter = 0;
	t_is_counting = 1;

	int j = 0;
	for(int i = from; i >= to; i -= T_TIMER_FREQ_STEP_UP) {
	    t_timer.setPeriod(i); // in microseconds
	    delay(T_SPEED_CHANGE_DELAY_MAX - j*T_SPEED_CHANGE_DELAY_STEP_UP);
	    j++;
	}

	t_counter_speed_up = t_counter;
}

void speedDownT(int from, int to) {

	t_counter_speed_down = t_counter;
	SerialUSB.println("Start_speedDownT");

	int j = 0;
	for(int i = from; i <= to; i += T_TIMER_FREQ_STEP_DOWN) {
		
		if(t_counter >= t_steps_num) break;
		
		t_timer.setPeriod(i);
		delay(T_SPEED_CHANGE_DELAY_MIN + j*T_SPEED_CHANGE_DELAY_STEP_DOWN);
		j++; 
	}

	t_counter_speed_down = t_counter - t_counter_speed_down;
	t_is_counting = 0;

	stopMotorT();

	SerialUSB.println("taping finished");
	SerialUSB.println(t_steps_num_to_stop);
	SerialUSB.print("t_counter");
	SerialUSB.println(t_counter);
	SerialUSB.print("t_counter_speed_up");
	SerialUSB.println(t_counter_speed_up);
	SerialUSB.print("t_counter_speed_down");
	SerialUSB.println(t_counter_speed_down);

	if(loopCount==0){
		Running_Status = OKURI_START;
		loopCount++;
	}else if(loopCount==1){
		Running_Status = OKURI_START2;
		loopCount++;
	}

}

void speedDownCheckerT(void)  {

	if(t_is_speed_down_started) {
		t_is_speed_down_started = 0;
		speedDownT(T_TIMER_FREQ_2, T_TIMER_FREQ_3);
	}
}

void handleMotorT(void) {

	if(t_is_stopped) return;

	if(t_is_counting) t_counter++;
	if(!t_is_speed_down_started && (t_counter == t_counter_speed_down_begin)) {
		t_is_speed_down_started = 1;
	}

	digitalWrite(t_positive_port, t_on_off);
	t_on_off = 1 - t_on_off;
}

void MotorHome(void) {
    
	SensorDetection = digitalRead(AS_COriginSignal);

	if(SensorDetection == HIGH){
        SerialUSB.print("SensorDetected");
        digitalWrite(AO_TapingFinished, HIGH);
        stopMotorT();
        MotorHomeStart = 0;
      }
    Initialize_LoopConditions();
}

void CheckCHomePos(void) {

	Running_Status = WAIT_INPUT;
    CisHome = digitalRead(AS_COriginSignal);
    delay(200);

	if (CisHome == HIGH){
       SerialUSB.println("C is Home");
       digitalWrite(AO_TapingFinished, HIGH);
       Initialize_LoopConditions();
    }

    if (CisHome == LOW){
       SerialUSB.println("C is not Home.");
       SerialUSB.println("Execute zero return once....");
       Running_Status = ZERO_RETURN;
    }
}

void ZeroReturn(void){
    initMotors(2000,3);
    startTaping2();
    loopCount = 2;
    MotorHomeStart = 1;
    Running_Status = WAIT_INPUT;
}

void StartToOrigin(void){

	Change_LoopConditions();
	digitalWrite(AO_TapingFinished, LOW);
    initMotors(6000,3);
    startTaping2();
    Running_Status = WAIT_INPUT;
    loopCount = 2;
    MotorHomeStart = 1;
}

void Change_LoopConditions(void){
    InputEntered = 1;
	microsec     = 50;
}

void Initialize_LoopConditions(void){
    loopCount2   = 0;
    microsec     = 1000;
    InputEntered = 0;
    Small = 0;
    Large = 0;
}

void AlarmReset(void){

    digitalWrite(M_AlarmResetSignal, HIGH);
    delay(200);
    digitalWrite(M_AlarmResetSignal, LOW);

}