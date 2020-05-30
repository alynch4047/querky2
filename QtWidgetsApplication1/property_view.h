#pragma once

#include <QDebug>

#include "tree_data_view.h"
#include "i_properties.h"

class PropertyView :
    public TreeDataView
{
public:

    PropertyView(QWidget* parent, QList<QString> headers, Services* services) :
        TreeDataView(parent, headers, services) {
        QObject::connect(&services->selection, &Selection::selectionChanged, this, &PropertyView::when_selection_changed);
    }

    void when_selection_changed(const Data* selection) {
        qInfo() << "services selection changed " << selection->name;
        model.clear();

        Data* data = const_cast<Data*>(selection);
        IProperties* i_tree_data = adapt<IProperties>(data);
        for (Property property : i_tree_data->get_properties()) {
            add_top_level_object(property);
        }

        
        refresh();
    }
};

