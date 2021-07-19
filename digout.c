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
		
		int numRegisters;				//  Total number of registers enabled to scan fr
		int ChanMode[8];				//  Per-channel mode, this gives the channel setting or mode e.g.ADC this is the resolution setting for Digin this the channel mode 
		int regAddress[MAX_DATAPOINTS]; //  addess minus the 40000 multiier, total  max registers per device              	
		float value[MAX_DATAPOINTS];	// 	decoded (and then scaled) value for the register	
		
		
		
*/	

			

void displayDigOutValues(int deviceId, int displayType)
{
	int regId;
	const char *chMode[4];
				chMode[0] = "Level";
				chMode[1] = "Level";
				chMode[2] = "Pulse Freq";
				chMode[3] = "Pulse Count";


	// initialise these to zero or else we'll get nonsense readings shown if the channel/register 
	// is not enabled in the config.
	// You could initialise this to NaN or some other recognisable value to indicate "No reading available" 
	int chanLvl[9]={0};      // Values from index position 1 onwards
    int chanFreq[9]={0};
    int chanPulseCnt[9]={0};
	float pulseFreqTemp=0;
    

	for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
	{	
		// Deals with channel 1 value registers
		if ( dataSource[deviceId].regAddress[regId] == 1  ) { chanLvl[1]      =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 10 ) { chanFreq[1]     =dataSource[deviceId].value[regId]; }    // Pulse Frequency 
		if ( dataSource[deviceId].regAddress[regId] == 11 ) { chanPulseCnt[1] =dataSource[deviceId].value[regId]; }    // Pulse Counter 
		
		// Deals with channel 2 value registers
		if ( dataSource[deviceId].regAddress[regId] == 2  ) { chanLvl[2]       =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 12 ) { chanFreq[2]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 13 ) { chanPulseCnt[2]  =dataSource[deviceId].value[regId]; }    
		
		// Deals with channel 3 value registers
		if ( dataSource[deviceId].regAddress[regId] == 3  ) { chanLvl[3]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 14 ) { chanFreq[3]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 15 ) { chanPulseCnt[3] =dataSource[deviceId].value[regId]; }    

		// Deals with channel 4 value registers
		if ( dataSource[deviceId].regAddress[regId] == 4  ) { chanLvl[4]       =dataSource[deviceId].value[regId]; }   
		if ( dataSource[deviceId].regAddress[regId] == 16 ) { chanFreq[4]      =dataSource[deviceId].value[regId]; }   
		if ( dataSource[deviceId].regAddress[regId] == 17 ) { chanPulseCnt[4]  =dataSource[deviceId].value[regId]; }   
		
		// Deals with channel 5 value registers
		if ( dataSource[deviceId].regAddress[regId] == 5  ) { chanLvl[5]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 18 ) { chanFreq[5]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 19 ) { chanPulseCnt[5] =dataSource[deviceId].value[regId]; }    

		// Deals with channel 6 value registers
		if ( dataSource[deviceId].regAddress[regId] == 6  ) { chanLvl[6]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 20 ) { chanFreq[6]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 21 ) { chanPulseCnt[6] =dataSource[deviceId].value[regId]; }    

		// Deals with channel 7 value registers
		if ( dataSource[deviceId].regAddress[regId] == 7  ) { chanLvl[7]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 22 ) { chanFreq[7]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 23 ) { chanPulseCnt[7] =dataSource[deviceId].value[regId]; }    

		// Deals with channel 8 value registers
		if ( dataSource[deviceId].regAddress[regId] == 8  ) { chanLvl[8]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 24 ) { chanFreq[8]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 25 ) { chanPulseCnt[8] =dataSource[deviceId].value[regId]; }    
	} 
	
	
	
	// present the output in the format desired by the command line option
	if (displayType == HUMANREAD)
	{			
		printf("_____| DO8 Modbus Address %i |______________________________________________________________________\n", dataSource[deviceId].modbusId);
		printf("Ch\tMode\t\tLevel\t\tPulse Freq\tPulse Count\n");
        
        // see https://eecs.wsu.edu/~cs150/reading/printf.htm for futher information on printf formating 


        for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{		
            printf("%i\t%-12s\t",chanNo, chMode[ dataSource[deviceId].ChanMode[chanNo] ]);

            if (dataSource[deviceId].ChanMode[chanNo]  < 2 )      // Level 
			{
                printf("%-16i%-16s%-16s\n",chanLvl[chanNo],"-","-");
			}
            else if (dataSource[deviceId].ChanMode[chanNo] == 2 )  // Pulse Output
			{
				if (chanFreq[chanNo] == 0)
					pulseFreqTemp = 0;
				else
					pulseFreqTemp=((1.0/chanFreq[chanNo])*1000);

                printf("%-16s%-16f%-16s\n","-",pulseFreqTemp,"-") ;
			}
			else if (dataSource[deviceId].ChanMode[chanNo] == 3 )  // Pulse Output Fixed Num of Pulses
			{
				if (chanFreq[chanNo] == 0)
					pulseFreqTemp = 0;
				else
					pulseFreqTemp=((1.0/chanFreq[chanNo])*1000);

				printf("%-16s%-16f%-16i\n","-",pulseFreqTemp,chanPulseCnt[chanNo]);
			}
        }

        printf("\n\n");       
	}	



	if (displayType == JSONREAD)
	{				
		printf ("      \"name\":\"RTU-DO8\",\n");
		printf ("      \"type\": %i,\n",dataSource[deviceId].deviceType);
		printf ("      \"deviceId\":\"%i\",\n",deviceId);
		printf ("      \"modbusId\":\"%i\",\n",dataSource[deviceId].modbusId);	        
		printf ("      \"channels\": 8,\n");

		for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{				
			printf ("      \"channel %i\": {\n",chanNo);
			printf ("         \"mode\": %i,\n",dataSource[deviceId].ChanMode[chanNo]);
            if (dataSource[deviceId].ChanMode[chanNo]  < 2 )                 
                printf ("         \"Level\": %i\n",chanLvl[chanNo]);
            else if (dataSource[deviceId].ChanMode[chanNo]> 1 )
            {
				if (chanFreq[chanNo] == 0)
					 pulseFreqTemp = 0;
				else
					pulseFreqTemp=((1.0/chanFreq[chanNo])*1000);

			    printf ("         \"frequency\": %3.2f,\n", pulseFreqTemp);
			    printf ("         \"numPulse\": %i\n",chanPulseCnt[chanNo]);
            }

			if (chanNo <8) { printf ("      },\n"); } else  { printf ("      }\n"); }			
		}
				
	}

	if (displayType == CPUREAD)
	{	

		//deviceId,deviceType,modbusId,ChansTotal,ChanMode[1], chanLvl[1], chanFreq[1], chanPulseCnt[1]....ChanMode[8], chanLvl[8], chanFreq[8], chanPulseCnt[8]...	
		printf("%i,%i,%i,8",deviceId,dataSource[deviceId].deviceType,dataSource[deviceId].modbusId);
        
        for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{				
		        printf (",%i,", dataSource[deviceId].ChanMode[chanNo]);
                printf ("%i,%3.2f,%i", (int)chanLvl[chanNo], ((1.0/chanFreq[chanNo])*1000), (int)chanPulseCnt[chanNo]);
                
		}
        printf(";\n");

	}
}



