
#include <QDebug>

#include "tree_data_view.h"
#include "i_display.h"
#include "i_treedata.h"
#include "icon.h"
#include "adapt.h"

QList<const IAdaptable*> Node::get_child_data() {
    QList<const IAdaptable*> child_data_;
    for (Node* child_node : children) {
        child_data_.append(child_node->data);
    }
    return child_data_;
}

void Node::clear() {
    for (Node* child : children) { child->clear(); }
    qDeleteAll(children);
    children.clear();
}

void Node::refresh(TreeDataModel& model) {
    if (data != nullptr) {
        IAdaptable* data_ = const_cast<IAdaptable*>(data);
        ITreeData* i_tree_data = adapt<ITreeData>(data_);
        if (i_tree_data == nullptr) return;
        QList<IAdaptable*> new_children = i_tree_data->get_children();
        QList<const Node*> to_remove;
        QList<const IAdaptable*> to_add;
        // check for removed nodes
        for (const Node* child_node: children) {
            IAdaptable* child_data = const_cast<IAdaptable*>(child_node->data);
            if (new_children.indexOf(child_data) == -1) {
                // this node was removed
                to_remove.append(child_node);
            }
        }
        // check for added nodes
        QList<const IAdaptable*> child_data = get_child_data();
        for (const IAdaptable* new_child_data : new_children) {
            if (child_data.indexOf(new_child_data) == -1) {
                to_add.append(new_child_data);
            }
        }

        for (const IAdaptable* new_data : to_add) {
            model.add_child_data(this, new_data);
        }
    }
    for (Node* child : children) {
        child->refresh(model);
    }
}

void TreeDataModel::add_child_data(Node* node, const IAdaptable* child_data) {
    Node* parent_node = node->parent;
    if (parent_node == nullptr) {
        return;
    }
    
    int row = parent_node->children.indexOf(parent_node);
    QModelIndex parent_index = createIndex(row, 0, node);
    beginInsertRows(parent_index, 0, 0);
    node->children.insert(0, new Node(child_data, node));
    endInsertRows();
}

void TreeDataModel::add_top_level_object(const IAdaptable* data) {
    int row = root_node->children.size();
    QModelIndex root_index = QModelIndex();
    beginInsertRows(root_index, row, row);
    root_node->add_child(data);
    endInsertRows();
    refresh();
}

void TreeDataModel::clear() {
    beginResetModel();
    root_node->clear();
    endResetModel();
}

void TreeDataModel::refresh() {
    root_node->refresh(*this);
}

QModelIndex TreeDataModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node* parent_node;

    if (!parent.isValid())  parent_node = root_node;
    else parent_node = static_cast<Node*>(parent.internalPointer());

    Node* child_node = parent_node->children[row];
    if (child_node) return createIndex(row, column, child_node);
    return QModelIndex();
};

QModelIndex TreeDataModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) return QModelIndex();

    Node* child_node = static_cast<Node*>(index.internalPointer());
    Node* parent_node = child_node->parent;

    if (parent_node == root_node) return QModelIndex();

    int row = parent_node->children.indexOf(const_cast<Node*>(child_node));

    return createIndex(row, 0, parent_node);
};

int TreeDataModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        if (parent.column() > 0) return 0;
        Node* parent_node = static_cast<Node*>(parent.internalPointer());
        return parent_node->children.size();
        
    }
    else {
        return root_node->children.size();
    }
};

int TreeDataModel::columnCount(const QModelIndex& parent) const { return headers.size(); };

QVariant TreeDataModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];

    return QVariant();
}

void TreeDataModel::set_headers(QList<QString> headers) {
    this->headers = headers;
}

Qt::ItemFlags TreeDataModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() > 0) {
        ITreeData* i_tree_data = get_i_data<ITreeData>(index);
        if (i_tree_data->is_editable(index.column())) flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool TreeDataModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    
    ITreeData* i_tree_data = get_i_data<ITreeData>(index);
    qDebug() << "set data " << index << role << i_tree_data << value;
    if (role != Qt::EditRole || i_tree_data == nullptr) return false;
    return i_tree_data->set_data(index.column(), value);
}


QVariant TreeDataModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();
 
    ITreeData* i_tree_data = get_i_data<ITreeData>(index);
    if (i_tree_data == nullptr) return QVariant();
    IDisplay* i_display = get_i_data<IDisplay>(index);
    if (i_display == nullptr) return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return i_display->get_name();
        }
        else {
            return i_tree_data->data(index.column());
        }
    }
    else if (role == Qt::DecorationRole && index.column() == 0) {
        QString& icon_name = i_display->get_icon_name();
        if (icon_name == "") return QVariant();
        const QIcon& icon = get_icon(icon_name);
        return icon;
    }
    else {
        return QVariant();
    }
};

void TreeDataView::add_top_level_object(const IAdaptable* data) {
    model.add_top_level_object(data);
}
