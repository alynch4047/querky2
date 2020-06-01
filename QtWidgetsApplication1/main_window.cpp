
#include "main_window.h"

#include <QObject>
#include <QString>
#include <QtWidgets>
#include <QList>

#include "plugins.h"
#include "data.h"
#include "adapt.h"
#include "i_properties.h"
#include "services.h"
#include "list_explorer.h"
#include "property_view.h"
#include "tree_explorer.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);

    load_plugins();

    // load initial data
    QList<IAdaptable*> data = make_data();
    for (IAdaptable* d : data) {
        services.all_objects.append(d);
    };

    create_docks(&services);

}


void MainWindow::create_docks(Services* services) {

    QDockWidget* dock = new QDockWidget("List Explorer", this);
    ListExplorer* list_explorer = new ListExplorer(dock, services);
    dock->setWidget(list_explorer);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    dock = new QDockWidget("Tree Explorer", this);
    TreeExplorer* tree_explorer = new TreeExplorer(dock, { "Data", "Detail" }, services);

    for (const auto* data : services->all_objects) {
        tree_explorer->add_top_level_object(data);
    }
    dock->setWidget(tree_explorer);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    dock = new QDockWidget("Properties", this);
    PropertyView* properties = new PropertyView(dock, {"Name", "Value"}, services);
    dock->setWidget(properties);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}