// Read back the channel config from the RTU device, in this case it's the digital ouptut mode
// this is custom for each rtu module so let's keep it in the module specific include even though it's modbus related
int getChanConfig(modbus_t *mb, int deviceId)
{
	// Defines storage for returned registers from modbus read, *must* equal or exceed maximum number of registers requested.
	uint16_t mbdata_UI16[30]; 

	int rc;	

	// Get RTU-DO8 specific channel config registers 40026=40033
	rc = modbus_read_registers(mb, 25, 8, mbdata_UI16);		
	if (rc == -1)
	{
		printf("Modbus request Fail : Device Address [%i] Start Address [25] For [8] Registers \n",deviceId);
		modbus_close(mb);
		modbus_free(mb);
		exit(1);
	}	

	dataSource[deviceId].ChanMode[1] = mbdata_UI16[0];
	dataSource[deviceId].ChanMode[2] = mbdata_UI16[1];
	dataSource[deviceId].ChanMode[3] = mbdata_UI16[2];
	dataSource[deviceId].ChanMode[4] = mbdata_UI16[3];
	dataSource[deviceId].ChanMode[5] = mbdata_UI16[4];
	dataSource[deviceId].ChanMode[6] = mbdata_UI16[5];
	dataSource[deviceId].ChanMode[7] = mbdata_UI16[6];
	dataSource[deviceId].ChanMode[8] = mbdata_UI16[7];

	// Change mode = 0 to mode = 1 so we can do cross checking later 
	if ( dataSource[deviceId].ChanMode[1] == 0 ) {dataSource[deviceId].ChanMode[1]++;}
	if ( dataSource[deviceId].ChanMode[2] == 0 ) {dataSource[deviceId].ChanMode[2]++;}
	if ( dataSource[deviceId].ChanMode[3] == 0 ) {dataSource[deviceId].ChanMode[3]++;}
	if ( dataSource[deviceId].ChanMode[4] == 0 ) {dataSource[deviceId].ChanMode[4]++;}
	if ( dataSource[deviceId].ChanMode[5] == 0 ) {dataSource[deviceId].ChanMode[5]++;}
	if ( dataSource[deviceId].ChanMode[6] == 0 ) {dataSource[deviceId].ChanMode[6]++;}
	if ( dataSource[deviceId].ChanMode[7] == 0 ) {dataSource[deviceId].ChanMode[7]++;}
	if ( dataSource[deviceId].ChanMode[8] == 0 ) {dataSource[deviceId].ChanMode[8]++;}

	return 0;
}



