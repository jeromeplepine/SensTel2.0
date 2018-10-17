//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook VII
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : ChinookCanUtils.h
// Author  : Gabriel Jean-Louis
// Date    : 2017-06-23
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : 
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : NA
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef _CHINOOK_CAN_UTILS_H    /* Guard against multiple inclusion */
#define _CHINOOK_CAN_UTILS_H


/********************************************/
// Add all CAN messageSID from projects.
/********************************************/
// Backplane messageSID
#define BACKPLANE_BOARD_SID             0x70
#define DISCONNECT_FROM_BACKPLANE       0x71

// Mast messageSID
#define MAST_BOARD_SID                  0x30
#define MAST_DISCONNECT_SID             0x31
#define MAST_DIRECTION_SID              0x32
#define MAST_MODE_SID                   0x33
#define MAST_CALIB_DONE_SID             0x34
#define IDENTIFICATION_TO_BACKPLANE     0x70
    
// Pitch messageSID
#define ID_PITCH_IDENTIFICATION        0x10
#define ID_PITCH_DISCONNECT            0x11
#define ID_PITCH_STATE                 0x12
#define ID_PITCH_VALUE                 0x13

// Gear messageSID
#define ID_GEAR_IDENTIFICATION         0x20
#define ID_GEAR_DISCONNECT             0x21
#define ID_GEAR_STATE                  0x22
#define ID_GEAR_VALUE                  0x23

// SensTel messageSID
#define WIND_SPEED_ID                   0x19
#define WIND_DIRECTION_ID               0x20
#define TURBINE_RPM_ID                  0x21
#define WHEEL_RPM_ID                    0x22
#define ACQ_ACK							0x25

// Volant messageSID
#define VOLANT_BOARD_SID                0x40
#define VOLANT_DISCONNECT_SID           0x41
#define VOLANT_SW_MSG                   0x42

/*
 * TODO: Added to match Gabe's mods
 */
#define VOLANT_MAST_MODE                0x43

#define VOLANT_MAST_DIR                 0x44
// Not used for now could be implemented in the futur.
#define VOLANT_MAST_ZERO                0x45
//#define VOLANT_SET_PITCH                0x46
//#define VOLANT_PITCH_STOP               0x47
#define VOALNT_PITCH_ZERO               0x48
#define VOLANT_WEATHER_ZERO             0x49
#define VOLANT_GEAR_UP                  0x4A
#define VOLANT_GEAR_DOWN                0x4B
#define VOLANT_GEAR_ZERO                0x4C

// General messageSID
#define CALIB_DONE_SID                  0xC2

#define EMPTY_CAN_MSG                   0x00


#endif /* _CHINOOK_CAN_UTILS_H */

/* *****************************************************************************
 End of File
 */
