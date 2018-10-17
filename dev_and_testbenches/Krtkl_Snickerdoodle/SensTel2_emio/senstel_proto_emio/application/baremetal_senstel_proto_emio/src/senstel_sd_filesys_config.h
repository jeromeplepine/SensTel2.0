#ifndef _SENSTEL_SD_FILESYS_CONFIG
#define _SENSTEL_SD_FILESYS_CONFIG

#include "xsdps.h"		/* SD device driver */
#include "diskio.h"
#include "xil_printf.h"
#include "ff.h"

#define NUM_BEAST	666
#define NUM_FILES	2

#define	MAX_FNAME_LEN	32
#define PATH_NAME	"0:/"
#define	DIR_NAME	"AcqData"
#define ACQ_FNAME	"Acq.txt"
#define LOG_FNAME	"Logfile.txt"

typedef struct xSdFiles xSdFiles_t;
typedef struct xSdDb xSdDb_t;

/*
 * 	SensTel will switch between those two files for writing its
 * 	system info.
 */
struct xSdFiles{
	FIL *ptrAcqFile;
//	char xAcqFileName[MAX_FNAME_LEN];
//	TCHAR xAcqFileName[MAX_FNAME_LEN];
	char *xAcqFileName;
	FIL *ptrLogFile;
//	TCHAR xLogFileName[MAX_FNAME_LEN];
	char *xLogFileName;
//	char xLogFileName[MAX_FNAME_LEN];
	//	char fname[MAX_FNAME_LEN];
	//	char *fname;
};

/*
 *	Sd filesystem database struct
 */
struct xSdDb{
	FATFS *fatfs;
	u32 ulBytesWritten;
	u32 ulFilesOpen;
	xSdFiles_t *xFsFiles;
	TCHAR *xPath;
//	char xPath[MAX_FNAME_LEN];
	DIR *xFilesDir;
	TCHAR *xFilesDirName;
//	char xDirName[MAX_FNAME_LEN];
};

//typedef eFile eFile_t;

#endif
