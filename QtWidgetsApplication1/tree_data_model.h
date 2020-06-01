#pragma once

#include <QObject>
#include <QList>
#include <QString>
#include <QAbstractItemModel>

#include "adapt.h"
#include "data.h"
#include "node.h"


class TreeDataModel : public QAbstractItemModel {

    Q_OBJECT

public:

    TreeDataModel(const QList<IAdaptable*>& objects) : root_node(new Node()) {
        headers = { "Name" };
    }

    Node* root_node;
    QList<QString> headers;

    void add_top_level_object(const IAdaptable* data);
    void add_child_data(Node* node, const IAdaptable* child_data);
    void update_data(Node* node, const IAdaptable* child_data);
    void remove_child_node(Node* node, Node* child_node);
    const IAdaptable* get_data(QModelIndex index) {
        if (!index.isValid()) return nullptr;
        Node* node = static_cast<Node*>(index.internalPointer());
        return node->data;
    }
    template<typename Interface> Interface* get_i_data(const QModelIndex& index) const {
        Node* node = static_cast<Node*>(index.internalPointer());
        IAdaptable* data = const_cast<IAdaptable*>(node->data);
        return adapt<Interface>(data);
    }
    void refresh();
    void clear();
    void set_headers(QList<QString> headers);

    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex& child) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

signals:
    void data_changed();
};


