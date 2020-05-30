#pragma once

#include <string>
#include <QString>

struct Data {
    const static std::string data_type_id;
    virtual const std::string get_data_type_id() { return "DATA"; };

    QString name;
    Data(QString name) : name(name) {};
};

