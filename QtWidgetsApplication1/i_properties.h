#pragma once

#include <memory>
#include <functional>

#include <QString>
#include <QList>
#include <QDebug>

#include "data.h"
#include "adapt.h"
#include "i_display.h"
#include "i_treedata.h"
#include "plugin.h"


class Property: public IAdaptable {
public:

    const static std::string data_type_id;
    virtual const std::string get_data_type_id() override { return Property::data_type_id; };

    QString name;
    std::function<QVariant()> getter;
    std::function<void(QVariant)> setter;

   Property(const QString& name, 
       std::function<QVariant()> getter,
       std::function<void(QVariant)> setter) : name(name), getter(getter), setter(setter) {};

};

struct PropertyToIDisplay : Adapter<Property, IDisplay> {
    virtual QString get_name() const override { return adaptee->name; };
    virtual QString get_icon_name() const override { return ""; };
};

struct PropertyToITreeData : Adapter<Property, ITreeData> {
    virtual QList<IAdaptable*> get_children() const {
        QList<IAdaptable*> children;
        return children;
    }
    virtual QVariant data(int column) const {
        if (column == 1) return adaptee->getter();
        else return "TBD";
    }
    virtual bool is_editable(int column) const { return true; }
    virtual bool set_data(int column, QVariant value) const { 
        adaptee->setter(value);
        return true;
    };
};

struct IProperties {

    IProperties() {};
    virtual QList<std::shared_ptr<Property>> get_properties() const = 0;
};

struct PropertyPlugin : public Plugin {
    void register_adapters() {
        register_adapter<PropertyToIDisplay>();
        register_adapter<PropertyToITreeData>();
    }
};
