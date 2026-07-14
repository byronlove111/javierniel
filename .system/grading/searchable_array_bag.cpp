#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag& source)
    : array_bag(source)
{
}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
    if (this != &source)
        array_bag::operator=(source);
    return *this;
}

searchable_array_bag::~searchable_array_bag()
{
}

// Parcours linéaire du tableau interne pour trouver target_value.
bool searchable_array_bag::has(int target_value) const
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i] == target_value)
            return true;
    }
    return false;
}
