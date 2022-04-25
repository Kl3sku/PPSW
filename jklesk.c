#include <LPC21xx.H>
#define LED0_BM (1<<16)
#define LED1_BM (1<<17)
#define LED2_BM (1<<18)
#define LED3_BM (1<<19)
#define CONSTANT_CONVERT 2500

#define BUTTON0_BM 1<<4
#define BUTTON1_BM 1<<6
#define BUTTON2_BM 1<<5
#define BUTTON3_BM 1<<7


void Delay(int iTimeInMili)
{
	int iCycleCounter;
	int iTimeConverter = iTimeInMili * CONSTANT_CONVERT;
	
	for(iCycleCounter=0;iCycleCounter<iTimeConverter;iCycleCounter++) {}
}
void LedInit(void){
	IO1DIR = LED0_BM | LED1_BM | LED2_BM | LED3_BM;
//	IO1SET = LED0_BM;
}
void KeyboardInit(void){
	
	IO0DIR = IO0DIR &(~(BUTTON0_BM | BUTTON1_BM | BUTTON2_BM | BUTTON3_BM));
}


void LedOn(unsigned char ucLedIndeks){
	LedInit();
	IO1CLR = LED0_BM | LED1_BM | LED2_BM | LED3_BM;
	switch (ucLedIndeks) {
		case 0:
			IO1SET = LED0_BM;
			break;
		case 1:
			IO1SET = LED1_BM;
			break;
		case 2:
			IO1SET = LED2_BM;
			break;
		case 3:
			IO1SET = LED3_BM;
			break;
		default:
			break;
	}
}
enum KeyboardState {RELASED,BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum KeyboardState eKeyboardRead(void){
	
	KeyboardInit();
	if (~(IO0PIN) & BUTTON0_BM){
		return BUTTON_0;
	}
	else if(~(IO0PIN) & BUTTON1_BM){
		return BUTTON_1;
	}
	else if (~(IO0PIN) & BUTTON2_BM ){
		return BUTTON_2;
	}
	else if (~(IO0PIN) & BUTTON3_BM ){
		return BUTTON_3;
	}
	else{
		return RELASED;
	}
}

enum Turn{LEFT,RIGHT};

void LedStep(enum Turn eCurrent){
	
	static unsigned int uiLedState = 0;
	
	if (eCurrent == LEFT){
		uiLedState = ((++uiLedState)%4);
		
	}		
	else if(eCurrent == RIGHT){
		uiLedState = ((--uiLedState)%4);	
	}
	LedOn(uiLedState);
	Delay(250);
}
void LedStepRight(void){
	
	LedStep(RIGHT);
}
void LedStepLeft(void){
	
	LedStep(LEFT);
}
int main()
{
	LedInit();
	KeyboardInit();
	Delay(1000);
	while(1){
		switch(eKeyboardRead()){
			case BUTTON_0:
				break;
			case BUTTON_1:
				LedStepRight();
				Delay(300);
				break;
			case BUTTON_2:
				LedStepLeft();
			  Delay(300);
				break;
			case BUTTON_3:
				break;
			default:
				break;
		}
	}

}