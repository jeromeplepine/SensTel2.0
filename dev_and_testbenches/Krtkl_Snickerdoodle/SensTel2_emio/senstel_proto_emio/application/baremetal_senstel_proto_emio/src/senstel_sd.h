/*
 * senstel_sd.h
 *
 *  Created on: May 8, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_SENSTEL_SD_H_
#define SRC_SENSTEL_SD_H_

#include "xsdps.h"		/* SD device driver */
#include "diskio.h"
#include "xil_printf.h"
#include "ff.h"
#include "xil_printf.h"
#include "senstel_sd_filesys_config.h"

//void vGetDbConfig(FATFS *fatfs);
int ulMountFs(FATFS *fatfs, FIL *file, DIR *dir);
int ulOpenFiles(FATFS *fatfs, FIL *file);
int ulDumpToFile(FIL *File);
int ulCloseFiles(xSdDb_t *FsDatabase);
//int ulUnmountFs(xSdDb_t *FsDatabase);


#endif /* SRC_SENSTEL_SD_H_ */
