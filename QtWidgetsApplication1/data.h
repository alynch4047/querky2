#pragma once

#include <string>
#include <QString>

struct IAdaptable {
    const static std::string data_type_id;
    virtual const std::string get_data_type_id() { return "ADAPTABLE"; };
};

