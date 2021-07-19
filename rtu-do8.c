/*
        The MIT License (MIT)

        Copyright (c) 2021 Andrew O'Connell

        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.

        Dependancies :

        apt-get install sqlite3 libsqlite3-dev libmodbus5 libmodbus-dev

        Compile as below or use 'make all' to allow program to use external system (.so) libraries
        gcc log.c -o log -lsqlite3 -lmodbus 


*/

// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// External Libs
#include <modbus/modbus.h> //LGPL 2.1

// Types & Variables
#include "Types.h"

// RTU Module Definitions
#include "digout.c"

// Functions
#include "config.c"
#include "modbus.c"
#include "rtudecode.c"


int main(int argc, char* argv[])
{
	
	int deviceId=1;  // there's only one device in the demo setup 
	int displayType = HUMANREAD; // default
	int opt;
	int debugMode=0;
    int configWrite=0;  
	int chanModeSetting[9]={0};
	int modbusBaudSetting=0;
	int chanLogicLevel=0;
	int targetChan=0;
	int chanFreq=0;
	int chanPulses=0;
	int modeSwitch=0; // 1 = Logic Level | 2 = Frequency Continious | 3 = Frequency Fixed Pulses
	
	// Load Config, this is 
	readConfig(); 

	// Command line options 
	//
	// For reference see : https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
	//
    // The colon after the letter tells getopt to expect an argument after the option
	// To disable the automatic error printing, put a colon as the first character     
	while((opt = getopt(argc, argv, ":hjcda:b:p:1:2:3:4:5:6:7:8:o:s:f:n:m:w")) != -1) 
    { 
        switch(opt) 
        { 
			case 'h': // Human Readable output
            	displayType = HUMANREAD;
                break; 				
            case 'j': // JSON output
				displayType = JSONREAD;
                break; 				
			case 'c': // comma seperated output
				displayType = CPUREAD;
                break;							
			case 'd': // Print Config
				debugMode=1;						
                break;							
			case 'a': // Set modbus address for read
				if (atoi(optarg) >0 && atoi(optarg) <255)
				{
					dataSource[deviceId].modbusId = atoi(optarg);				
				}
				break;
			case 'b': // Set baudrate for read			    
				if (atoi(optarg) == 9600  
				||  atoi(optarg) == 14400
				||  atoi(optarg) == 19200
				||  atoi(optarg) == 38400
				||  atoi(optarg) == 57600)
				{
					dataSource[deviceId].baudRate = atoi(optarg);
				}
				break;
			case 'p': // Set serial interface for read
				strcpy(dataSource[deviceId].interface,optarg);
				break;
			case 'w':  // Invoke write to RTU NVRAM
				displayType=HUMANREAD;
				configWrite=1;
				break;  
			case '1': // Configure RTU Channel 1 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[1] = atoi(optarg);
				}				
				break;
			case '2': // Configure RTU Channel 2 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[2] = atoi(optarg);
				}				
				break;
			case '3': // Configure RTU Channel 3 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[3] = atoi(optarg);
				}				
				break;
			case '4': // Configure RTU Channel 4 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[4] = atoi(optarg);
				}				
				break;
			case '5': // Configure RTU Channel 5 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[5] = atoi(optarg);
				}				
				break;
			case '6': // Configure RTU Channel 6 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[6] = atoi(optarg);
				}				
				break;
			case '7': // Configure RTU Channel 7 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[7] = atoi(optarg);
				}				
				break;
			case '8': // Configure RTU Channel 8 Mode setting
				if (atoi(optarg) <4 && atoi(optarg) >0)
				{
					chanModeSetting[8] = atoi(optarg);
				}				
				break;
			case 'o':
				if (atoi(optarg) <9 && atoi(optarg) >0)
				{
					targetChan=atoi(optarg);
				}								
				break;				
			case 's':	// Logic Level output mode
				if (atoi(optarg) <2)
				{					
					chanLogicLevel=atoi(optarg);
					modeSwitch=1;
				}								
				break;
			case 'f':	// Pulse frequency output mode - this sets the pulse period 
				if (atoi(optarg) <1000)
				{					
					chanFreq = atoi(optarg);
					// don't over-write -n setting of modeSwitch
					if (modeSwitch==0) { modeSwitch=2; }
				}								
				break;
			case 'n':	// Pulse frequency output mode - this sets the number of pulses to output 
					chanPulses = atoi(optarg);				
					modeSwitch=3;
				break;
			case 'm':	// Set value for RTU Baud Rate register  (use in conjunction with -w flag)
				if (atoi(optarg) <6 && atoi(optarg) >0)
				{
					modbusBaudSetting = atoi(optarg);									
				}				
				break;
            case '?': 
                printf ("Synapse RTU-DI8 Reader - v1.0\n\n");				
				printf ("%s [-h|j|c] [-a] [-b] [-p] [-o] [-s] [-f] [-n] [-1] [-2] [-3] [-4] [-5] [-6] [-7] [-8] [-m] [-w] [-d]\n\n", argv[0]);
				printf ("Syntax :\n\n");
				printf ("-h = Human readable output (default)\n");
				printf ("-j = JSON readable output\n");
				printf ("-c = Comma delimited minimal output\n");
				printf("\n");			
				printf ("-a = Set Modbus device address (1-255)  default=1 \n");
				printf ("-b = Set serial baud rate (9600/14400/19200/38400/57600)  default=19200 \n");
				printf ("-p = Set serial interface to use e.g. /dev/ttyS0  default=/dev/ttyUSB0 \n");
				printf("\n");
				printf ("-o = Output channel to set (1|2|3|4|5|6|7|8) ");
				printf("\n");
				printf ("-s = Set logic on/off state (0|1) \n");
				printf ("-f = Set period of pulse frequency output  e.g. 100 = 10Hz  or  0 = off \n");				
				printf ("-n = Select number of pulses for fixed pulse count output\n");				
				printf("\n");
				printf ("-1 = Set Channel 1 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-2 = Set Channel 2 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-3 = Set Channel 3 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-4 = Set Channel 4 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-5 = Set Channel 5 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-6 = Set Channel 6 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-7 = Set Channel 7 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf ("-8 = Set Channel 8 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level\n");
				printf("\n");
				printf ("-m = Set value for RTU Baud Rate register (1=9600/2=14400/3=19200/4=38400/5=57600)  \n");
				printf("\n");
				printf ("-w = Confirm writing configured setting registers to RTU NVRAM\n");				printf("\n");
				printf ("-d = debug mode\n");				
				printf("\n");
				printf("Examples :\n");
				printf ("Set output channel 3 to on                                                 :  %s -a 1 -b 19200 -p /dev/ttyS0 -o 3 -s 1 \n", argv[0]);
				printf ("Set output channel 3 to off                                                :  %s -a 1 -b 19200 -p /dev/ttyS0 -o 3 -s 0 \n", argv[0]);
				printf("\n");
				printf ("Set output channel 1 to pulse frequency 10Hz (free running )               :  %s -a 1 -b 19200 -p /dev/ttyS0 -o 1 -f 100 \n", argv[0]);
				printf ("Set output channel 1 to pulse frequency 0Hz (off)                          :  %s -a 1 -b 19200 -p /dev/ttyS0 -o 1 -f 0 \n", argv[0]);
				printf("\n");
				printf ("Set output channel 1 to pulse frequency 10Hz for 50 pulses only )          :  %s -a 1 -b 19200 -p /dev/ttyS0 -o 1 -f 100 -n 50 \n", argv[0]);
				printf("\n");
				printf ("Reconfigure RTU channel 1 into pulse frequency output mode                 :  %s -a 3 -p /dev/ttyS0 -1 2 -w\n", argv[0]);
				printf("\n");
				exit(1);
                break; 							
        } 
	}

	if (displayType==HUMANREAD) { printf("\nSynapse RTU-DO8 Reader - v1.0\n\n"); }
	

	// Write 
	if (configWrite ==1) 
	{ 
		reconfigureRTU(deviceId, modbusBaudSetting, chanModeSetting);
		exit(0);
	}

	if (debugMode==1) { printConfig(); }
	
	// Set ouput channel according to command line
	if (targetChan >0)
	{
		setModbusValues(targetChan,chanLogicLevel,chanFreq,chanPulses,modeSwitch); // only 1 device configured in demo tool
	}

	
	// Read in Modbus registers
	if (displayType==HUMANREAD) { printf("Modbus Reads...\n"); }
	if (getModbusValues() == 0)
	{
		if (displayType==HUMANREAD) { printf("Modbus reads OK\n\n"); }
	}
	else
	{
		printf("..Fatal Error : Error Reading Modbus device(s) \n\n");
		exit(1);
	}
	
	
	

	// Print output in desired format 
	for(deviceId=1 ; deviceId<(config.dsTotal+1) ; deviceId++)
	{	
		if (displayType==JSONREAD)
		{
			if (deviceId == 1) 
				printf("{\n   \"device 1\" : {\n");
			else 
			 	printf("   \"device %i\" : {\n",deviceId);	
		}

		displayDigOutValues(deviceId, displayType);
 		
		if (displayType==JSONREAD)
		{
			if ( deviceId<(config.dsTotal) )
				printf("   },\n");
			else 
				printf("   }\n}\n",deviceId);	
		}
	}
		

}