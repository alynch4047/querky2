#pragma once

#include <QDebug>

#include "tree_data_view.h"

class TreeExplorer :
    public TreeDataView
{
public:
    TreeExplorer(QWidget* parent, QList<QString> headers, Services* services) :
        TreeDataView(parent, headers, services) {
        QObject::connect(selection_model.get(), &QItemSelectionModel::selectionChanged, this, &TreeExplorer::when_selection_changed);
    }

    void when_selection_changed(const QItemSelection& selected, const QItemSelection& deselected) {
        QModelIndex index = selected.indexes()[0];
        const IAdaptable* data = model.get_data(index);
        if (data == nullptr) qInfo() << "null data selected";
        else {
            qInfo() << "selection changed " ;
            services->selection.set_selection(data);
        }
    };
};

