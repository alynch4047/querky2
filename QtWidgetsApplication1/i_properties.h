#pragma once

#include <memory>

#include <QString>
#include <QList>

#include "data.h"
#include "adapt.h"
#include "i_display.h"
#include "i_treedata.h"
#include "plugin.h"


class Property: public IAdaptable {
public:

    const static std::string data_type_id;
    virtual const std::string get_data_type_id() override { return "PROPERTY"; };

    QString name;
    QString val;

   Property(const QString& name, QString& val) : name(name), val(val) {};
   /* Property(const Property& property) : name(property.name), val(property.val) {};
    Property& operator= (const Property& property) {
        name = property.name;
        val = property.val;
    }*/
};

struct PropertyToIDisplay : Adapter<Property, IDisplay> {
    virtual QString get_name() const override { return adaptee->name; };
    virtual QString get_icon_name() const override { return ""; };
};

struct PropertyToITreeData : Adapter<Property, ITreeData> {
    virtual QList<IAdaptable*> get_children() const {
        QList<IAdaptable*> children;
        return children;
    };
    virtual QVariant data(int column) const {
        if (column == 1) return adaptee->val;
        else return "TBD";
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
