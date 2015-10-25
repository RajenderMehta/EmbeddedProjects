Date: 25 Oct, 2015
    Created delete file batch script, and working on FAT32 drivers.
    
Date: 24 Oct, 2015

   Understanding.
        2GB - FAT16
        
        |-----------------------|
        |  Reserved Sector: 0-7 |
        |-----------------------|
        |  FAT_1: 8 - 243       |
        |-----------------------|
        |  FAT_2: 244 - 479     |
        |-----------------------|
        |  Root_dir_sector: 480 |
        |                       |
        |  0x200 entries        |
        |       of 32 bytes each|
        |-----------------------|
        |  Data Cluster 2: 512  |
        |-----------------------|
        |  Data Cluster 3: 576  |
        |-----------------------|
        |  Data Cluster 4: 640  |
        |-----------------------|
        |  ...                  |


    Verified:
        1. File listing
        2. FAT table content
        3. Lot of files in root dir
        4. large files.
        5. Diff between FAT and root dir sector
        6. Diff between file and dir.
        7. Bottom line: Able to read fat tables, directories, files and content.
        
     ToDo:
        1. Traversing the file list in SD Card.
        2. fopen to open and read the file.
        
        

Date: 17 Oct, 2015
SD Card init sequence
    1. Init freq = 10 KHz
    2. Operating freq = 100 KHz
    
    Init Sequence:
        Send cmd_0 until you get 1 (100 times)
        Send cmd_1 until you get 0 (1000 times)
     
    No pull up needed on MISO or any line.
    
    
    