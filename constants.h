#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

// General constants
#define PI (4.0*atan((double)(1.0)))
#define DEG2RAD (PI/180.0)
#define RAD2NM  (180.0*60.0/PI)
#define RAD2KM  (RAD2NM*6076.1*12.0*2.54/100.0/1000.0)
#define NM2KM (6076.1*12.0*2.54/100.0/1000.0)
#define FT2M (12.0*2.54/100.0)  // divide by 3,28
#define M2FT (100.0/2.54/12.0)  // multiply by 3.28
#define AE 6378137.0
#define FLAT (1.0/298.257223563)

// Constants used by auto waypoint algorithms
#define SIMPLE_THRESHOLD_NM 1.0
#define TRAV_XTE_FT 500.0
#define TRAV_TRACK_DEG 10.0
#define APPR_XTE_FT 5000.0
#define APPR_TRACK_DEG 30.0
#define APPR_DIST_NM 30.0
#define DPRT_XTE_FT 200.0
#define DPRT_TRACK_DEG 5.0
#define DPRT_DIST_NM 20.0

// ILS constants
#define DDMLMAX 0.155
#define DDMGMAX 0.175


#endif // CONSTANTS_H

