#include "point3d.h"

Point3D::Point3D(double x_, double y_, double z_)
{
    x = x_;
    y = y_;
    z = z_;
}

void Point3D::shiftByX(double shift)
{
    x += shift;
}

void Point3D::shiftByY(double shift)
{
    y += shift;
}

void Point3D::shiftByZ(double shift)
{
    z += shift;
}


Point3D Point3D::operator =(const Point3D& newPoint)
{
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
}
