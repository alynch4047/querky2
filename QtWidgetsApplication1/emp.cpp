#include "emp.h"

const std::string Emp::data_type_id = "EMP";

std::ostream& operator<<(std::ostream& os, const Emp& emp)
{
    os << &emp.name;
    return os;
}
