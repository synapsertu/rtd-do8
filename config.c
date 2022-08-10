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
*/
int readConfig()
{	
	int deviceId=1; // there's only one device configured in this tool
	int regId;
    
	//***************************************************************
	//********************** CONFIG *********************************
	//***************************************************************
	
	config.dsTotal=1; // there's only one device configured in this tool	

	//***************************************************************
	//********************** DATA SOURCES ***************************
	//***************************************************************	

   	dataSource[deviceId].deviceType  = RTU_DO8;

    // These values will be overwrtten by cmd line options
	dataSource[deviceId].modbusId = 1;
	dataSource[deviceId].baudRate = 19200;
	dataSource[deviceId].dataBits = 8;		
	dataSource[deviceId].stopBit  = 1;
	dataSource[deviceId].timeout  = 5;
	strcpy(dataSource[deviceId].parity,"None");
	strcpy(dataSource[deviceId].interface, "/dev/ttyUSB0");
	
		
	// this MUST equal the total number of registered configured 
	dataSource[deviceId].numRegisters=8;


	//***************************************************************
	//********************** DATA POINTS ****************************
	//***************************************************************
	
	dataSource[deviceId].regAddress[1]  =1  ;	dataSource[deviceId].regType[1]	 =1  ;		// Channel 1 Logic Level Reading  
	dataSource[deviceId].regAddress[2]  =2  ;	dataSource[deviceId].regType[2]	 =1  ;		// Channel 2 Logic Level Reading  
	dataSource[deviceId].regAddress[3]  =3  ;	dataSource[deviceId].regType[3]	 =1  ;		// Channel 3 Logic Level Reading  
	dataSource[deviceId].regAddress[4]  =4  ;	dataSource[deviceId].regType[4]	 =1  ;		// Channel 4 Logic Level Reading  
	dataSource[deviceId].regAddress[5]  =5  ;	dataSource[deviceId].regType[5]	 =1  ;		// Channel 5 Logic Level Reading  
	dataSource[deviceId].regAddress[6]  =6  ;	dataSource[deviceId].regType[6]	 =1  ;		// Channel 6 Logic Level Reading  
	dataSource[deviceId].regAddress[7]  =7  ;	dataSource[deviceId].regType[7]	 =1  ;		// Channel 7 Logic Level Reading  
	dataSource[deviceId].regAddress[8]  =8  ;	dataSource[deviceId].regType[8]	 =1  ;		// Channel 8 Logic Level Reading  

}

void printConfig()
{
	int deviceId;
	int regId;
	
	printf("--------- Config Imported ----------\n\n");

	// i = device  n = register
   for(deviceId=1 ; deviceId<(config.dsTotal+1) ; deviceId++)
   {	
	
		printf("dataSource [%i] deviceType  = [%i]  \n", deviceId, dataSource[deviceId].deviceType);
		printf("dataSource [%i] modbusId    = [%i]  \n", deviceId, dataSource[deviceId].modbusId);
		printf("dataSource [%i] interface   = [%s]  \n", deviceId, dataSource[deviceId].interface);
		printf("dataSource [%i] baudRate    = [%i]  \n", deviceId, dataSource[deviceId].baudRate);
		printf("dataSource [%i] dataBits    = [%i]  \n", deviceId, dataSource[deviceId].dataBits);
		printf("dataSource [%i] parity      = [%s]  \n", deviceId, dataSource[deviceId].parity);	
		printf("dataSource [%i] stopBit     = [%i]  \n", deviceId, dataSource[deviceId].stopBit);
		printf("dataSource [%i] timeout     = [%i]  \n", deviceId, dataSource[deviceId].timeout);
		printf("dataSource [%i] DataPoints  = [%i] \n",  deviceId, dataSource[deviceId].numRegisters);
		
		
		for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
		{	
			printf("[%i]\tregAddress  = [%i]  regType     = [%i]    ",regId, dataSource[deviceId].regAddress[regId],dataSource[deviceId].regType[regId]);
			printf("\n");
		}
		
	}
	printf("\n");
	printf("------------------------------------\n");
	printf("\n");
	
}