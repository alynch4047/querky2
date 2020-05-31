#pragma once

#include <QDebug>

#include "tree_data_view.h"
#include "i_properties.h"
#include "adapt.h"

class PropertyView :
    public TreeDataView
{
public:

    PropertyView(QWidget* parent, QList<QString> headers, Services* services) :
        TreeDataView(parent, headers, services) {
        QObject::connect(&services->selection, &Selection::selectionChanged, this, &PropertyView::when_selection_changed);
    }

    QList<Property> current_properties;

    void when_selection_changed(const Data* selection) {
        qInfo() << "services selection changed " << selection->name;
        model.clear();

        Data* data = const_cast<Data*>(selection);
        //add_top_level_object(selection);

        IProperties* i_properties = adapt<IProperties>(data);
        if (i_properties == nullptr) return;
        // keep a copy of properties for lifetime of view
        current_properties = i_properties->get_properties();
        for (Property& property : current_properties) {
            add_top_level_object(&property);
        }
        
        refresh();
    }
};

