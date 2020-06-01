#include "data.h"

const std::string IAdaptable::data_type_id = "DATA";

std::ostream& operator<<(std::ostream& os, const IAdaptable& data)
{
    os << "ADAPTABLE";
    return os;
}