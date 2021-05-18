#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimplePandemicSimulation.h"

class SimplePandemicSimulation : public QMainWindow
{
    Q_OBJECT

public:
    SimplePandemicSimulation(QWidget *parent = Q_NULLPTR);

private:
    Ui::SimplePandemicSimulationClass ui;
};
