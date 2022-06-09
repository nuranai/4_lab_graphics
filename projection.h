#ifndef PROJECTION_H
#define PROJECTION_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QPoint>
#include "Point3D.h"
#include "matrix.h"

class Projection : public QWidget
{
    Q_OBJECT
public:
    Projection();
    virtual ~Projection() {}

public slots:
    void newFrame();

private slots:
    void paintEvent(QPaintEvent *event);

private:

    QPoint window_method();
    void correction(std::vector<double>& Up, std::vector<double>& Down, Point3D lastPoint, Point3D currentPoint);

    Matrix rotateMatrix;


    double f(double x, double z) { double a = qSqrt(x*x + z*z); return cos(a)/(a+1); };
    const int X_MAX = 2*M_PI;
    const int X_MIN = -2*M_PI;
    const int Z_MAX = 2*M_PI;
    const int Z_MIN = -2*M_PI;

    const double D_X = 0.1*M_PI;
    const double D_Z = 0.1*M_PI;

    double current_angle_x = -0.1;
    double current_angle_y = 0;
    double current_angle_z = 0;
};

#endif // PROJECTION_H
