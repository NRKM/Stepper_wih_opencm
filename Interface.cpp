#include "Common.h"

//----------------------Alias_Config----------------------
int AI_TapingStart;
int AI_BarClose;
int AI_CableTension;
int AI_ReturnToOrigin;
int AI_TapingCheck;
int AO_TapingFinished;
int AO_BarClosed;
int AO_TapingChecked;
//----------------------Logic_Config----------------------
int L_TapingStartFromIO;
int L_BarCloseFromIO;
int L_CableTensionFromIO;
int L_StartToOriginFromIO;
int L_TapingRemainCheckFromIO;
int Small;
int Large;

void initInterface(void);
void initI(void);
void IOCheck(void);
void USBCheck(void);
void SignalsRead(void);
void StartToOrigin(void);

void initInterface(void) {
	initI();
}

void initI() {
	//----------------------Signals_Alias----------------------
    AI_TapingStart			 =	In_TapingStart;
    AI_BarClose				 =	In_BarClose;
    AI_CableTension			 =	In_CableTension;
    AI_ReturnToOrigin		 =	In_ReturnToOrigin;
    AI_TapingCheck			 =	In_TapingCheck;
	AO_TapingFinished		 =	Out_TapingFinished;
	AO_BarClosed			 =	Out_BarClosed;
	AO_TapingChecked		 =	Out_TapingChecked;

	//----------------------Signals_Configration----------------------
	pinMode(AI_TapingStart	 , INPUT_PULLDOWN);
	pinMode(AI_BarClose		 , INPUT_PULLDOWN);
	pinMode(AI_CableTension	 , INPUT_PULLDOWN);
	pinMode(AI_ReturnToOrigin, INPUT_PULLDOWN);
	pinMode(AI_TapingCheck	 , INPUT_PULLDOWN);
	pinMode(AO_TapingFinished, OUTPUT);
	pinMode(AO_BarClosed	 , OUTPUT);
    digitalWrite(AO_BarClosed, LOW);
	pinMode(AO_TapingChecked , OUTPUT);

	//----------------------Signals_Configration----------------------
	M_AlarmResetSignal = Motor_AlarmResetSignal;
	pinMode(M_AlarmResetSignal, OUTPUT);
    digitalWrite(M_AlarmResetSignal, LOW);
	pinMode(M_MotorOnSignal, OUTPUT);
    digitalWrite(M_MotorOnSignal, HIGH);

}

//----------------------I/O----------------------
void IOCheck(){
  SignalsRead();
  //----------------------#17_Taping_Start----------------------
  if(loopCount2 == 0 && L_TapingStartFromIO == HIGH){
    SerialUSB.println("Received_TapingStartFromIO");
	Small = 1;
    TapingStart();
  }
  //----------------------#18_Bar_Close----------------------
  //if(L_BarCloseFromIO          == HIGH){
  //  SerialUSB.println("Received_BarCloseFromIO");
  //  BarClose();
  //}
  //----------------------#18_Bar_Close----------------------
  if(loopCount2 == 0 && L_BarCloseFromIO == HIGH){
    SerialUSB.println("Received_BarCloseFromIO");
	Large = 1;
    TapingStart();
  }
  //----------------------#19_Cable_Tension----------------------
  if(L_CableTensionFromIO      == HIGH){
    SerialUSB.println("Received_CableTensionFromIO");
    //CableTension();
	AirForTape_On();
  }
  //----------------------#20_Start_To_Origin----------------------
  if(L_StartToOriginFromIO     == HIGH){
    SerialUSB.println("Received_StartToOriginFromIO");
    //StartToOrigin();
	BarFlat();
	AirForTape_Off();
    //HandsOpen();
  }
  //----------------------#21_Taping_Remain_Check----------------------
  if(L_TapingRemainCheckFromIO == HIGH){
    SerialUSB.println("Received_TapingRemainCheckFromIO");
    BarOpen();
    //TapingRemainCheck();
  }
}

