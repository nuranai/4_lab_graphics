#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{   
    myProjection = new Projection();

    generalVLayout = new QVBoxLayout();
    buttonHLayout = new QHBoxLayout();

    startButton = new QPushButton("start");
    resetButton = new QPushButton("reset");

    //buttonHLayout->addWidget(startButton);
    //buttonHLayout->addWidget(resetButton);

    generalVLayout->addWidget(myProjection);
    generalVLayout->addLayout(buttonHLayout);

    setLayout(generalVLayout);

    //update();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), myProjection, SLOT(newFrame()));


    timer->start(50);


    //connect(resetButton, SIGNAL(clicked()), myProjection, SLOT(reset()));
}

MainWindow::~MainWindow()
{
}

