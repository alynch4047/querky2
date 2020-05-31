#pragma once

#include <QListView>
#include <QAbstractItemModel>

#include "services.h"
#include "i_display.h"
#include "adapt.h"
#include "icon.h"

class ListExplorerModel : public QAbstractItemModel {
public:

    ListExplorerModel(const QList<IAdaptable*>* objects) : objects(objects) {};

    const QList<IAdaptable*>* objects;

    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex& child) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

class ListExplorer : public QListView
{
public:
    ListExplorer(QWidget* parent, Services* services) : QListView(parent), services(services), model(&services->all_objects) {
        setModel(&model);
    }

    ListExplorerModel model;

    Services* services;
};

