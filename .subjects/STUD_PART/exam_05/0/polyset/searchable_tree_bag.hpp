#pragma once

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

// searchable_tree_bag hérite à la fois de tree_bag (stockage en arbre BST)
// et de searchable_bag (capacité de recherche).
// Elle n'a besoin d'implémenter que has(), car toutes les autres méthodes
// viennent de tree_bag.
class searchable_tree_bag : public tree_bag, public searchable_bag
{
    private:
        // Fonction récursive qui parcourt le BST depuis un nœud donné.
        bool search_in_subtree(node* current_node, int target_value) const;

    public:
        searchable_tree_bag();
        searchable_tree_bag(const searchable_tree_bag& source);
        searchable_tree_bag& operator=(const searchable_tree_bag& source);
        ~searchable_tree_bag();

        bool has(int target_value) const;
};
