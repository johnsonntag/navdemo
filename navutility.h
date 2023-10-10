#include <math.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <exception>
#include <GeographicLib/Gnomonic.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Utility.hpp>
#include <GeographicLib/Rhumb.hpp>
#include <GeographicLib/Ellipsoid.hpp>
#include <QDebug>

double xtdgeodesic(double,double,double,double,double,double,int *);
double xtdgreatcircle(double,double,double,double,double,double);
double xtdloxodrome(double,double,double,double,double,double,int *);
double xtdloxodrome2(double,double,double,double,double,double,int *);
