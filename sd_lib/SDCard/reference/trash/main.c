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
	FAT_INFO * fat_info;
	FILE_ENTRY * file_info;
	uint32 file_data_sector;

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
	
	assert(p_bpb->BPB_BytsPerSec == 512);
	assert(p_bpb->BPB_NumFATs == 2);

	fat_info = (FAT_INFO *) malloc(sizeof(FAT_INFO));

	fat_info->fat_begin = p_bpb->BPB_RsvdSecCnt + p_bpb->BPB_RootEntCnt; 
	fat_info->cluster_begin = fat_info->fat_begin + (p_bpb->BPB_NumFATs * p_bpb->BPB_FATSz32 ); 
	fat_info->root_cluster = p_bpb->BPB_RootClus;
	fat_info->sectors_per_clusters = p_bpb->BPB_SecPerClus;

	SD_Sector_Read(Read_buffer_1, fat_info->cluster_begin);

	assert(sizeof(FILE_ENTRY)==32);

	file_info = (void *)Read_buffer_1;

	//temp file code.
	while (file_info->cluster_low != 0x5) {
		file_info++;
	}
	
	//Get file data now.
	file_data_sector = fat_info->cluster_begin + ((file_info->cluster_low) - (fat_info->root_cluster))*(fat_info->sectors_per_clusters);

	SD_Sector_Read(Read_buffer_1, file_data_sector);

	while(1);
}

int main() {
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
