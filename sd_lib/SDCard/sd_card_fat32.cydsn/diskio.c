/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sd_spi.h"
#include "pffconf.h"

extern char Read_buffer_1[0x200];
/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	DSTATUS stat;

    //Set SD card clock to 10 KHz. 
    Clock_1_SetDivider(39); 
    
    SPIM_Start();
	
    /* If Initialization Succeeded */
    if( !SD_init())
    {
        /* clear the STA_NOINIT err flag */
        stat &= ~STA_NOINIT;
        
        //Not able to init SD card.
        //	assert(status == 0);
    }
    
    //Boost the SD card clocks to 100 KHz.
    Clock_1_SetDivider(3);
    
    /* return current status */
	return stat;
}

/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* buff,		/* Pointer to the destination object */
	DWORD sector,	/* Sector number (LBA) */
	UINT offset,	/* Offset in the sector */
	UINT count		/* Byte count (bit15:destination) */
)
{
    volatile static DWORD sec_n = -1;
    
    if(sec_n != sector) {
        SD_Sector_Read(Read_buffer_1, sector);
        sec_n = sector;
    }
    
    memcpy(buff, Read_buffer_1+offset, count);
    return RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Write partial sector                                                  */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_writep (
	const BYTE *buff,	/* Pointer to the bytes to be written (NULL:Initiate/Finalize sector write) */
	DWORD sc			/* Number of bytes to send, Sector number (LBA) or zero */
)
{
	DRESULT res;
	volatile static uint32 sec_n;

	if (buff) {		/* Send data bytes */
		SD_Sector_Read(Read_buffer_1, sec_n);
		memcpy(Read_buffer_1, (void *)buff, sc);
		SD_Sector_Write(Read_buffer_1, sec_n);		
		res = RES_OK;
	}
	else {
		if (sc) {	/* Initiate sector write process */
			sec_n = sc;	
			res = RES_OK;
		}
		else {	/* Finalize sector write process */

		}
	}

	return res;
}
#endif
