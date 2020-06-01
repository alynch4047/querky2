#pragma once

#include <QTreeView>
#include <QList>
#include <QAbstractItemModel>
#include <QtAlgorithms>
#include <QObject>

#include "data.h"
#include "services.h"
#include "tree_data_model.h"


class TreeDataView: public QTreeView
{

public:
    TreeDataView(QWidget* parent, QList<QString> headers, Services* services) :
        QTreeView(parent), headers(headers), services(services), model(services->all_objects) {
        model.set_headers(headers);
        setModel(&model);
        selection_model = std::make_unique<QItemSelectionModel>(&model);
        setSelectionModel(selection_model.get());
    }

    TreeDataModel model;

    QList<QString> headers;

    std::unique_ptr<QItemSelectionModel> selection_model;

    void add_top_level_object(const IAdaptable* data);

    void refresh() { model.refresh(); }

    void clear() {
        model.clear();
    }

    Services* services;

};

