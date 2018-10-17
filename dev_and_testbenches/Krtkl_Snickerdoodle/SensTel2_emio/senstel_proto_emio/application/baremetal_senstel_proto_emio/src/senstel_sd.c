/*
 * senstel_sd.c
 *
 *  Created on: May 8, 2018
 *      Author: Chinook-ELE
 */




#include <stdio.h>
#include "xparameters.h"	/* SDK generated parameters */
#include "xsdps.h"		/* SD device driver */
#include "diskio.h"
#include "xil_printf.h"
#include "ff.h"
#include "senstel_sd.h"
#include "senstel_sd_filesys_config.h"

//#ifdef _FS_MINIMIZE
//#undef _FS_MINIMIZE
//#define _FS_MINIMIZE 0
//#endif /* _FS_MINIMIZE */

//void vGetDbConfig(xSdDb_t *FsDatabase)
//{
//	FsDatabase->ulFilesOpen = 0;
//	FsDatabase->ulBytesWritten = 0;
//	//TODO: Add session start timestamp in fname and dirname
////	sprintf(fname, ACQ_FNAME);
////	FsDatabase->xFsFiles->fname = fname;
//	//	FsDatabase->xFsFiles->xAcqFileName = ACQ_FNAME;
////	sprintf(FsDatabase->xFsFiles->xAcqFileName, ACQ_FNAME);
//	FsDatabase->xFsFiles->xAcqFileName = ACQ_FNAME;
////	sprintf(FsDatabase->xFsFiles->xLogFileName, LOG_FNAME);
//	FsDatabase->xFsFiles->xLogFileName = LOG_FNAME;
////	sprintf(FsDatabase->xPath, PATH_NAME);
//	FsDatabase->xPath = PATH_NAME;
////	sprintf(FsDatabase->xDirName, DIR_NAME);
//	FsDatabase->xFilesDirName = DIR_NAME;
//}

int ulMountFs(FATFS *fatfs, FIL *file, DIR *dir)
{
	FRESULT Res;
	BYTE ini_s;

	ini_s = disk_initialize(XPAR_PS7_SD_1_DEVICE_ID);

	/*
	 * To test logical drive 0, Path should be "0:/"
	 * For logical drive 1, Path should be "1:/"
	 */
//	FATFS fatfs;
	TCHAR *Path = "0:/";

	/*
	 * Register volume work area, initialize device
	 */
	Res = f_mount(fatfs,
//	Res = f_mount(&fatfs,
//			FsDatabase->xPath,
			Path,
			1);

	if (Res != FR_OK) {
		return XST_FAILURE;
	}

	/*
	 * Path - Path to logical driver, 0 - FDISK format.
	 * 0 - Cluster size is automatically determined based on Vol size.
	 */
//	Res = f_mkfs((TCHAR *)FsDatabase->xPath, 0, 0);
	Res = f_mkfs(Path, 0, 0);
//	Res = f_mkfs(FsDatabase->xPath, 0, 0);
	if (Res != FR_OK) {
		return XST_FAILURE;
	}

	char dirname[64];

//	sprintf(dirname, "acq_d%d_m%d_h%d_m%d", 10, 6, 13, 37);
//	Res = f_mkdir((TCHAR *)dirname);
//	Res = f_opendir(dir, (TCHAR *)dirname);
//	Res = f_chdir((TCHAR *)dirname);

	Res = f_open(
				file,
	//			FsDatabase->xFsFiles->xLogFileName,
				"somefile.txt",
				FA_OPEN_ALWAYS | FA_WRITE | FA_READ
				);

		if (Res) {
			return XST_FAILURE;
		}

		/*
		 * Pointer to beginning of file.
		 */
		Res = f_lseek(file, 0);
	//	Res = f_lseek(FsDatabase->xFsFiles->ptrLogFile, 0);
		if (Res) {
			return XST_FAILURE;
		}

//		Res = f_printf(file, "This is: %s", "Written");
		char word[75];
		sprintf(word, "STRING FORMAT TEST + TCHAR CASTING: drop the %s\n", "bomb");
		Res = f_puts((TCHAR *)word, file);
		sprintf(word, "FLOAT FORMAT TEST USING SPRINTF:drop the %f\n", 666.612);
		Res = f_puts((TCHAR *)word, file);
		sprintf(word, "CSV FORMAT TEST: %d, %d, %d, %d, %d\n", 8, 16, 32, 64, 128);
		Res = f_puts((TCHAR *)word, file);
		Res = f_puts("CHECKING BKSLSH+N SUPPORT:This is: Something written\n\n", file);
		Res = f_puts("It goes like this...:\n\n", file);
		Res = f_puts("Maybe something with numeric formatting soon\n", file);
//		Res = f_puts((TCHAR *)word, file);
		Res = f_printf(file, "Christmas is on the: %d th of December.\n", 25);
		Res = f_printf(file, "STR FRMT TST: This is: %s", "Written");
	//	Res = f_write(File, (const void*)SourceAddress, FileSize,
	//			&NumBytesWritten);
		if (Res < 0) {
			return XST_FAILURE;
		}

		Res = f_close(file);
		if (Res < 0) {
			return XST_FAILURE;
		}


		Res = f_mount(0, "", 1);
		if (Res < 0) {
			return XST_FAILURE;
		}
		return XST_SUCCESS;
}

