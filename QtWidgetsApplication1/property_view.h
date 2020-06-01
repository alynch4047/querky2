#pragma once

#include <QDebug>

#include "tree_data_view.h"
#include "i_properties.h"
#include "adapt.h"

class PropertyView :
    public TreeDataView
{
    Q_OBJECT

public:

    PropertyView(QWidget* parent, QList<QString> headers, Services* services) :
        TreeDataView(parent, headers, services) {
        QObject::connect(&services->selection, &Selection::selectionChanged, this, &PropertyView::when_selection_changed);
        QObject::connect(this, &PropertyView::data_changed, this->services, &Services::data_changed);
        QObject::connect(&model, &TreeDataModel::data_changed, this, &PropertyView::data_changed);
    }

    QList<std::shared_ptr<Property>> current_properties;

    void when_selection_changed(const IAdaptable* selection) {
        qInfo() << "services selection changed ";
        model.clear();

        IAdaptable* data = const_cast<IAdaptable*>(selection);

        IProperties* i_properties = adapt<IProperties>(data);
        if (i_properties == nullptr) return;
        // keep a copy of QList for lifetime of view
        current_properties = i_properties->get_properties();
        for (auto& property : current_properties) {
            add_top_level_object(property.get());
        }
        
        refresh();

    }

signals:
    void data_changed();
};

