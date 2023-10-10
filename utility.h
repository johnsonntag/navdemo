#include <sys/time.h>
#include <math.h>

#include "constants.h"

//#define PI (4.0*atan((double)(1.0)))
//#define DEG2RAD (PI/180.0)
//#define RAD2NM (180.0*60.0/PI)
//#define RAD2KM (RAD2NM*6076.1*12.0*2.54/100.0/1000.0)
//#define M2FT (100.0/2.54/12.0)

double timediff(timeval, timeval);
double gcdist(double lat1,double lon1,double lat2,double lon2);
double gccourse1(double lat1,double lon1,double lat2,double lon2);
void gcproject(double lat1,double lon1,double tc1,double dist,
                 double *lat2,double *lon2);
void navcalc(double lat,double lon,double h,double lat1,double lon1,double h1,
             double lat2,double lon2,double h2,double *xtdiff,double *hdiff,
             int *pflag,double *tot);
void sec2hms(double sec,int *h,int *m,double *s);
void parsehms(double hms,int *hour,int *min,double *sec);
void parseymd(int hms,int *year,int *month,int *day);
void latlon2xy(double lat,double lon,double loncm,int projection,double *x,double *y);
int geod2ps(double latd,double lond,double latcd,double lon0d,double k0,
                       double ae,double flat,double *x,double *y);

int geod2utm(double lat,double lon,double loncm,double *y,double *x,int *zone);
void projmercator(double, double, double *, double *);
void inversemercator(double, double, double *, double *);

