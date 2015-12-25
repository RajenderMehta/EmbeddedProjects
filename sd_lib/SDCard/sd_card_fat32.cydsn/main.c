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
FATFS fs;

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
   int sendchar(c) {
	UART_UartPutChar(c);
}

int getkey() {
	UART_UartGetChar();
}

void f_print(const char * f_name) {
	uint32 br;
	uint32 temp; 
    char rd_buff[0x100] = {0};
	
	if (pf_mount(&fs) == FR_OK &&
		pf_open(f_name) == FR_OK) {
		
		temp = sizeof(rd_buff);
					
		while(FR_OK == pf_read(rd_buff, sizeof(rd_buff), &br)) {
			
			if (br < temp) {	//hit end of file.
				rd_buff[br] = 0;	//get only read data.
				printf("%s",rd_buff);	
				break;
			}
			else 
				printf("%s",rd_buff);
		}
	}
}

int main()
{
	uint32 br, bw;
	uint32 temp;
	char * f_name = "HELLO.TXT";
	
	//Global interrupt enable.
	/*CyGlobalIntEnable;*/
	UART_Start();
		
	//SD_test();
	printf("Hello World\r\n");

    /* Open a text file and type it */
	f_print(f_name);
	
	//Put data in file.
	if (pf_open(f_name) == FR_OK) {			
			pf_write("Hello World Hello World Hello World Hello World", 50, &bw);		
	}

	for (;;) ;
}

/* [] END OF FILE */
