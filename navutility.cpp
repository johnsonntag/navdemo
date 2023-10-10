#include "navutility.h"
#include "utility.h"

double getangle1minusangle2(double angle1,double angle2)
{
  double diff = angle1 - angle2;
  while (diff<-180.0) diff += 360.0;
  while (diff>180.0) diff -= 360.0;
  return(diff);
}


// Adapted from a Karney example found on the web.
// Points A1 and A2 define the desired geodesic.
// Point B1 is an arbitrary point for which we desire to find the distance to the geodesic.
// Point B2 is the point along the geodesic closest to B1.
// Geodesics are nearly straight in the gnomonic projection, and exactly straight if they
// go through the center of projection.  So here we do the following:
// 1. Guess coordinates for B2.
// 2. Make the guess for B2 the center of a gnomonic projection.
// 3. Map A1, A2 and B1 onto this projection.
// 4. Solve the planar intersection problem for an updated B2.
// 5. Repeat until the updates to B2 fall below the desired tolerance.
//

class vector3 {
public:
  double _x, _y, _z;
  vector3(double x, double y, double z = 1) throw()
    : _x(x)
    , _y(y)
    , _z(z) {}
  vector3 cross(const vector3& b) const throw() {
    return vector3(_y * b._z - _z * b._y,
                   _z * b._x - _x * b._z,
                   _x * b._y - _y * b._x);
  }
  void norm() throw() {
    _x /= _z;
    _y /= _z;
    _z = 1;
  }
};


double xtdgeodesic(double lata1,double lona1,double lata2,double lona2,double latb1,double lonb1,int *niter)
{
  int k;
  double latb2,lonb2,latnew,lonnew;
  double xa1, ya1, xa2, ya2,xb1, yb1,snew,sb12;
  const GeographicLib::Geodesic
    geod(GeographicLib::Constants::WGS84_a(),
         GeographicLib::Constants::WGS84_f());
  const GeographicLib::Gnomonic gn(geod);
  double getangle1minusangle2(double,double);
  
  // Initial guess for closest point to B2
  latb2 = latb1;
  lonb2 = lonb1;
  snew = 999.0;
  
  // Find B2 by iteration (Karney's method)
  k = 0;
  while (snew>0.01&&k<10)
  {
    gn.Forward(latb2, lonb2, lata1, lona1, xa1, ya1);
    gn.Forward(latb2, lonb2, lata2, lona2, xa2, ya2);
    gn.Forward(latb2, lonb2, latb1, lonb1, xb1, yb1);
    // See Hartley and Zisserman, Multiple View Geometry, Sec. 2.2.1
    vector3 va1(xa1, ya1); vector3 va2(xa2, ya2);
    // la is homogeneous representation of line A1,A2
    vector3 la = va1.cross(va2);
    vector3 vb1(xb1, yb1);
    // lb is homogeneous representation of line thru B1 perpendicular to la
    vector3 lb(la._y, -la._x, la._x * yb1 - la._y * xb1);
    // p0 is homogeneous representation of intersection of la and lb
    vector3 p0 = la.cross(lb);
    p0.norm();
    gn.Reverse(latb2, lonb2, p0._x, p0._y, latnew, lonnew);
    geod.Inverse(latb2,lonb2,latnew,lonnew,snew);
    latb2 = latnew;
    lonb2 = lonnew;
    k++;
  }
  *niter = k;

  // Calculate distance B1 to B2
  double azb1b2,aztemp;
  geod.Inverse(latb1,lonb1,latb2,lonb2,sb12,azb1b2,aztemp);
  
  // Determine the sign of the xtd
  double aza1a2,azdiff;
  geod.Inverse(lata1,lona1,lata2,lona2,aza1a2,aztemp);
  azdiff = getangle1minusangle2(aza1a2,azb1b2);
  qDebug() << aza1a2 << azb1b2 << azdiff;
  if (azdiff>0.0) return(sb12);
  else return (-sb12);

  //geod1.Inverse(lata1,lona1,latb1,lonb2,azia1b1,azitemp2);
  //geod2.Inverse(lata1,lona1,lata2,lona2,azia1a2,azitemp1);
  //azidiff = getangle1minusangle2(azia1b1,azia1a2);
  //if (azidiff>=0.0)
  //{
  //    return(sb12);
  //}
  //else
  //{
  //    return(-sb12);
  //}
  
}


