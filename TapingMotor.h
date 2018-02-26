#ifndef	_TapingMotor_H
#define	_TapingMotor_H
#ifdef	__cplusplus
extern	"C"	{
#endif

#define Motor_MotorOnSignal  0
#define Motor_AlarmResetSignal  1
#define Motor_CW_P  2

#define T_TIMER_FREQ_1            50		 // microseconds
#define S_T_TIMER_FREQ_1            400      // microseconds
#define T_TIMER_FREQ_2            50		 // 48 microseconds
#define S_T_TIMER_FREQ_2            400      // 48 microseconds
#define T_TIMER_FREQ_3            50		 // microseconds
#define S_T_TIMER_FREQ_3            400		 // microseconds
#define T_TIMER_FREQ_STEP_UP      1
#define T_TIMER_FREQ_STEP_DOWN    1


#define T_SPEED_CHANGE_DELAY_MAX       0.1
#define T_SPEED_CHANGE_DELAY_MIN       0.1
#define T_SPEED_CHANGE_DELAY_STEP_UP   0.1
#define T_SPEED_CHANGE_DELAY_STEP_DOWN 0.1

#define T_STEPS_NUM_FOR_1_LAP     1440
#define T_STEPS_NUM_FOR_2_LAPS    2880

#define	T_GEARS_RATIO             1

#define T_TIMER_CHANEL TIMER_CH1

extern int t_positive_port;
extern int M_AlarmResetSignal;
extern int M_MotorOnSignal;

extern int t_is_stopped;
extern int t_is_ready;
extern int t_is_counting;
extern int t_is_speed_down_started;
extern int t_on_off;
extern int t_counter, t_counter_speed_up, t_counter_speed_down;
extern int t_counter_speed_down_begin;
extern int t_steps_num_to_stop;
extern int SensorDetection;
extern int MotorHomeStart;
extern int CisHome;

extern void initT(int SettingPulse, int SpeedDown);
extern void startMotorT(void);
extern void startMotorT2(void);
extern void stopMotorT(void);
extern void speedUpT(int from, int to);
extern void speedDownT(int from, int to);
extern void speedDownCheckerT(void);
extern void handleMotorT(void);
extern void MotorHome(void);
extern void CheckCHomePos(void);
extern void ZeroReturn(void);
extern void StartToOrigin(void);
extern void Initialize_LoopConditions(void);
extern void Change_LoopConditions(void);
extern void AlarmReset(void);

#define ROTATE_TO_STEPS(x) (x / 360 * 1000)

#ifdef	__cplusplus
}
#endif
#endif
