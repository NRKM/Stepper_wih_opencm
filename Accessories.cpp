#include "Common.h"

//-----------------Sensors_Alias_Config-----------------
int AS_DeshiroSignal;
int AS_ZanryoSignal;
int AS_COriginSignal;
//-----------------Sensors_Logic_Config-----------------
int L_DeshiroSignal;
int L_ZanryoSignal;
//-----------------TapingMachines_Alias_Config-----------------
int T_Okuri;
int T_OkuriMiddle;
int T_Cut1;
int T_Cut2;
int T_HandROpen;
int T_HandRClose;
int T_HandLOpen;
int T_HandLClose;
int T_HandTension1;
int T_HandTension2;
int T_BarOpen;
int T_BarClose;

void initAccessories(void);
void Cutting_Start(void);
void Okuri_Start(int T_Okuri_Time, int T_OkuriMiddle_Time);
void Okuri_Start2(int T_Okuri2_Time, int T_OkuriMiddle2_Time);
void initA(void);
void BarClose(void);
void BarOpen(void);
void CableTension(void);
void TapingRemainCheck(void);
void HandsOpen(void);
void BarFlat(void);
void AirForTape_On(void);
void AirForTape_Off(void);

void initAccessories(void) {
	initA();
}

void initA() {
    //-----------------Sensors-----------------
    AS_DeshiroSignal  			= Sensor_DeshiroSignal;
    AS_ZanryoSignal   			= Sensor_ZanryoSignal;
    AS_COriginSignal	 		= Sensor_COriginSignal;
    //-----------------TapingMachines-----------------
	T_Okuri			 			= Taping_Okuri;
	T_OkuriMiddle	 			= Taping_OkuriMiddle;
	T_Cut1			 			= Taping_Cut1;
	T_Cut2			 			= Taping_Cut2;
	T_HandROpen		 			= Taping_HandROpen;
	T_HandRClose	 			= Taping_HandRClose;
	T_HandLOpen		 			= Taping_HandLOpen;
	T_HandLClose	 			= Taping_HandLClose;
	T_HandTension1	 			= Taping_HandTension1;
	T_HandTension2	 			= Taping_HandTension2;
	T_BarOpen					= Taping_BarOpen;
	T_BarClose					= Taping_BarClose;

    //-----------------Sensors-----------------
	pinMode(AS_DeshiroSignal	, INPUT_PULLDOWN);
	pinMode(AS_ZanryoSignal		, INPUT_PULLDOWN);
	pinMode(AS_COriginSignal	, INPUT_PULLDOWN);
    //-----------------TapingMachines-----------------
	pinMode(T_Okuri				, OUTPUT);
	pinMode(T_OkuriMiddle		, OUTPUT);
	pinMode(T_Cut1				, OUTPUT);
	pinMode(T_Cut2				, OUTPUT);
	pinMode(T_HandROpen			, OUTPUT);
	pinMode(T_HandRClose		, OUTPUT);
	pinMode(T_HandLOpen			, OUTPUT);
	pinMode(T_HandLClose		, OUTPUT);
	pinMode(T_HandTension1		, OUTPUT);
	digitalWrite(T_HandTension1 , LOW);
	pinMode(T_HandTension2		, OUTPUT);
	pinMode(T_BarOpen			, OUTPUT);
	pinMode(T_BarClose			, OUTPUT);
	digitalWrite(T_BarClose		, LOW);

}

void Cutting_Start() {
	digitalWrite(T_Cut1, LOW);
	digitalWrite(T_Cut2, HIGH);
	delay(200);
	digitalWrite(T_Cut2, LOW);
	digitalWrite(T_Cut1, HIGH);
}

//Okuri_Start:T_Okuri+T_OkuriMiddle_then_Only_T_OkuriMiddle_ver
//void Okuri_Start(int T_Okuri_Time, int T_OkuriMiddle_Time) {
//	int TimeDef = T_OkuriMiddle_Time - T_Okuri_Time;
//
//	if(loopCount == 1){
//		Running_Status = CUTTING_START;
//	}
//	digitalWrite(T_Okuri, HIGH);
//	digitalWrite(T_OkuriMiddle, HIGH);
//	delay(T_Okuri_Time);
//	digitalWrite(T_Okuri, LOW);
//	delay(TimeDef);
//	digitalWrite(T_OkuriMiddle, LOW);
//}

