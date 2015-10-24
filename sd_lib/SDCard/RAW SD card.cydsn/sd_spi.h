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
#define len(x) (sizeof(x)/sizeof(x[0]))

typedef enum status{
	PASS = 0,
	FAILURE
}STATUS;

typedef struct partion_boot_sector{
	char jmp_instr[3];
	char oem_name[8];
	char bpb[25];
	char ex_bpb[26];
	char bootstrape_code[448];
	char end_of_sector[2];	
}PARTION_BOOT_SECTOR;

typedef struct {
    unsigned char filename[8];
    unsigned char ext[3];
    unsigned char attributes;
    unsigned char reserved[10];
    unsigned short modify_time;
    unsigned short modify_date;
    unsigned short starting_cluster;
    unsigned long file_size;
} __attribute((packed)) Fat16Entry;

typedef struct bpb {
	char bytes_per_cluster[2];
	char sectors_per_cluster[1];
	char reserved_sectors[2];
	char n_fats[1];
	char root_entry[2];
	char small_sectors[2];
	char media_type[1];
	char sectors_per_fat[2];
	char sectors_per_track[2];
	char n_heads[2];
	char hidden_sectors[4];
	char large_sectors[4];
	char physical_disk_number[1];
	char current_head[1];
	char signature[1];
	char vol_sr_no[4];
	char volume_label[11];
	char sys_id[8];
}BPB;

//Private functions.
static char sdSpiByte(char data);
static uint8 sdReadResp(char * buffer, int length);
static void sdReadResp_nBytes(char * buff, uint32 nBytes);
static char sdCrc7(char* chr,char cnt,char crc);
static void sdSendCommand(char cmd, uint32 param);
static void sdCommandAndResponse(char cmd, uint32 param);

//Global functions.
uint32 SD_Sector_Read(void * Read_buffer, uint32  sec_num);
uint32 SD_Sector_Write(void * Write_buffer ,uint32  sec_num);
int SD_init();
/* [] END OF FILE */