double xtdloxodrome2(double lata1,double lona1,double lata2,double lona2,double latb1,double lonb1,int *niter)
{
    double xtd;
    double a = GeographicLib::Constants::WGS84_a();
    double f = GeographicLib::Constants::WGS84_f();
    GeographicLib::Rhumb r1(a, f);
    GeographicLib::Rhumb r2(a, f);

    double lata1r = lata1*DEG2RAD;
    double lona1r = lona1*DEG2RAD;
    while (lona1r<0.0) lona1r +=2.0*PI;
    double lata2r = lata2*DEG2RAD;
    double lona2r = lona2*DEG2RAD;
    while (lona2r<0.0) lona2r +=2.0*PI;
    double latb1r = latb1*DEG2RAD;
    double lonb1r = lonb1*DEG2RAD;
    while (lonb1r<0.0) lonb1r +=2.0*PI;

    // Special case - travel along a parallel
    // NEED TO TEST WHEN CROSSING PRIME MERIDIAN AND DATELINE
    if (lata1r==lata2r)
    {
      xtd = 1000.0*RAD2KM*(latb1r-lata1r);
      double crsABdeg = gccourse1(lata1r,lona1r,lata2r,lona2r)*180.0/PI;
      qDebug() << "Rhumb line - travel along a parallel" << crsABdeg << '\n';
      if (fabs(crsABdeg-90.0)<45.0) xtd *=-1.0;
    }

    // Special case - travel along a meridian (which is also a great circle)
    // NEED TO TEST NEAR PRIME MERIDIAN AND DATELINE
    else if ( fabs(lona1r-lona2r)<0.00001 )
    {
      qDebug() << "Rhumb line - travel along a meridian\n";
      double distAD = gcdist(lata1r,lona1r,latb1r,lonb1r);
      double crsAD  = gccourse1(lata1r,lona1r,latb1r,lonb1r);
      double crsAB  = gccourse1(lata1r,lona1r,lata2r,lona2r);
      xtd = 1000.0*RAD2KM*asin(sin(distAD)*sin(crsAD-crsAB));
    }

    // General rhumb line travel
    // THIS IS NOT THOROUGHLY TESTED!!!!!
    else
    {
        double xa,ya,xb,yb,xac,yac,latc,lonc;
        projmercator(lata1r,lona1r,&xa,&ya);
        projmercator(lata2r,lona2r,&xb,&yb);
        projmercator(latb1r,lonb1r,&xac,&yac);
        double crsAB  = gccourse1(lata1r,lona1r,lata2r,lona2r);
        double alpha = crsAB-2.0*PI;
        double mr = (yb-ya)/(xb-xa);
        double xc = (yac-ya+mr*xa+xac*tan(alpha))/(mr+tan(alpha));
        double yc = mr*(xc-xa)+ya;
        inversemercator(xc,yc,&latc,&lonc);
        //xtd = 6076.1*RAD2NM*(gcdist(latc,lonc,latb1r,lonb1r));
        xtd = 1000.0*RAD2KM*(gcdist(latc,lonc,latb1r,lonb1r));

        //double crsDc = gccourse1(latb1r,lonb1r,latc,lonc);
        //double crscB = gccourse1(latc,lonc,lata2r,lona2r);
        //double deltahdg = (crscB-crsDc)*180.0/PI;
        //if (deltahdg<-180.0) deltahdg += 360.0;
        //else if (deltahdg>180.0) deltahdg -= 360.0;
        //if (deltahdg<0.0) xtd *=-1.0;
        qDebug() << "General rhumb line travel";

        //geod.Inverse(lata1,lona1,lata2,lona2,azia1a2,azitemp);
        //geod.Inverse(lata1,lona1,latb1,lonb2,azia1b1,azitemp);
        //azidiff = getangle1minusangle2(azia1b1,azia1a2);
        //if (azidiff>=0.0) return(sb12);
        //else return(-sb12);

        double dtemp;
        double crsa1a2;
        double crsa1b1;
        r1.Inverse(lata1,lona1,lata2,lona2,dtemp,crsa1a2);
        r1.Inverse(lata1,lona1,latb1,lonb1,dtemp,crsa1b1);
        //double crsa1a2 = gccourse1(lata1r,lona1r,lata2r,lona2r); // mistake, must calculate this with lox not gc
        //double crsa1b1 = gccourse1(lata1r,lona1r,latb1r,lonb1r);
        double deltahdg = getangle1minusangle2(crsa1b1,crsa1a2);
        //qDebug() << crsa1a2 << crsa1b1 << deltahdg;
        while(deltahdg<-180.0) deltahdg+=360.0;
        while (deltahdg>180.0) deltahdg-=360.0;
        if (deltahdg<0.0) xtd*=-1.0;
    }

    *niter=0;
    return(xtd);

}


