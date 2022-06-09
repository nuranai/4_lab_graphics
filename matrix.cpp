#include "matrix.h"
#include <QtMath>

void Matrix::operator*=(const Matrix& temp)
{
   Matrix result;

   for (int i = 0; i < 4; i++)
       for (int j = 0; j < 4; j++)
       {
           result.matrix[i][j] = 0;
           for (int k = 0; k < 4; k++)
               result.matrix[i][j] += matrix[i][k] * temp.matrix[k][j];
       }
   operator=(result);
}

Matrix::Matrix()
{
    matrix = new double*[4];
    for (int i = 0; i < 4; i++)
        matrix[i] = new double[4];

    reset();
}

Matrix::Matrix(const Matrix& newMatrix)
{
    matrix = new double*[4];
    for (int i = 0; i < 4; i++)
    {
        matrix[i] = new double[4];
        for (int j = 0; j < 4; j++)
            matrix[i][j] = newMatrix.matrix[i][j];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < 4; i++)
        delete[] matrix[i];

    delete[] matrix;
}


void Matrix::reset()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                matrix[i][j] = 1.0;
            else
                matrix[i][j] = 0.0;
}

void Matrix::shift(double dx, double dy, double dz)
{
    Matrix shiftMatrix;

    shiftMatrix.matrix[3][0] = dx;
    shiftMatrix.matrix[3][1] = dy;
    shiftMatrix.matrix[3][2] = dz;

    this->operator*=(shiftMatrix);
}

void Matrix::scale(double dx, double dy, double dz)
{
    Matrix scaleMatrix;

    scaleMatrix.matrix[0][0] = dx;
    scaleMatrix.matrix[1][1] = dy;
    scaleMatrix.matrix[2][2] = dz;

    operator*=(scaleMatrix);
}

void Matrix::rotateByX(double angle)
{
    Matrix rotateMatrix;

    rotateMatrix.matrix[1][1] = cos(angle);
    rotateMatrix.matrix[2][1] = sin(angle);
    rotateMatrix.matrix[1][2] = -sin(angle);
    rotateMatrix.matrix[2][2] = cos(angle);

    operator*=(rotateMatrix);
}

void Matrix::rotateByY(double angle)
{
    Matrix rotateMatrix;

    rotateMatrix.matrix[0][0] = cos(angle);
    rotateMatrix.matrix[2][0] = -sin(angle);
    rotateMatrix.matrix[0][2] = sin(angle);
    rotateMatrix.matrix[2][2] = cos(angle);

    operator*=(rotateMatrix);
}

void Matrix::rotateByZ(double angle)
{
    Matrix rotateMatrix;

    rotateMatrix.matrix[0][0] = cos(angle);
    rotateMatrix.matrix[1][0] = sin(angle);
    rotateMatrix.matrix[0][1] = -sin(angle);
    rotateMatrix.matrix[1][1] = cos(angle);

    operator*=(rotateMatrix);
}

Point3D Matrix::changePoint(const Point3D& point)
{
    double newX = point.getX() * matrix[0][0] + point.getY() * matrix[1][0] + point.getZ() * matrix[2][0] + matrix[3][0];
    double newY = point.getX() * matrix[0][1] + point.getY() * matrix[1][1] + point.getZ() * matrix[2][1] + matrix[3][1];
    double newZ = point.getX() * matrix[0][2] + point.getY() * matrix[1][2] + point.getZ() * matrix[2][2] + matrix[3][2];

    Point3D res(newX, newY, newZ);
    return res;
}

void Matrix::operator =(const Matrix& temp)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = temp.matrix[i][j];
}
