#pragma once

#include <QList>
#include <QtAlgorithms>

#include "data.h"

class TreeDataModel;

class Node {

public:
    const IAdaptable* data = nullptr;

    Node* parent = nullptr;

    Node() {};
    Node(const IAdaptable* data, Node* parent = nullptr) : data(data), parent(parent) {};

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