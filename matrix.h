#ifndef MATRIX_H
#define MATRIX_H

#include "point3d.h"

class Matrix
{
private:
    double** matrix;

    void operator *= (const Matrix& temp);

public:
    Matrix();
    Matrix(const Matrix& newMatrix);
    ~Matrix();

    void reset();
    void shift(double dx, double dy, double dz);
    void scale(double dx, double dy, double dz);
    void rotateByX(double angle);
    void rotateByY(double angle);
    void rotateByZ(double angle);

    Point3D changePoint(const Point3D& point);

    void operator =(const Matrix& temp);
};

#endif // MATRIX_H
