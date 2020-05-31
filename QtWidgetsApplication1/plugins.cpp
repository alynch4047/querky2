
#include <iostream>
#include <string>
#include <vector>

#include<QList>

#include "adapt.h"
#include "book.h"
#include "i_properties.h"
#include "emp.h"
#include "plugins.h"


QList<Data*> make_data() {

    Emp* e1 = new Emp{ "jim", 5000 };
    Emp* e2 = new Emp{ "paul", 2000 };
    Book* b1 = new Book{ "ulysses", "joyce", 421 };
    Book* b2 = new Book{ "the dubliners", "joyce", 201 };

    e1->books.append(b1);
    e1->books.append(b2);

    QList<Data*> data = QList<Data*>();
    data.push_back(e1);
    data.push_back(b1);
    data.push_back(e2);

    return data;
};

void load_plugins()
{
    std::vector<Plugin*> plugins;
    plugins.push_back(new EmpPlugin());
    plugins.push_back(new BookPlugin());
    plugins.push_back(new PropertyPlugin());

    for (auto plugin : plugins) {
        plugin->register_adapters();
    }

}

