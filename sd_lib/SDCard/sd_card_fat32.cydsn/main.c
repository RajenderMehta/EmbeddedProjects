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
#include <project.h>
#include "pff.h"
#include "sd_spi.h"
#include "assert.h"

//#include <stdio.h>

char Read_buffer_1[0x200], Read_buffer_2[0x200];
	
void sys_init() {
	int status = 0;
	//Set SD card clock to 10 KHz.
	Clock_1_SetDivider(39);			//Source clock 400KHz. Divider setting 39 (+ 1)
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPIM_Start();
	status = SD_init();
	
	//Not able to init SD card.
	//assert(status == 0);
	
	//Boost the SD card clocks to 100 KHz.
	Clock_1_SetDivider(3);			//Source clock 400KHz. Divider setting 3 (+ 1).
}

void SD_test() {
	int j = 0;
	volatile int pass = 0, fail = 0;

	sys_init();
	
	//initiate data pattern.
	for (j =0; j < 0x200; j++) {
		Read_buffer_1[j] = (char)j;
	}
	
	for (j =0; j < 100; j++) {
		SD_Sector_Write(Read_buffer_1, j);
		SD_Sector_Read(Read_buffer_2, j);
		
		if (0 == memcmp(Read_buffer_1, Read_buffer_2, 0x200))
			pass++;
		else 
			fail++;
	}
		
	while(1);
}
   
int main()
{
	FATFS fs;
	UINT br;
    char rd_buff[0x1e] = {0};

	//Global interrupt enable.
	/*CyGlobalIntEnable;*/
	
	SD_test();
	
    /* Open a text file and type it */
	if (pf_mount(&fs) == FR_OK &&
		pf_open("HELLO.TXT") == FR_OK) {
    		pf_read(rd_buff, 0x1e, &br);	/* Direct output to the console */
	}

	for (;;) ;
}

/* [] END OF FILE */
