#pragma once

#include <QList>
#include <QVariant>

#include "data.h"


struct ITreeData {

    ITreeData() {};
    virtual QList<IAdaptable*> get_children() const = 0;
    virtual QVariant data(int column) const = 0;
    virtual bool is_editable(int column) const = 0;
};