int ulOpenFiles(FATFS *fatfs, FIL *file)
{
	FRESULT Res;
	char dirname[64];

//	sprintf(dirname, "acq_d%d_m%d_h%d_m%d", 10, 6, 13, 37);
//	f_mkdir((TCHAR *)dirname);
//	f_opendir(dir);
//
//	f_opendir(FsDatabase->xFilesDir, FsDatabase->xFilesDirName);

//	FIL *file;

//	Res = f_open(
////			FsDatabase->xFsFiles->ptrAcqFile,
//			file,
//			"dude.txt",
//			FA_CREATE_ALWAYS | FA_WRITE | FA_READ
//			);

	Res = f_open(
			file,
//			FsDatabase->xFsFiles->xLogFileName,
			"somefile.txt",
			FA_CREATE_ALWAYS | FA_WRITE | FA_READ
			);

	if (Res) {
		return XST_FAILURE;
	}

	/*
	 * Pointer to beginning of file.
	 */
	Res = f_lseek(file, 0);
//	Res = f_lseek(FsDatabase->xFsFiles->ptrLogFile, 0);
	if (Res) {
		return XST_FAILURE;
	}

	Res = f_printf(file, "This is: %s", "Written");
//	Res = f_write(File, (const void*)SourceAddress, FileSize,
//			&NumBytesWritten);
	if (Res < 0) {
		return XST_FAILURE;
	}

//	FsDatabase->ulFilesOpen = 2;

	return XST_SUCCESS;
}

//TODO: Format data buffer here or have them submit me a string
//int ulDumpToFile(FIL *File, char* buffer, u16 buflength)
int ulDumpToFile(FIL *File)
{
	FRESULT Res;

	/*
	 * Write data to file.
	 */
	Res = f_printf(File, "This is: %s", "Written");
//	Res = f_write(File, (const void*)SourceAddress, FileSize,
//			&NumBytesWritten);
	if (Res < 0) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int ulCloseFiles(xSdDb_t *FsDatabase)
{
	FRESULT Res;

	Res = f_close(FsDatabase->xFsFiles->ptrAcqFile);
	Res = f_close(FsDatabase->xFsFiles->ptrLogFile);

	FsDatabase->ulFilesOpen = 0;

	return XST_SUCCESS;
}

//int ulUnmountFs(xSdDb_t *FsDatabase)
//{
//	FRESULT Res;
//
//	return XST_SUCCESS;
//}