double xtdloxodrome(double lata1,double lona1,double lata2,double lona2,double latb1,double lonb1,int *niter)
{
  double a = GeographicLib::Constants::WGS84_a();
  double f = GeographicLib::Constants::WGS84_f();
  GeographicLib::Geodesic geod(a, f);
  GeographicLib::Rhumb rhumb(a, f);
  GeographicLib::Ellipsoid ell(a, f);
  double azia1a2, sa1b2;
  double getangle1minusangle2(double,double);
    
  // Solve for azia1a2 and define the rhumb line using that
  double sa1a2;
  rhumb.Inverse(lata1,lona1,lata2,lona2,sa1a2,azia1a2);
  GeographicLib::RhumbLine rl = rhumb.Line(lata1,lona1,azia1a2);
  
  // Initial guess for sa1b2
  double azia1b1;
  rhumb.Inverse(lata1,lona1,latb1,lonb1,sa1b2,azia1b1);

  double sb1b2, azib1, azib2, m13, M13, M31;
  double latb2, lonb2;
  double ds = 1.0e6;

  // Find B2 by iteration (Karney's method)
  int k = 0;
  while (fabs(ds)>0.01&&k<10)
  {
    rl.Position(sa1b2, latb2, lonb2);
    geod.Inverse(latb1, lonb1, latb2, lonb2, sb1b2, azib1, azib2, m13, M13, M31);
    double dazi3 = GeographicLib::Math::AngDiff(azia1a2, azib2) * GeographicLib::Math::degree();
    double g = cos(dazi3);
    double lat3r = latb2*GeographicLib::Math::degree();
    double azia1a2r = azib2*GeographicLib::Math::degree();
    double tcr = ell.TransverseCurvatureRadius(latb2);
    double dg = (-sin(dazi3)*(-sin(dazi3)*M31/m13+tan(lat3r)*sin(azia1a2r)/tcr));
    ds = -g/dg;
    sa1b2 += ds;
    k++;
  }
  *niter = k;
  
  // Calculate and return distance B1 to B2
  rl.Position(sa1b2, latb2, lonb2);
  geod.Inverse(latb1,lonb1,latb2,lonb2,sb1b2,azib1,azib2);
  double azidiff = getangle1minusangle2(azia1b1,azia1a2);
  if (azidiff>=0.0) return(sb1b2);
  else return(-sb1b2);  
  
}

//#define PI (4.0*atan((double)(1.0)))
//#define DEG2RAD (PI/180.0)
//#define RAD2NM (180.0*60.0/PI)
//#define RAD2KM (RAD2NM*6076.1*12.0*2.54/100.0/1000.0)

double xtdgreatcircle(double lata1,double lona1,double lata2,double lona2,double latb1,double lonb1)
{
  //double gcdist(double,double,double,double);
  //double gccourse1(double,double,double,double);

  // Compute XTD according to ATM/OIB formulation
  double latA = lata1*DEG2RAD;
  double latB = lata2*DEG2RAD;
  double latD = latb1*DEG2RAD;
  double lonA = lona1*DEG2RAD;
  double lonB = lona2*DEG2RAD;
  double lonD = lonb1*DEG2RAD;
  double distAD = gcdist(latA,lonA,latD,lonD);
  double crsAD = gccourse1(latA,lonA,latD,lonD);
  double crsAB = gccourse1(latA,lonA,latB,lonB);
  return(asin(sin(distAD)*sin(crsAD-crsAB))*RAD2KM*1000.0);
  
}


//double gcdist(double lat1,double lon1,double lat2,double lon2)
//{
//  double dist;
//
//  lon1 = -lon1;
//  lon2 = -lon2;
//  dist = acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
//  return(dist);
//
//}


//double gccourse1(double lat1,double lon1,double lat2,
//                 double lon2)
//{
//  double dist,tc1;
//
//  /*  Change longitude sign convention  */
//  if (lon1<0.0)
//    lon1 += 2.0*PI;
//  if (lon2<0.0)
//    lon2 += 2.0*PI;
//  lon1 = -lon1;
//  lon2 = -lon2;
//
//  /*  Check for pole  */
//  if (cos(lat1) < 0.00001)
//  {
//    if (lat1 > 0)
//      tc1 = PI;
//    else
//      tc1 = 0;
//  }
//
//  /*  Check for meridian  */
//  //else if (lon1 == lon2)
//  else if (fabs(lon1-lon2)<(0.00001*DEG2RAD))
//  {
//    if (lat1>lat2)
//    {
//      tc1 = PI;
//    }
//    else
//    {
//      tc1 = 0.0;
//    }
//  }
//
//  /*  Point 1 not a pole  */
//  else
//  {
//    dist = acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
//    tc1 = acos((sin(lat2)-sin(lat1)*cos(dist))/(sin(dist)*cos(lat1)));
//    if (sin(lon2-lon1)>=0)
//      tc1 = 2*PI-tc1;
//  }
//
//  /*  Return the result  */
//  return(tc1);
//
//}
