#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& source)
    : tree_bag(source)
{
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& source)
{
    if (this != &source)
        tree_bag::operator=(source);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag()
{
}

// Recherche récursive dans le BST.
// Comme les valeurs sont insérées en ordre BST (gauche < nœud < droite),
// on peut éliminer la moitié de l'arbre à chaque étape.
bool searchable_tree_bag::search_in_subtree(node* current_node, int target_value) const
{
    if (current_node == nullptr)
        return false;

    if (current_node->value == target_value)
        return true;

    if (target_value < current_node->value)
    {
        bool found_in_left = search_in_subtree(current_node->l, target_value);
        return found_in_left;
    }

    bool found_in_right = search_in_subtree(current_node->r, target_value);
    return found_in_right;
}

bool searchable_tree_bag::has(int target_value) const
{
    bool found = search_in_subtree(this->tree, target_value);
    return found;
}
