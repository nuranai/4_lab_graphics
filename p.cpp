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
        std::vector<Point3D> projectPoints((X_MAX - X_MIN)/D_X + 2);
        std::vector<Point3D> lastProjectPoints((X_MAX - X_MIN)/D_X + 2);
        std::vector<int> lastVids((X_MAX - X_MIN)/D_X + 2, -1);
        while (current.getX() < (X_MAX + D_X/2))
        {
            current.setY(f(current.getX(), current.getZ()));

            projectPoints[i] = rotateMatrix.changePoint(current);
            //projectPoint.setX(1280 * projectPoint.getX() / (Pk.x() * 2) + 1280/2);
            //projectPoint.setY(720 * projectPoint.getY() / (Pk.y() * 2) + 720/2);

            //projectPoint.setX(projectPoint.getX() * 100 + 1280/2);
            //projectPoint.setY(projectPoint.getY() * 100 + 720/2);

            int Vid = 0;
            if (projectPoints[i].getY() >= Up[i])
                Vid += 1;

            if (projectPoints[i].getY() <= Down[i])
                Vid += 2;

            if (Vid != 0)
            {
                painter.setPen(QPen(QBrush(QColor(color, 255 - color, 255-i*5, 255)), 3));
                painter.drawPoint(QPoint(projectPoints[i].getX() * 100 + 1280/2, 720/2 - projectPoints[i].getY() * 100));
/*
                if (Vid == 1 || Vid == 3)           //выше верхнего
                {
                    Up[i] = projectPoint.getY();
                }

                if (Vid > 1)                       //ниже нижнего
                {
                    Down[i] = projectPoint.getY();
                }*/
            }

            if (lastVids[i] > -1 && (Vid != 0 || lastVids[i] != 0))
            {
                correction(Up, Down, lastProjectPoints[i], projectPoints[i]);
            }


            lastVids[i] = Vid;
            lastProjectPoints[i] = projectPoints[i];

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

void Projection::correction(std::vector<double>& Up, std::vector<double>& Down, Point3D lastPoint, Point3D currentPoint)
{
    if (abs(lastPoint.getX() - currentPoint.getX()) < 0.15)
    {
        /*if (Up[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)] < lastPoint.getY())
            Up[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)] = lastPoint.getY();
        if (Up[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)] < currentPoint.getY())
            Up[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)] = currentPoint.getY();

        if (Down[abs(lastPoint.getX() - X_MIN)/D_X + 1] > lastPoint.getY())
            Down[abs(lastPoint.getX() - X_MIN)/D_X + 1] = lastPoint.getY();
        if (Down[abs(lastPoint.getX() - X_MIN)/D_X + 1] > currentPoint.getY())
            Down[abs(lastPoint.getX() - X_MIN)/D_X + 1] = currentPoint.getY();*/
         Up[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)] = qMax(qMax((int)lastPoint.getY(), (int)currentPoint.getY()),(int)Up[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)]);
         Down[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)] = qMin(qMin((int)lastPoint.getY(), (int)currentPoint.getY()),(int)Down[int(abs(lastPoint.getX() - X_MIN)/D_X + 1)]);
    }
    else
    {
        double m = (currentPoint.getY() - lastPoint.getY()) / (currentPoint.getX() - lastPoint.getX());
        double Y = lastPoint.getY();
        for (double X = lastPoint.getX(); X < currentPoint.getX(); X++)
            {
                int Vid = 0;
                if (Y >= Up[(X - X_MIN)/D_X + 1])
                    Vid += 1;

                if (Y <= Down[(X - X_MIN)/D_X + 1])
                    Vid += 2;

                if (Vid != 0)
                {
                    if (Vid == 1 || Vid == 3)           //выше верхнего
                    {
                        Up[(X - X_MIN)/D_X + 1] = Y;
                    }

                    if (Vid > 1)                       //ниже нижнего
                    {
                        Down[(X - X_MIN)/D_X + 1] = Y;
                    }
                }

                Y += m;
            }


    }
}

void Projection::newFrame()
{
    rotateMatrix.rotateByY(current_angle_y);
    rotateMatrix.rotateByX(current_angle_x);
    rotateMatrix.rotateByZ(current_angle_z);
    update();
}

