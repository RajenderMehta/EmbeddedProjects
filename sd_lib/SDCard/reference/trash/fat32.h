#ifndef _FAT32_H_
#define _FAT32_H_

#include "project.h"

typedef struct fat_info {
	uint32 fat_begin;
	uint32 cluster_begin;
	uint32 sectors_per_clusters;
	uint32 root_cluster;
} FAT_INFO;

typedef struct bpb {
	char jmp_instr[3];
	char oem_name[8];
	char bytes_per_sector[2];
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
	char large_sector_per_fat[4];
	char ext_flags[2];
	char fs_version[2];
	char root_dir_start[4];
	char fs_info_sector[2];
	char backup_boot_sector[2];
	char reserved[12];
	char nPartitions[1];
	char unused[1];
	char exntd_sign[1];
	char partion_sr_no[4];
	char partition_name[11];
	char fat_name[8];
}BPB;

typedef struct partion_boot_sector{
	char bpb[sizeof(BPB)];
	char bootstrape_code[420];
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
} Fat16Entry;

#endif