//Okuri_Start:Only_T_Okuri_then_T_Okuri+T_OkuriMiddle_ver
void Okuri_Start(int T_Okuri_Time, int T_OkuriMiddle_Time) {
	//int TimeDef = T_OkuriMiddle_Time - T_Okuri_Time;

	if(loopCount == 1){
		Running_Status = CUTTING_START;
	}
	digitalWrite(T_Okuri, HIGH);
	delay(T_Okuri_Time);
	digitalWrite(T_OkuriMiddle, HIGH);

	delay(T_OkuriMiddle_Time);
	digitalWrite(T_Okuri, LOW);
	digitalWrite(T_OkuriMiddle, LOW);
}

//Okuri_Start:T_Okuri+T_OkuriMiddle_then_Only_T_OkuriMiddle_ver
//void Okuri_Start2(int T_Okuri2_Time, int T_OkuriMiddle2_Time) {
//	int TimeDef2 = T_OkuriMiddle2_Time - T_Okuri2_Time;

//	digitalWrite(T_Okuri, HIGH);
//	digitalWrite(T_OkuriMiddle, HIGH);
//	delay(T_Okuri2_Time);
//	digitalWrite(T_Okuri, LOW);
//	delay(TimeDef2);
//	digitalWrite(T_OkuriMiddle, LOW);
//}

//Okuri_Start:Only_T_Okuri_then_T_Okuri+T_OkuriMiddle_ver
void Okuri_Start2(int T_Okuri2_Time, int T_OkuriMiddle2_Time) {
	int TimeDef2 = T_OkuriMiddle2_Time - T_Okuri2_Time;

	digitalWrite(T_Okuri, HIGH);
	delay(T_Okuri2_Time);
	digitalWrite(T_OkuriMiddle, HIGH);

	delay(T_OkuriMiddle2_Time);
	digitalWrite(T_Okuri, LOW);
	digitalWrite(T_OkuriMiddle, LOW);
}

void BarClose(){

	//--Initial Set For Bar Close
    digitalWrite(AO_BarClosed, LOW);
    digitalWrite(T_BarOpen	, LOW);
    delay(50);

	//--Bar Close
    digitalWrite(T_BarClose , HIGH);
    delay(50);

	//--Output Bar Closed Signal
    digitalWrite(AO_BarClosed, HIGH);
}

void BarOpen(){

	//--Initial Set For Bar Open
    digitalWrite(T_BarClose, LOW);
    delay(50);

	//--Bar Open
    digitalWrite(T_BarOpen, HIGH);
    delay(50);

	//--Output Bar Opened Signal(O_BarClosed OFF = Bar Opened)
    digitalWrite(AO_BarClosed, LOW);
}

void BarFlat(void){
	digitalWrite(T_BarOpen, LOW);
}

void CableTension(){

	//--Initial Set For Cable Tension Action
    digitalWrite(T_HandLOpen	, LOW);
    digitalWrite(T_HandROpen	, LOW);
    digitalWrite(T_HandTension2 , LOW);
    delay(50);

	//--Start Cable Tension Action
    digitalWrite(T_HandLClose	, HIGH);
    digitalWrite(T_HandRClose	, HIGH);
    delay(200);

	//--Slide HandR
    digitalWrite(T_HandTension1 , HIGH);
}

void TapingRemainCheck(){

	//--Initial Set For Cable Tension Action
	digitalWrite(Out_TapingChecked , LOW);
    delay(200);

	//--Read Sensor Status and Output Checked Signal 
	L_DeshiroSignal	 = digitalRead(AS_DeshiroSignal);
	L_ZanryoSignal	 = digitalRead(AS_ZanryoSignal);
	if(L_DeshiroSignal == HIGH && L_ZanryoSignal == HIGH){
	    digitalWrite(Out_TapingChecked , HIGH);
	}
}

void HandsOpen(){

	//--Initial Set For Cable Tension Action
    digitalWrite(T_HandRClose	, LOW);
    digitalWrite(T_HandLClose	, LOW);
    digitalWrite(T_HandTension1 , LOW);
    delay(100);

	//--Start Cable Tension Action
    digitalWrite(T_HandROpen	, HIGH);
    digitalWrite(T_HandLOpen	, HIGH);
    delay(200);

	//--Slide HandR
    digitalWrite(T_HandTension2 , HIGH);

}

void AirForTape_On(void){
	//--Initial Set For Cable Tension Action
    digitalWrite(T_HandRClose	, LOW);
    delay(100);

	//--Start Cable Tension Action
    digitalWrite(T_HandROpen	, HIGH);

}

void AirForTape_Off(void){
	//--Initial Set For Cable Tension Action
    digitalWrite(T_HandROpen	, LOW);
    delay(100);

	//--Start Cable Tension Action
    digitalWrite(T_HandRClose	, HIGH);

}
