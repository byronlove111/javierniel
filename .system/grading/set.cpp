#include "set.hpp"
#include "searchable_array_bag.hpp"

set::set(searchable_bag& underlying_bag) : bag(underlying_bag)
{
}

set::~set()
{
}

bool set::has(int value) const
{
    bool found = bag.has(value);
    return found;
}

// N'insère la valeur que si elle n'est pas déjà présente dans le bag.
void set::insert(int value)
{
    bool already_present = this->has(value);
    if (!already_present)
        bag.insert(value);
}

// Insère chaque élément du tableau, en ignorant les doublons.
void set::insert(int* values, int count)
{
    for (int i = 0; i < count; i++)
        this->insert(values[i]);
}

void set::print() const
{
    bag.print();
}

void set::clear()
{
    bag.clear();
}

const searchable_bag& set::get_bag()
{
    return this->bag;
}
