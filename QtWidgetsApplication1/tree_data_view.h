#pragma once

#include <QTreeView>
#include <QList>
#include <QAbstractItemModel>
#include <QtAlgorithms>

#include "data.h"
#include "services.h"


class TreeDataModel;

class Node {
public:
    const IAdaptable* data = nullptr;

    Node* parent = nullptr;

    Node() {};
    Node(const IAdaptable* data, Node* parent=nullptr) : data(data), parent(parent) {};

    QList<Node*> children;

    virtual ~Node() {
        qDeleteAll(children);
    }

    void add_child(const IAdaptable* data) {
        children.append(new Node(data, this));
    }

    void clear();

    void refresh(TreeDataModel& model);

    QList<const IAdaptable*> get_child_data();

};

class TreeDataModel : public QAbstractItemModel {
public:

    TreeDataModel(const QList<IAdaptable*>& objects) : root_node(new Node()) {
        headers = { "Name" }; 
    }

    Node* root_node;
    QList<QString> headers;

    void add_top_level_object(const IAdaptable* data);
    void add_child_data(Node* node, const IAdaptable* child_data);
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
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
};


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

