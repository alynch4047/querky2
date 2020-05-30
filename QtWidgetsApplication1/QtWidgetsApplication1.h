#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "services.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

    void create_docks(Services* services);

public slots:
    void testSlot();

private:
    Ui::QtWidgetsApplication1Class ui;
};
