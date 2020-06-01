
#include <QDebug>

#include "tree_data_view.h"
#include "i_display.h"
#include "i_treedata.h"
#include "icon.h"
#include "adapt.h"
#include "data.h"


void TreeDataView::add_top_level_object(const IAdaptable* data) {
    model.add_top_level_object(data);
}
