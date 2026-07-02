#include "searchable_bag.hpp"

// set encapsule un searchable_bag par référence et garantit l'unicité :
// chaque valeur ne peut être insérée qu'une seule fois.
// Il délègue toutes les opérations de stockage au bag sous-jacent.
class set
{
    private:
        searchable_bag& bag;

    public:
        // Un set doit toujours encapsuler un bag existant — pas de construction par défaut.
        set() = delete;
        set(const set& source) = delete;
        set& operator=(const set& source) = delete;

        set(searchable_bag& underlying_bag);
        ~set();

        bool has(int value) const;
        void insert(int value);
        void insert(int* values, int count);
        void print() const;
        void clear();

        const searchable_bag& get_bag();
};
