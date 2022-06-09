#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QTimer>
#include <QPushButton>
#include "projection.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVBoxLayout *generalVLayout;
    QHBoxLayout *buttonHLayout;

    QPushButton *startButton;
    QPushButton *resetButton;

    Projection *myProjection;

    QTimer* timer;
};
#endif // MAINWINDOW_H
