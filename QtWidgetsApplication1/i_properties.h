#pragma once

#include <QString>
#include <QList>


class Property {
public:
    QString name;
    QString& val;

    Property(const QString& name, QString& val) : name(name), val(val) {};
};


struct IProperties {

    IProperties() {};
    virtual QList<Property> get_properties() const = 0;
};
