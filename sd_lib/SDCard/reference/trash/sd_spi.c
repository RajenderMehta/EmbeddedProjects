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
#include <stdio.h>

const char fileName[] = "c:\\test.bin";
char send[6]; 
char resp[20];
FILE * fp;

//Global functions.
int SD_init() {
	fopen(fileName,"rb");
	return 0;
}

uint32 SD_Sector_Read(void * Read_buffer ,uint32  sec_num) {
	// CMD_17 - Dump the sector.
	fseek(fp, (sec_num * 512), SEEK_SET);
	fread(Read_buffer, 512, 1, fp);  
}

uint32 SD_Sector_Write(void * Write_buffer ,uint32  sec_num) {
	//CMD_24 - Write single sector
	fseek(fp, (sec_num * 512), SEEK_SET);
	fwrite(Write_buffer, 512, 1, fp);
}

void sys_init() {
	fp = fopen(fileName, "rb+");
	assert(fp != NULL);
}

/* [] END OF FILE */