// Uses modbus_write_registers (FC16) to write single config registers 
// this is custom for each rtu module so let's keep it in the module specific include even though it's modbus related
int reconfigureRTU(int deviceId, int modbusBaudSetting,  int chanModeSetting[])
{  

	int rc;	
	int regId;

	const char *chMode[4];
				chMode[0] = "Static Level";
				chMode[1] = "Static Level";
				chMode[2] = "Pulse Frequency Modulated Output (Free Running)";
				chMode[3] = "Pulse Frequency Modulated Output (Fixed Number of Pulses)";

	const char *adcBaud[6];
				adcBaud[0] = "19200";
				adcBaud[1] = "9600";
				adcBaud[2] = "14400";
				adcBaud[3] = "19200";
				adcBaud[4] = "38400";
				adcBaud[5] = "57600";



	uint16_t tableRegisters[1]; // 1 element array for use with modbus write command 

	// modbus device handle
	modbus_t *mb;  
	
	// Defines storage for returned registers from modbus read, *must* equal or exceed maximum number of registers requested, ask me how I know...
	uint16_t mbdata_UI16[30]; 


	

	printf("Processing Config Changes...\n");	

	mb = modbus_new_rtu( dataSource[deviceId].interface, 
					 	 dataSource[deviceId].baudRate,
						 dataSource[deviceId].parity[0],
						 dataSource[deviceId].dataBits,
						 dataSource[deviceId].stopBit);
						
	modbus_set_slave(mb, dataSource[deviceId].modbusId);


	// Set per-byte and total timeouts, this format has changed from the older libmodbus version.		
	// This could be useful if we've a latent RF-Link 
	// TODO : Don't hard code this, allow it to be configurable
	modbus_set_response_timeout(mb, 5, (5*1000000));
	modbus_set_byte_timeout(mb,5,(5*1000000));

	
	// Enable/Disable Modbus debug
	modbus_set_debug(mb, FALSE);

	// check we can connect (not sure if this is relevant on serial modbus)
	if(modbus_connect(mb) == -1)
	{
		printf("Connect Failed to Modbus ID [%i] on [%s]\n", dataSource[deviceId].modbusId, 
															 dataSource[deviceId].interface);
		modbus_close(mb);
		modbus_free(mb);
		return -1;
	}

	// Due to the way modbus registers start at 1 and not 0, 24 = register address 25
	for (int i=1 ; i<9 ; i++)
	{
		 
		if (chanModeSetting[i] >0)  
		{  
			printf("Changing DO Chan %i mode to : %s\n",i,chMode[chanModeSetting[i]]);
			tableRegisters[0]=chanModeSetting[i];
			rc = modbus_write_registers(mb, (24+i) ,  1, tableRegisters);
			if (rc == -1)
			{
				printf("Modbus request Fail : Device Address [%i] Start Address [%i] For [1] Registers \n",deviceId,(63+i) );
				modbus_close(mb);
				modbus_free(mb);
				exit(1);
			}				
		}
	}

	
	if (modbusBaudSetting>0)	
	{	
		printf("Changing RTU Baud Rate to %s...\n",adcBaud[modbusBaudSetting]);		
		tableRegisters[0]=modbusBaudSetting;
		rc = modbus_write_registers(mb, 33,  1, tableRegisters);
		if (rc == -1)
		{
			printf("Modbus request Fail : Device Address [%i] Start Address [73] For [1] Registers \n",deviceId);
			modbus_close(mb);
			modbus_free(mb);
			exit(1);
		}	

	}

    
	printf("Writing Config Register...\n");	
	tableRegisters[0]=255;
	rc = modbus_write_registers(mb, 34,  1, tableRegisters);

	if (rc == -1)
	{
		printf("Modbus request Fail : Device Address [%i] Start Address [74] For [1] Registers \n",deviceId);
		modbus_close(mb);
		modbus_free(mb);
		exit(1);
	}	

	exit(0);

}


