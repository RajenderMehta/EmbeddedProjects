/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "sd_spi.h"

char send[6]; 
char resp[20];

//Private functions.
static char sdSpiByte(char data){
     SPIM_WriteTxData(data);
     //while(!(ssp1stat & (1<<BF)));
     return SPIM_ReadRxData();
} 
static uint8 sdReadResp(char * buffer, int length){ 
    char v;
	int i = 0; 
	int j = 0;
	
	do {                 
          v = sdSpiByte(0xFF); 
    } while(v == 0xFF);      

	buffer[i] = v;
	
    do {
		if(i>length) 
			return -1;
		
		buffer[++i] = v = sdSpiByte(0xFF); 
    } while((v != 0xFF));      
     
	return i;
}
static void sdReadResp_nBytes(char * buff, uint32 nBytes){ 
    char v;
	int i = 0;
	int j = 0;
	
	do {                 
          v = sdSpiByte(0xFF); 
    } while(v != 0xFE);
	
    while(i < nBytes) {                 
          buff[i++] = v = sdSpiByte(0xFF); 
    } 
}

static void sdWrite_Sector(char * buff, uint32 nBytes){ 
    char v;
	int i = 0;
	int j = 0;
	
	v = sdSpiByte(0xFE);
	
    do {                 
          v = sdSpiByte(buff[i++]); 
    } while(i <= nBytes);
	
	//Closing the command.
	sdSendCommand(0xFF, 0x0);
	
	do {
		v = sdSpiByte(0xFF);
	} while(v!=0xFF);
	
}

static char sdCrc7(char* chr,char cnt,char crc){ 
     char i, a; 
     char Data; 

     for(a = 0; a < cnt; a++){           
          Data = chr[a];           
          for(i = 0; i < 8; i++){                
               crc <<= 1; 
               if( (Data & 0x80) ^ (crc & 0x80) ) {crc ^= 0x09;}                
               Data <<= 1; 
          } 
     }      
     return crc & 0x7F; 
} 
static void sdSendCommand(char cmd, uint32 param){      
     
     send[0] = cmd | 0x40; 
     send[1] = param >> 24; 
     send[2] = param >> 16; 
     send[3] = param >> 8; 
     send[4] = param; 
     send[5] = (sdCrc7(send, 5, 0) << 1) | 1; 
      
     for(cmd = 0; cmd < sizeof(send); cmd++){ 
          send[cmd] = sdSpiByte(send[cmd]); 
     } 
} 
static void sdCommandAndResponse(char cmd, uint32 param){   
     char ret;          
     ret = sdSpiByte(0xFF); 
     sdSendCommand(cmd, param); 
     sdReadResp(resp, len(resp));     
     return;
}

//Global functions.
int SD_init() {
    char i = 0;
	int res = -1;
       
	//Pin_1_Write(1);
	
	for(i=0; i < 2; i++) // idle for 1 bytes / 80 clocks
		sdSendCommand(0xFF, 0x0);
		
	//Pin_1_Write(0);
	
	// CMD_0
	res = 100;
	do {
		sdSendCommand(0x0, 0x0);
		i = sdSpiByte(0xff);
		res--;
	} while((i != 1) & (res != 0));
	
	if(res == 0)
		return -1;	//Failure.
	
	res = 100;
	do {
		sdSendCommand(8, 0x1AA);
		i = sdSpiByte(0xff);
		res--;
	} while((i != 1) & (res != 0));
	
	if(res == 0)
		return -1;	//Failure.
     
	
	// Optional: CMD8 - Just validating the legal command for card type.
	//sdCommandAndResponse(8, 0x000001AA);
	
	// Card Init. Series of CMD_55 and CMD_41
	do {	
		sdCommandAndResponse(55, 0x0);
    	sdCommandAndResponse(41, 0x40000000);
	} while(resp[0] != 0);

	// Optional: CMD_58 - Check voltage compatiblity.
 	sdCommandAndResponse(58, 0);
	
	// Optional: CMD_16 - Set block length.
	sdCommandAndResponse(16, 512);
	
	// Optional: CMD_10 - Read CID.
	sdCommandAndResponse(10, 0);
	sdReadResp_nBytes(resp, 20);
	
	//Success.
	return 0;
}

uint32 SD_Sector_Read(void * Read_buffer ,uint32  sec_num) {
	// CMD_17 - Dump the sector.
	sdCommandAndResponse(17, sec_num << 9);
	sdReadResp_nBytes(Read_buffer, 512);    
}

uint32 SD_Sector_Write(void * Write_buffer ,uint32  sec_num) {
	//CMD_24 - Write single sector
	sdCommandAndResponse(24, sec_num << 9);
	sdWrite_Sector(Write_buffer, 512);
}

/* [] END OF FILE */
