#pragma once

#include <QList>
#include <QVariant>

#include "data.h"


struct ITreeData {

    ITreeData() {};
    virtual QList<Data*> get_children() const = 0;
    virtual QVariant data(int column) const = 0;
};
