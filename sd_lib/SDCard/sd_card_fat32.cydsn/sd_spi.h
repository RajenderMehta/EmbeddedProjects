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

#define SD_OK       (0)
#define SD_ERROR    (-1)
#define SD_TIMEOUT  (-2)

//Private functions.
static uint8 sdSpiByte(uint8 data);
static uint8 sdReadResp(uint8 * buffer, int length);
static void sdReadResp_nBytes(uint8 * buff, uint32 nBytes);
static uint8 sdCrc7(uint8* chr,uint8 cnt,uint8 crc);
static void sdSendCommand(uint8 cmd, uint32 param);
static void sdCommandAndResponse(uint8 cmd, uint32 param);

//Global functions.
uint32 SD_Sector_Read(void * Read_buffer, uint32  sec_num);
uint32 SD_Sector_Write(void * Write_buffer ,uint32  sec_num);
int SD_init();
/* [] END OF FILE */
