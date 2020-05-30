#pragma once

#include <QString>


struct IDisplay {

    IDisplay() {};
    virtual QString get_name() const = 0;
    virtual QString get_icon_name() const = 0;
};
