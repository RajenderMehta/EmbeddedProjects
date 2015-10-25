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
#include "sd_spi.h"
#include "assert.h"

char Read_buffer_1[0x200], Read_buffer_2[0x200];
	
void sys_init() {
	int status = 0;
	//Set SD card clock to 10 MHz.
	Clock_1_SetDivider(39);			//Source clock 400KHz. Divider setting 39 (+ 1)
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPIM_Start();
	status = SD_init();
	
	//Not able to init SD card.
	assert(status == 0);
	
	//Boost the SD card clocks to 100 MHz.
	Clock_1_SetDivider(3);			//Source clock 400KHz. Divider setting 3 (+ 1).
}

void SD_test() {
	int j = 0;
	volatile int pass = 0, fail = 0;
	uint32 root_dir_sector;
	PARTION_BOOT_SECTOR * p_pbs;
	BPB * p_bpb;
	Fat16Entry * p_fe;
/*
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
*/
	SD_Sector_Read(Read_buffer_1, 0);
	
	p_pbs = (void *)Read_buffer_1;
	p_bpb = p_pbs->bpb;
	
	root_dir_sector = *(uint16 *)p_bpb->reserved_sectors + (*(uint16 *)(p_bpb->sectors_per_fat)) * (*(uint16 *)(p_bpb->n_fats));
	
	SD_Sector_Read(Read_buffer_1, root_dir_sector);
	
	p_fe = Read_buffer_1;
	
	//file listing.
	while(strcmp((char *)(p_fe->filename), "") != 0) {
		p_fe++;
	}
	
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