//----------------------Serial_USB----------------------
void USBCheck(){

  if(!isStopped()) return;
  if(!SerialUSB.available()) return;
  
  key = SerialUSB.read();
  SerialUSB.println(key);  
  //----------------------Taping_Start----------------------
  if(key == '0'){
    SerialUSB.println("Taping_Start");
    TapingStart();
  }
  //----------------------Okuri_Start----------------------
  if(key == '1'){
    SerialUSB.println("Okuri_Start:Okuri_Time:1s,OkuriMiddle_Time:1.2s");
    Okuri_Start2(400,400);
  }
  //----------------------Motor_Home----------------------
  if(key == '2'){
    SerialUSB.println("MotorHomeFromIO:3Rotation");
    StartToOrigin();
  }
  //----------------------Cutting----------------------
  if(key == '3'){
    SerialUSB.println("Cutting_Start");
    Cutting_Start();
  }
  //----------------------Servo_Off----------------------
  if(key == '4'){
    SerialUSB.println("Servo_Off");
    digitalWrite(M_MotorOnSignal, LOW);
  }
  //----------------------Motor_On----------------------
  if(key == '5'){  
    SerialUSB.println("Servo_On");
    digitalWrite(M_MotorOnSignal, HIGH);
  }
  //----------------------Sensor_Detected_Check----------------------
  if(key == '6'){
    SerialUSB.println("Sensor_Detected_Check");
    CisHome = digitalRead(AS_COriginSignal);
    if(CisHome == HIGH){
      SerialUSB.println("SensorDetected");
    }
  }
  //----------------------Reset----------------------
  if(key == '7'){
    SerialUSB.println("Alarm_Reset");
	AlarmReset();
  }
  //----------------------BarClose----------------------
  if(key == 'a'){
    SerialUSB.println("BarClose");
    BarClose();
  }
  //----------------------BarOpen----------------------
  if(key == 'b'){
    SerialUSB.println("BarOpen");
    BarOpen();
  }
  //----------------------Cable_Tension----------------------
  if(key == 'c'){
    SerialUSB.println("Cable_Tension");
    CableTension();
  }
  //----------------------Hands_Open----------------------
  if(key == 'd'){
    SerialUSB.println("Hands_Open");
    HandsOpen();
  }
  //----------------------IO_Check----------------------
  if(key == 'e'){
    SerialUSB.println("T_Okuri");
	digitalWrite(T_Okuri, HIGH);
    delay(500);
	digitalWrite(T_Okuri, LOW);
    SerialUSB.println("T_OkuriMiddle");
	digitalWrite(T_OkuriMiddle, HIGH);
    delay(500);
	digitalWrite(T_OkuriMiddle, LOW);
    SerialUSB.println("T_Cut1");
	digitalWrite(T_Cut1, HIGH);
    delay(500);
	digitalWrite(T_Cut1, LOW);
    SerialUSB.println("T_Cut2");
	digitalWrite(T_Cut2, HIGH);
    delay(500);
	digitalWrite(T_Cut2, LOW);
    SerialUSB.println("T_HandROpen");
	digitalWrite(T_HandROpen, HIGH);
    delay(500);
	digitalWrite(T_HandROpen, LOW);
    SerialUSB.println("T_HandRClose");
	digitalWrite(T_HandRClose, HIGH);
    delay(500);
	digitalWrite(T_HandRClose, LOW);
    SerialUSB.println("T_HandLOpen");
	digitalWrite(T_HandLOpen, HIGH);
    delay(500);
	digitalWrite(T_HandLOpen, LOW);
    SerialUSB.println("T_HandLClose");
	digitalWrite(T_HandLClose, HIGH);
    delay(500);
	digitalWrite(T_HandLClose, LOW);
    SerialUSB.println("T_HandTension1");
	digitalWrite(T_HandTension1, HIGH);
    delay(500);
	digitalWrite(T_HandTension1, LOW);
    SerialUSB.println("T_HandTension2");
	digitalWrite(T_HandTension2, HIGH);
    delay(500);
	digitalWrite(T_HandTension2, LOW);
    SerialUSB.println("T_BarOpen");
	digitalWrite(T_BarOpen, HIGH);
    delay(500);
	digitalWrite(T_BarOpen, LOW);
    SerialUSB.println("T_BarClose");
	digitalWrite(T_BarClose, HIGH);
    delay(500);
	digitalWrite(T_BarClose, LOW);
  }
  //----------------------IO_Check----------------------
  if(key == 'f'){
    SerialUSB.println("D23-ON");
	digitalWrite(AO_TapingFinished, HIGH);
    delay(500);
	digitalWrite(AO_TapingFinished, LOW);
    SerialUSB.println("D23-OFF");
  }
  if(key == 'g'){
    SerialUSB.println("D24-OFF");
	digitalWrite(AO_BarClosed, HIGH);
    delay(10000);
	digitalWrite(AO_BarClosed, LOW);
    SerialUSB.println("D24-OFF");
  }
  if(key == 'h'){
    SerialUSB.println("D25-OFF");
	digitalWrite(AO_TapingChecked, HIGH);
    delay(500);
	digitalWrite(AO_TapingChecked, LOW);
    SerialUSB.println("D25-OFF");
  }
  if(key == 'i'){
    SerialUSB.println("T_OkuriMiddle");
	digitalWrite(T_Okuri, HIGH);
    delay(100);
	digitalWrite(T_Okuri, LOW);
  }
  if(key == 'j'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_OkuriMiddle, HIGH);
    delay(100);
	digitalWrite(T_OkuriMiddle, LOW);
  }
  if(key == 'k'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_Cut1, HIGH);
    delay(2000);
	digitalWrite(T_Cut1, LOW);
  }
  if(key == 'l'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_Cut2, HIGH);
    delay(2000);
	digitalWrite(T_Cut2, LOW);
  }
  if(key == 'm'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_HandROpen, HIGH);
    delay(2000);
	digitalWrite(T_HandROpen, LOW);
    SerialUSB.println("D23-OFF");
  }
  if(key == 'n'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_HandRClose, HIGH);
    delay(2000);
	digitalWrite(T_HandRClose, LOW);
    SerialUSB.println("D23-OFF");
  }
  if(key == 'o'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_HandLOpen, HIGH);
    delay(2000);
	digitalWrite(T_HandLOpen, LOW);
    SerialUSB.println("D23-OFF");
  }
  if(key == 'p'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_HandLClose, HIGH);
    delay(2000);
	digitalWrite(T_HandLClose, LOW);
  }
  if(key == 'q'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_HandTension1, HIGH);
    delay(2000);
	digitalWrite(T_HandTension1, LOW);
  }
  if(key == 'r'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_HandTension2, HIGH);
    delay(2000);
	digitalWrite(T_HandTension2, LOW);
  }
  if(key == 's'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_BarOpen, HIGH);
    delay(2000);
	digitalWrite(T_BarOpen, LOW);
  }
  if(key == 't'){
    SerialUSB.println("D23-ON");
	digitalWrite(T_BarClose, HIGH);
    delay(2000);
	digitalWrite(T_BarClose, LOW);
  }
  if(key == 'u'){
    SerialUSB.println("barflat");
	BarFlat();
  }
}

void SignalsRead(){

	L_TapingStartFromIO		     = digitalRead(AI_TapingStart);
	L_BarCloseFromIO			 = digitalRead(AI_BarClose);
	L_CableTensionFromIO		 = digitalRead(AI_CableTension);
	L_StartToOriginFromIO		 = digitalRead(AI_ReturnToOrigin);
	L_TapingRemainCheckFromIO    = digitalRead(AI_TapingCheck);

}