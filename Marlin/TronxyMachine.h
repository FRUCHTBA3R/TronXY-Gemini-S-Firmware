#pragma once
#define PROJ_GEMINIS       30 //f446,U 300-300-400
#define PROJ_GEMINIXS      32 //f446,U 255-255-260
#define PROJ_GEMINID1      33 //f446,U 255-255-280
#define PROJ_GEMINIX       36 //f446,U 330-330-400

#define UI_MARLIN_DEFAULT  0
#define UI_SIM480X320      2

#define TRONXY_PROJ        PROJ_GEMINIS
#define TRONXY_UI          UI_SIM480X320

#if TRONXY_UI > 0
#define HAS_TRONXY_UI      1
#endif
#if TRONXY_PROJ
#define HAS_TRONXY_PROJ    1
#endif

#if TRONXY_PROJ == PROJ_GEMINIS

#define TRONXY_MACHINE_NAME       "GeminiS"
#define TRONXY_BACKUP_POWER       0 //UPS function, please note that certain pins are required for power failure detection and configure the corresponding interrupt function.
#define TRONXY_SCREEN_SHUTDOWN    1 //Screen off function
#define TRONXY_HOME_XY_ONLY       0 //Is the manual debugging interface reset only XY reset? If so, the Z reset button is activated, otherwise it is invalid.
#define WIFI_INTERFACE            0 //WIFI function
#define TAOLI_SERIAL              0
#define LASER_SERIAL              0 //wifi terminal for laser PWM control
#define DUAL_ZMAX_HOME            0 //Big end reset, reset in the opposite direction, then return to the forward direction to find 0 point
#define Z_BED_MOVE                0 //Z-axis movement: hot bed
#define EXTRUDERS                 2 //Number of extruders
#define INVERT_E0_DIR             true //TITAN:true,true; BMG:false,true
#define INVERT_E1_DIR             true
#define USE_EXTRUDER              1 //T,B TITAN:1,BMG:2,TAOLI:3,general:4
// #define FIX_MOUNTED_PROBE

#elif TRONXY_PROJ == PROJ_GEMINIXS

#define TRONXY_MACHINE_NAME       "GeminiXS"
#define TRONXY_BACKUP_POWER       0 //UPS function, please note that certain pins are required for power failure detection and configure the corresponding interrupt function.
#define TRONXY_SCREEN_SHUTDOWN    1 //Screen off function
#define TRONXY_HOME_XY_ONLY       0 //Is the manual debugging interface reset only XY reset? If so, the Z reset button is activated, otherwise it is invalid.
#define WIFI_INTERFACE            0 //WIFI function
#define TAOLI_SERIAL              0
#define LASER_SERIAL              0 //wifi terminal for laser PWM control
#define DUAL_ZMAX_HOME            0 //Big end reset, reset in the opposite direction, then return to the forward direction to find 0 point
#define Z_BED_MOVE                0 //Z-axis movement: hot bed
#define EXTRUDERS                 2 //Number of extruders
#define INVERT_E0_DIR             true //TITAN:true,true; BMG:false,true
#define INVERT_E1_DIR             true
#define USE_EXTRUDER              1 //T,B TITAN:1,BMG:2,TAOLI:3,general:4
// #define FIX_MOUNTED_PROBE

#elif TRONXY_PROJ == PROJ_GEMINID1

#define TRONXY_MACHINE_NAME       "GeminiD1"
#define TRONXY_BACKUP_POWER       0 //UPS function, please note that certain pins are required for power failure detection and configure the corresponding interrupt function.
#define TRONXY_SCREEN_SHUTDOWN    1 //Screen off function
#define TRONXY_HOME_XY_ONLY       0 //Is the manual debugging interface reset only XY reset? If so, the Z reset button is activated, otherwise it is invalid.
#define WIFI_INTERFACE            0 //WIFI function
#define TAOLI_SERIAL              0
#define LASER_SERIAL              0 //wifi terminal for laser PWM control
#define DUAL_ZMAX_HOME            0 //Big end reset, reset in the opposite direction, then return to the forward direction to find 0 point
#define Z_BED_MOVE                1 //Z-axis movement: hot bed
#define EXTRUDERS                 2 //Number of extruders
#define INVERT_E0_DIR             false //BMG:false,false
#define INVERT_E1_DIR             false
#define USE_EXTRUDER              2 //TITAN:1,BMG:2,TAOLI:3,general:4
// #define FIX_MOUNTED_PROBE

#elif TRONXY_PROJ == PROJ_GEMINIX

#define TRONXY_MACHINE_NAME       "GeminiX"
#define TRONXY_BACKUP_POWER       0 //UPS function, please note that certain pins are required for power failure detection and configure the corresponding interrupt function.
#define TRONXY_SCREEN_SHUTDOWN    1 //Screen off function
#define TRONXY_HOME_XY_ONLY       0 //Is the manual debugging interface reset only XY reset? If so, the Z reset button is activated, otherwise it is invalid.
#define WIFI_INTERFACE            0 //WIFI function
#define TAOLI_SERIAL              0
#define LASER_SERIAL              1 //wifi terminal for laser PWM control
#define DUAL_ZMAX_HOME            0 //Big end reset, reset in the opposite direction, then return to the forward direction to find 0 point
#define Z_BED_MOVE                1 //Z-axis movement: hot bed
#define EXTRUDERS                 2 //Number of extruders
#define INVERT_E0_DIR             false //BMG:false,false
#define INVERT_E1_DIR             false
#define USE_EXTRUDER              2 //TITAN:1,BMG:2,TAOLI:3,general:4
// #define FIX_MOUNTED_PROBE

#else

#error "You haven't configure this machine."

#endif
