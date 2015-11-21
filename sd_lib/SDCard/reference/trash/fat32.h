#ifndef _FAT32_H_
#define _FAT32_H_

#include "project.h"

typedef struct fat_info {
	uint32 fat_begin;
	uint32 cluster_begin;
	uint32 sectors_per_clusters;
	uint32 root_cluster;
} FAT_INFO;

#pragma pack(1)			//__packed for ARMCC.
typedef struct bpb {
	char BS_jmpBoot[3];
	char BS_OEMName[8];
	uint16 BPB_BytsPerSec;
	uint8 BPB_SecPerClus;
	uint16 BPB_RsvdSecCnt;
	uint8 BPB_NumFATs;
	uint16 BPB_RootEntCnt;
	uint16 BPB_TotSec16;
	uint8 BPB_Media;
	uint16 BPB_FATSz16;
	uint16 BPB_SecPerTrk;
	uint16 BPB_NumHeads;
	uint32 BPB_HiddSec;
	uint32 BPB_TotSec32;
	uint32 BPB_FATSz32;
	uint16 BPB_ExtFlags;
	uint16 BPB_FSVer;
	uint32 BPB_RootClus;
	uint16 BPB_FSInfo;
	uint16 BPB_BkBootSec;
	char BPB_Reserved[12];
	uint8 BS_DrvNum;
	char BS_Reserved1[1];
	char BS_BootSig[1];
	uint32 BS_VolID;
	char BS_VolLab[11];
	char BS_FilSysType[8];
}BPB;

typedef struct file_info{
	char short_file_name[11];
	uint8 att;
	char reserved[8];
	uint16 cluster_high;
	uint32 reserved_1;
	uint16 cluster_low;
	uint32 file_size;
}FILE_ENTRY;

typedef struct partion_boot_sector{
	char bpb[sizeof(BPB)];
	char bootstrape_code[420];
	char end_of_sector[2];	
}PARTION_BOOT_SECTOR;

#endif
