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
#include "project.h"
#include "sd_spi.h"
#include "assert.h"

char Read_buffer_1[0x200], Read_buffer_2[0x200];

void SD_test() {
	int j = 0;
	volatile int pass = 0, fail = 0;
	uint32 root_dir_sector;
	PARTION_BOOT_SECTOR * p_pbs;
	BPB * p_bpb;
	Fat16Entry * p_fe;

	//initiate data pattern.
	for (j =0; j < 0x200; j++) {
		Read_buffer_1[j] = (char)j;
	}
	/*
	for (j =0; j < 100; j++) {
		SD_Sector_Write(Read_buffer_1, j);
		SD_Sector_Read(Read_buffer_2, j);
		
		if (0 == memcmp(Read_buffer_1, Read_buffer_2, 0x200))
			pass++;
		else 
			fail++;
	}
	*/
	SD_Sector_Read(Read_buffer_1, 0);
	
	p_pbs = (PARTION_BOOT_SECTOR *)Read_buffer_1;
	p_bpb = (BPB*)(p_pbs->bpb);
	
	while(1);
}

int main()
{	
	//Global interrupt enable.
	/*CyGlobalIntEnable;*/
	sys_init();
	
	//Testing sd card init. Will corrupt the file system. 
	SD_test();
			
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
