/*
    Blink 2 Led with push button
    By Domenico Luciani aka DLion 
    To compile it you can do:
    gcc source_name.c -o binary_name -lwiringPi
    obviously you have to install the wiringPi libraries.
    and after you have to do:
    sudo ./binary_name
    and when you will press the push button you'll see leds turn on.
*/

//Using wiringPi library
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    //Using pin 8 to read input (pin 3 on the raspi)
    int pin8_in = 8;
    //Using pin 0 and 1 to write output (pin 11 and 12 on the raspi)
    int pin0_out = 0;
    int pin1_out = 1;
    
     //Starting Setup
    if(wiringPiSetup() == -1)
        exit(1);
    //Set pin 8 to input
    pinMode(pin8_in,INPUT);
    //Set pin 0 and 1 to output
    pinMode(pin0_out,OUTPUT);
    pinMode(pin1_out,OUTPUT);

    while(1)
    {
        //Push button pressed
        if(digitalRead(pin8_in) == 0)
        {
            //LED 0 ON
            digitalWrite(pin0_out,1);
            //Wait 50 ms
            delay(50);
            //LED 1 ON
            digitalWrite(pin1_out,1);
            delay(50);
            //LED 0 OFF 
            digitalWrite(pin0_out,0);
            delay(50);
            //LED 1 OFF
            digitalWrite(pin1_out,0);
            delay(50);
        }
        //Wait 100 ms
        delay(100);
    }
    return 0;
}