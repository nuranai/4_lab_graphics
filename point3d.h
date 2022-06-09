#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{
private:
    double x = 0;
    double y = 0;
    double z = 0;

public:
    Point3D() {};
    Point3D(double x_, double y_, double z_);

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    void setX(double new_x) { x = new_x; }
    void setY(double new_y) { y = new_y; }
    void setZ(double new_z) { z = new_z; }

    void shiftByX(double shift);
    void shiftByY(double shift);
    void shiftByZ(double shift);

    Point3D operator =(const Point3D& newPoint);
};


#endif // POINT3D_H
