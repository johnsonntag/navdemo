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

#endif // DATASTRUCTURES_H
