#include "book.h"

const std::string Book::data_type_id = "BOOK";

std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << &book.name;
    return os;
}

