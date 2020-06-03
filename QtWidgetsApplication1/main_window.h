#pragma once

#include <QtWidgets/QMainWindow>

#include "services.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    void create_docks(Services* services);

};
