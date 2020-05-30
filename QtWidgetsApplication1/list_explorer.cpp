#include "list_explorer.h"


QModelIndex ListExplorerModel::index(int row, int column, const QModelIndex& parent) const {
    return createIndex(row, column);
};
QModelIndex ListExplorerModel::parent(const QModelIndex& child) const {
    return QModelIndex();
};
int ListExplorerModel::rowCount(const QModelIndex& parent) const {
    return objects->size();
};
int ListExplorerModel::columnCount(const QModelIndex& parent) const { return 1; };

QVariant ListExplorerModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    Data* data = (*objects)[index.row()];
    IDisplay* i_display = adapt<IDisplay>(data);

    if (role == Qt::DisplayRole) {
        return i_display->get_name();
    }
    else if (role == Qt::DecorationRole) {
        QString& icon_name = i_display->get_icon_name();
        const QIcon& icon = get_icon(icon_name);
        return icon;
    }
    else {
        return QVariant();
    }
};