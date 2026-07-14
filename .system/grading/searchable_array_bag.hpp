#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

// searchable_array_bag hérite à la fois de array_bag (stockage tableau)
// et de searchable_bag (capacité de recherche).
// Elle n'a besoin d'implémenter que has(), car toutes les autres méthodes
// viennent de array_bag.
class searchable_array_bag : public array_bag, public searchable_bag
{
    public:
        searchable_array_bag();
        searchable_array_bag(const searchable_array_bag& source);
        searchable_array_bag& operator=(const searchable_array_bag& source);
        ~searchable_array_bag();

        bool has(int target_value) const;
};