// This is for RTU modules which have output capability only
// this is custom for each rtu module so let's keep it in the module specific include even though it's modbus related
int setModbusValues(int targetChan, int chanLogicLevel, int chanFreq, int chanPulses, int modeSwitch)
{  


	int wRegId;
	int wStartRegId;
	int wStartReg;
	int wEndReg;
	int requestedRegisters;
	int requestFull = 0;
	int rc;	
	int regId;
	int deviceId=1; // There's only one device in the demo code

	// modbus device handle
	modbus_t *mb;  
	
	// Defines storage for returned registers from modbus read, *must* equal or exceed maximum number of registers requested, ask me how I know...
	uint16_t mbdata_UI16[30]; 

	// 1 element array for use with modbus write command 
	uint16_t tableRegisters[1]; 

     
	mb = modbus_new_rtu(dataSource[deviceId].interface, 
						dataSource[deviceId].baudRate,
						dataSource[deviceId].parity[0],
						dataSource[deviceId].dataBits,
						dataSource[deviceId].stopBit);
						
	modbus_set_slave(mb, dataSource[deviceId].modbusId);


	// Set per-byte and total timeouts, this format has changed from the older libmodbus version.		
	// This could be useful if we've a latent RF-Link 
	// TODO : Don't hard code this, allow it to be configurable
	modbus_set_response_timeout(mb, 5, (5*1000000));
	modbus_set_byte_timeout(mb,5,(5*1000000));

	
	// Enable/Disable Modbus debug
	modbus_set_debug(mb, FALSE);

	// check we can connect (not sure if this is relevant on serial modbus)
	if(modbus_connect(mb) == -1)
	{
			printf("Connect Failed to Modbus ID [%i] on [%s]\n", dataSource[deviceId].modbusId, 
																	dataSource[deviceId].interface);
			modbus_close(mb);
			modbus_free(mb);
			return -1;
	}

	// Get RTU Specific channel config by making a read from the RTU module ahead of the main request 
	// Defined in digout.c
	getChanConfig(mb,deviceId);
		
	// Let's cross check that we're trying to apply a setting for a mode we're in
	if (dataSource[deviceId].ChanMode[targetChan] == modeSwitch)
	{
		switch (modeSwitch)
		{
			case 1:  // static level writes
				tableRegisters[0]=chanLogicLevel;
				rc = modbus_write_registers(mb, dataSource[deviceId].regAddress[(targetChan-1)] ,  1, tableRegisters);
				if (rc == -1)
				{
					printf("Modbus request Fail : Device Address [%i] Start Address [72] For [1] Registers \n",deviceId),(0+(targetChan-1));
					modbus_close(mb);
					modbus_free(mb);
					exit(1);
				}			
				break;
			case 2:  // Pulse frequency (Free running)
				tableRegisters[0]=chanFreq;
				rc = modbus_write_registers(mb, ( 7+(targetChan*2) ),  1, tableRegisters);
				if (rc == -1)
				{
					printf("Modbus request Fail : Device Address [%i] Start Address [72] For [1] Registers \n",deviceId),(0+(targetChan-1));
					modbus_close(mb);
					modbus_free(mb);
					exit(1);
				}			
				break;
			case 3: // Fixed pulse ouput 

				// First write number of pulses required
				tableRegisters[0]=chanPulses;
				rc = modbus_write_registers(mb, ( 8+(targetChan*2) ),  1, tableRegisters);
				if (rc == -1)
				{
					printf("Modbus request Fail : Device Address [%i] Start Address [72] For [1] Registers \n",deviceId),(0+(targetChan-1));
					modbus_close(mb);
					modbus_free(mb);
					exit(1);
				}			

				// Then write the frequency 
				tableRegisters[0]=chanFreq;
				rc = modbus_write_registers(mb, ( 7+(targetChan*2) ),  1, tableRegisters);
				if (rc == -1)
				{
					printf("Modbus request Fail : Device Address [%i] Start Address [72] For [1] Registers \n",deviceId),(0+(targetChan-1));
					modbus_close(mb);
					modbus_free(mb);
					exit(1);
				}			
				break;
		}
	}
	else
	{
		printf("Illigal setting for channel %i\n",targetChan);
		modbus_close(mb);
		modbus_free(mb);
		exit(1);

	}

	
	modbus_close(mb);
	modbus_free(mb);

	return 0;
}