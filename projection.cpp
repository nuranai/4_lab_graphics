#include "projection.h"

#include <vector>
#include <iostream>

Projection::Projection()
{
    setMinimumSize(1280, 720);
    setMaximumSize(1280, 720);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setPalette(Pal);
    setAutoFillBackground(true);

    //rotateMatrix.rotateByZ(M_PI);
    //rotateMatrix.shift(2, 2, 0);

    newFrame();
}


void Projection::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setPen(QPen(QBrush(Qt::blue), 3));
    //painter.drawLine(QLine(QPoint(10, 10), QPoint(600, 600)));


    QPoint Pk = window_method();


    std::vector<double> Up((X_MAX - X_MIN)/D_X + 2, 0);
    std::vector<double> Down = Up;

    Point3D current(X_MIN, 0, Z_MIN);
    int color = 0;
    while (current.getZ() < (Z_MAX + D_Z/2))
    {
        int i = 0;
        while (current.getX() < (X_MAX + D_X/2))
        {
            current.setY(f(current.getX(), current.getZ()));

            Point3D projectPoint = rotateMatrix.changePoint(current);

            projectPoint.setX(projectPoint.getX() * 75 + 1280/2);
            projectPoint.setY(projectPoint.getY() * 75 + 720/2);

            int Vid = 0;
            if (projectPoint.getY() >= Up[i])
                Vid += 1;

            if (projectPoint.getY() <= Down[i])
                Vid += 2;

            if (Vid != 0)
            {
                //painter.setPen(QPen(QBrush(QColor(255, 255, 255, 255)), 3));
                painter.setPen(QPen(QBrush(QColor(color, 255 - color, 255-i*5, 255)), 3));
                painter.drawPoint(QPoint(projectPoint.getX(), 720 - projectPoint.getY()));

                if (Vid == 1 || Vid == 3)           //выше верхнего
                {
                    Up[i] = projectPoint.getY();
                }

                if (Vid > 1)                       //ниже нижнего
                {
                    Down[i] = projectPoint.getY();
                }
            }

            current.shiftByX(D_X);
            i++;
        }
        color += 10;
        current.setX(X_MIN);
        current.shiftByZ(D_Z);
    }

}


QPoint Projection::window_method()
{
    std::vector<QPoint> X(4);
    X[0] = QPoint(X_MIN, Z_MIN);
    X[1] = QPoint(X_MAX, Z_MIN);
    X[2] = QPoint(X_MIN, Z_MAX);
    X[3] = QPoint(X_MAX, Z_MAX);

    QPoint Pk(X[0].manhattanLength(), 0);
    for (unsigned i = 1; i < X.size(); i++)
        Pk.setX(qMax(Pk.x(), X[i].manhattanLength()));

    Point3D current(X_MIN, 0, Z_MIN);
    while (current.getZ() < (Z_MAX + D_Z/2))
    {
        while (current.getX() < (X_MAX + D_X/2))
        {
            current.setY(f(current.getX(), current.getZ()));

            int newY = rotateMatrix.changePoint(current).getY();
            Pk.setY(qMax(Pk.y(), newY));

            current.shiftByX(D_X);
        }
        current.shiftByZ(D_Z);
    }
}

void Projection::newFrame()
{
    rotateMatrix.rotateByY(current_angle_y);
    rotateMatrix.rotateByX(current_angle_x);
    rotateMatrix.rotateByZ(current_angle_z);
    update();
}
