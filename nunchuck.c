/*
 * The MIT License (MIT)
 * Copyright (c) 2014 Domenico Luciani http://dlion.it domenicoleoneluciani@gmail.com
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define DEVICE "/dev/i2c-1"
#define ADDRESS 0x52
#define LEGGI 0
#define SCRIVI 1

int comunica(char*, int, int);

int main(void) 
{
    char buffer_read[6], //Buffer ricezione byte
         buffer_init[] = { 0xF0, 0x55 }, //Sequenza di init
         buffer_stop[] = { 0x00 }; //Sequenza di stop
  
    int file; //File handler
    int z, c; //Pulsanti
    int responso; //Responso della comunicazione

    responso = comunica(buffer_init, 2, SCRIVI);
    if(responso == 0)
        puts("Init avvenuto con successo");
    else
    {
        printf("Errore nella comunicazione %d\n", responso);
        exit(responso);
    }
      
    while(responso == 0)
    {
        //Stop
        responso = comunica(buffer_stop, 1, SCRIVI);
        if(responso != 0)
        {
            printf("Errore nella comunicazione %d\n", responso);
            exit(responso);
        }

        //Leggo
        responso = comunica(buffer_read, 6, LEGGI);
        if(responso != 0)
        {
            printf("Errore nella comunicazione %d\n", responso);
            exit(responso);
        }

        // Pulsanti
        z = buffer_read[5] & 0x01;
        c = (buffer_read[5] >> 1) & 0x01;
    
        //Asse X
        buffer_read[2] <<= 2;
        buffer_read[2] |= ((buffer_read[5] >> 2) & 0x03);
        //Asse Y		
        buffer_read[3] <<= 2;
        buffer_read[3] |= ((buffer_read[5] >> 6) & 0x03);

        printf("Analog X: %d Analog Y: %d Asse-X: %d Asse-Y: %d Asse-Z: %d ", buffer_read[0], buffer_read[1], buffer_read[2], buffer_read[3], buffer_read[4]);

        printf("Pulsante Z: ");
        (z == 1) ? printf("non premuto ") : printf("premuto ");
    
        printf("Pulsante C: ");
        (c == 1) ? printf("non premuto\n\f") : printf("premuto\n\f");
    
        usleep(200000);
    }
    
    return 0;
}

int comunica(char *buffer, int ndati, int mod)
{
    int file;

    if((file = open(DEVICE, O_RDWR)) < 0)
        return -1;

    if(ioctl(file, I2C_SLAVE, ADDRESS) < 0)
        return -2;

    if(mod == SCRIVI)
    {
        if(write(file, buffer, ndati) != ndati)
            return -3;
    }
    else if(mod == LEGGI)
    {
        if(read(file, buffer, ndati) != ndati)
            return -3;
    }
    else
        return -4;
  
    close(file);

    return 0;
}
