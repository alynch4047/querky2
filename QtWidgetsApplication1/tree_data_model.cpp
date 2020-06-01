
#include <QDebug>

#include "tree_data_model.h"
#include "tree_data_view.h"
#include "i_display.h"
#include "i_treedata.h"
#include "icon.h"

void TreeDataModel::remove_child_node(Node* parent_node, Node* child_node) {
    if (parent_node == root_node) {
        return;
    }

    int row = parent_node->children.indexOf(child_node);
    QModelIndex parent_index = createIndex(row, 0, parent_node);
    beginRemoveRows(parent_index, row, row);
    parent_node->children.removeOne(child_node);
    endRemoveRows();
}

void TreeDataModel::update_data(Node* parent_node, const IAdaptable* child_data) {
    IAdaptable* ia = const_cast<IAdaptable*>(child_data);
    QString name = adapt<IDisplay>(ia)->get_name();
    qDebug() << "update model data" << name << '\n';
    for (int row = 0; row < parent_node->children.size(); ++row) {
        if (parent_node->children[row]->data == child_data) {
            for (int col_no = 0; col_no < columnCount(); ++col_no) {
                QModelIndex index = createIndex(row, col_no, parent_node->children[row]);
                emit dataChanged(index, index);
            }
            break;
        }
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
    qDebug() << "tree model refresh\n";
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
    emit data_changed();
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
