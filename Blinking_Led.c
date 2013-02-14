/*
    Blink a simple LED connect with RaspBerryPi
    By Domenico Luciani aka DLion 
    To compile it you can do:
    gcc source_name.c -o binary_name -lwiringPi
    obviously you have to install the wiringPi libraries.
    and after you have to do:
    sudo ./binary_name
*/

//Using wiringPi library
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define ON 1
#define OFF 0


int main (void)
{
    //Using pin 0 to write output (pin 11 on the raspi)
    int pin = 0;
    
     //Starting Setup
    if(wiringPiSetup() == -1)
        exit(1);

    //Set pin to output
    pinMode(pin,OUTPUT);
   
    while(1)
    {
        //Led ON
        digitalWrite(pin,ON);
        //Wait 500ms
        delay(500);
        //Led OFF
        digitalWrite(pin,OFF);
        //Wait 500ms
        delay(500);
    }
    return 0;
}