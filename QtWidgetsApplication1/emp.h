#pragma once

#include <QString>
#include <QList>

#include "adapt.h"
#include "plugin.h"
#include "data.h"
#include "book.h"

#include "i_properties.h"
#include "i_display.h"
#include "i_treedata.h"


class Emp : public IAdaptable {
public:
    const static std::string data_type_id;
    virtual const std::string get_data_type_id() override { return Emp::data_type_id; };
    Emp(QString name, int salary) : name(name), salary(salary) {};

    QString name;
    int salary;
    QList<Book*> books;
};


struct EmpToIProperties : Adapter<Emp, IProperties> {
    QList<std::shared_ptr<Property>> get_properties() const override {
        return { std::make_shared<Property>("name", [this]() {return adaptee->name; }, [this](QVariant v) {adaptee->name = v.toString(); }) };
    }
};

struct EmpToIDisplay : Adapter<Emp, IDisplay> {
    virtual QString get_name() const override { return adaptee->name; };
    virtual QString get_icon_name() const override { return "006-monkey.png"; };
};

struct EmpToITreeData : Adapter<Emp, ITreeData> {
    virtual QList<IAdaptable*> get_children() const {
        QList<IAdaptable*> children;
        for (auto* book : adaptee->books) {
            children.append(book);
        }
        return children;
    }
    virtual QVariant data(int column) const { return adaptee->salary; }
    virtual bool is_editable(int column) const { return false; }
    virtual bool set_data(int column, QVariant value) const { return false; };
};


struct EmpPlugin : public Plugin {
    void register_adapters() {
        register_adapter<EmpToIProperties>();
        register_adapter<EmpToIDisplay>();
        register_adapter<EmpToITreeData>();
    }
};
