/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sd_spi.h"

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


#if 0
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
	DRESULT res;
	BYTE rc;
	UINT bc;
    uint8 temp = 0;

	sector *= 512;	/* Convert to byte address if needed */

	res = RES_ERROR;
//	if (send_cmd(CMD17, sector) == 0) {	/* READ_SINGLE_BLOCK */

//    if (sdSendCommand(17, (int) sector) == 0) {
       sdSendCommand(17, (int) sector);
		bc = 40000;	/* Time counter */
		do {				/* Wait for data packet */
		//	rc = rcv_spi();
            rc = sdSpiByte(0xFF);
		} while (rc != 0xFE && --bc);  // Ignore the responce( which is 0) before 0xFE

		if (rc == 0xFE) {	/* A data packet arrived */

			bc = 512 + 2 - offset - count;	/* Number of trailing bytes to skip */

			/* Skip leading bytes */
			//while (offset--) rcv_spi();

            while (offset--)
                temp = sdSpiByte(0xFF); 
            
			/* Receive a part of the sector */
			if (buff) {	/* Store data to the memory */
				do {
                    //*buff++ = rcv_spi();
        //            *buff++ = sdSpiByte(0xFF);
                                 temp = sdSpiByte(0xFF);
                                *buff++ = temp;
				} while (--count);
			}

			/* Skip trailing bytes and CRC */
			//do rcv_spi(); while (--bc);
            do sdSpiByte(0xFF); while (--bc);
            
			res = RES_OK;
		}

	//rcv_spi(); // dont know why we need this

	return res;
}

#else

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

#endif
/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/
#if 0
DRESULT disk_writep (
	const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
	DRESULT res;


	if (!buff) {
		if (sc) {

			// Initiate write process

		} else {

			// Finalize write process

		}
	} else {

		// Send data to the disk

	}

	return res;
}

#endif