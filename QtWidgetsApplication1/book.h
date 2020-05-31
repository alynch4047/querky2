#pragma once

#include <QString>
#include <QList>

#include "data.h"
#include "i_properties.h"
#include "i_display.h"
#include "i_treedata.h"
#include "plugin.h"

class Book : public Data {
public:
    const static std::string data_type_id;
    virtual const std::string get_data_type_id() override { return "BOOK"; };
    Book(QString name, QString author, int num_pages) : Data(name), author(author), num_pages(num_pages) {};

    QString author;
    int num_pages;
};

struct BookToIProperties : Adapter<Book, IProperties> {
    QList<std::shared_ptr<Property>> get_properties() const override {
            return {
                std::make_shared<Property>("name", adaptee->name), 
                std::make_shared<Property>("author", adaptee->author) 
            };
    };
};

struct BookToIDisplay : Adapter<Book, IDisplay> {
    virtual QString get_name() const override { return adaptee->name; };
    virtual QString get_icon_name() const override { return "019-compass.png"; };
};

struct BookToITreeData : Adapter<Book, ITreeData> {
    virtual QList<Data*> get_children() const {
        QList<Data*> children;
        return children;
    };
    virtual QVariant data(int column) const { return "TBD"; };
};

struct BookPlugin : public Plugin {
    void register_adapters() {
        register_adapter<BookToIProperties>();
        register_adapter<BookToIDisplay>();
        register_adapter<BookToITreeData>();
    }
};

