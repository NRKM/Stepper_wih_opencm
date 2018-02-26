#include <Common.h>

int Running_Status;
int loopCount    = 0;
int loopCount2   = 0;
int InputEntered = 0;
int microsec     = 1000;

char key = 0;
//-------------------------setup_Sequence---------------
void setup() {
  Running_Status = WAIT_INPUT;
  //---------------------Initial_Setup------------------
  initInterface();
  initAccessories();
}
//---------------------loop_Sequence---------------------
void loop() {
  if(InputEntered == 0){
    //---------------------waits_until_input-------------
    waitInput();
  }
  checkState();
  if(MotorHomeStart == 1){
    MotorHome();
  }
  //---------------------Taping_Sequence---------------------
  switch(Running_Status){
	case START_TAPING:
                AlarmReset();
                delay(100);
                loopCount =0;
                initMotors(250,65);
                startTaping();
                Running_Status = WAIT_INPUT;
		break;
	case OKURI_START:
                //---------------------Okuri_Start(OkuriTime, OkuriTime+MiddleOkuriTime)---------------
                Okuri_Start(75,0);
		break;
	case CUTTING_START:
                Cutting_Start();
                Running_Status = START_TAPING2;
		break;
	case START_TAPING2:
                initMotors(7750,65);
                startTaping();
                Running_Status = WAIT_INPUT;
		break;
	case OKURI_START2:
                if(Small ==1){
                  Okuri_Start(600,400);
                }
                if(Large ==1){
                  //Okuri_Start(650,325);
                  Okuri_Start(800,450);
                }
                Running_Status = CHECK_CHOMEPOS;
		break;
        //---------------------Note:No Sensor Ver.---------------
	case CHECK_CHOMEPOS:
                digitalWrite(AO_TapingFinished, HIGH);
                Initialize_LoopConditions();
		break;
        //---------------------Note:No Sensor Ver.---------------
        //---------------------Note:Sensor Ver.---------------
	//case CHECK_CHOMEPOS:
                //CheckCHomePos();
		//break;
	//case ZERO_RETURN:
                //ZeroReturn();
		//break;
        //---------------------Note:Sensor Ver.---------------
	default :
		break;
  }
  delayMicroseconds(microsec);
}
void waitInput() {
  IOCheck();
  USBCheck();
}
