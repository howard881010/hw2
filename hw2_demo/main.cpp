#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn But1(A0);         // decrease the freq
DigitalIn But2(A1);         // confirm freq
DigitalIn But3(A2);         // increase the freq
DigitalIn mypin(USER_BUTTON);
AnalogOut aout(PA_4);       // set the analog output
AnalogIn AIN(A3);           // set the analog input


int main(){
	int temp = 400;     // the frequency shown on the uLCD
	int freq = 400;     // the confirm frequency (the frequency of the output wave)	
	float data[100];    // sampled data
	uint16_t sample = 0;
	aout = 1;

    while (1) {
		// scan the button
		printf("%d", int(But1));
		if (But1 == 1) {
			temp -= 10;
			uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%d\n", temp);
		}

		if (But2 == 1) {
			freq = temp;
			//conf = 1;
			uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%d\n", freq);
			break;
		}

		if (But3 == 1) {
			temp += 10;
			uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%d\n", temp);
		}
	}
	printf("%d\r\n", freq);
	while(1){
		if (!mypin) break;
		for (int i = 0; i < 5; i++) {
            sample = (uint16_t)(59578 * i / 5);
            aout.write_u16(sample);
            data[i] = AIN;
            wait_us(20000/freq);
        }
        for (int i = 0; i < 45; i++) {
            sample = (uint16_t)(59578 * (45 - i) / 45);
            aout.write_u16(sample);
            data[i + 5] = AIN;
            wait_us(20000/freq);
        }
        for (int i = 0; i < 5; i++) {
            sample = (uint16_t)(59578 * i / 5);
            aout.write_u16(sample);
			data[i + 50] = AIN;
            wait_us(20000/freq);
        }
        for (int i = 0; i < 45; i++) {
            sample = (uint16_t)(59578 * (45 - i) / 45);
            aout.write_u16(sample);
	        data[i + 55] = AIN;
            wait_us(20000/freq);
        }
            
    }
    for (int i = 0; i < 100; i++) {
            printf("%f\r\n", data[i]);
    }
}
