#pragma once

#include <iostream>

#include <QString>
#include <QList>

#include "data.h"
#include "i_properties.h"
#include "i_display.h"
#include "i_treedata.h"
#include "plugin.h"

class Book : public IAdaptable {
public:
    const static std::string data_type_id;
    virtual const std::string get_data_type_id() override { return "BOOK"; };
    Book(QString name, QString author, int num_pages) : name(name), author(author), num_pages(num_pages) {};

    QString name;
    QString author;
    int num_pages;
};


struct BookToIProperties : Adapter<Book, IProperties> {
    QList<std::shared_ptr<Property>> get_properties() const override {
            return {
                std::make_shared<Property>("name",
                [this]() {return adaptee->name; },
                [this](QVariant v) {adaptee->name = v.toString(); }) ,
                std::make_shared<Property>("author",
                [this]() {return adaptee->author; },
                [this](QVariant v) {adaptee->author = v.toString(); }),
                std::make_shared<Property>("pages",
                [this]() {return adaptee->num_pages; },
                [this](QVariant v) {adaptee->num_pages = v.toInt(); })
            };
    }
};

struct BookToIDisplay : Adapter<Book, IDisplay> {
    virtual QString get_name() const override { return adaptee->name; }
    virtual QString get_icon_name() const override { return "019-compass.png"; }
};

struct BookToITreeData : Adapter<Book, ITreeData> {
    virtual QList<IAdaptable*> get_children() const {
        QList<IAdaptable*> children;
        return children;
    }
    virtual QVariant data(int column) const { return "TBD"; }
    virtual bool is_editable(int column) const { return false; }
    virtual bool set_data(int column, QVariant value) const { return false; };
};

struct BookPlugin : public Plugin {
    void register_adapters() {
        register_adapter<BookToIProperties>();
        register_adapter<BookToIDisplay>();
        register_adapter<BookToITreeData>();
    }
};

