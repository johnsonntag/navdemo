#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QString>

enum navtechnique { geodesic, greatcircle, loxodrome, undefined };

struct wp
{
    QString name;
    double lat;
    double lon;
};

struct seg
{
    QString name1;
    double lat1;
    double lon1;
    QString name2;
    double lat2;
    double lon2;
    double alt;
    navtechnique nt;
    bool reversible;
};

#endif // DATASTRUCTURES_H
