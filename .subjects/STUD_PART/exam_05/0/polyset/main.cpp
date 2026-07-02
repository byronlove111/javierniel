#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"


#include <iostream>

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	searchable_bag *t = new searchable_tree_bag;
	searchable_bag *a = new searchable_array_bag;

	for (int i = 1; i < argc; i++) {
		t->insert(atoi(argv[i]));
		a->insert(atoi(argv[i]));
	}
	t->print();
	a->print();

	for (int i = 1; i < argc; i++)
	{
		std::cout << t->has(atoi(argv[i])) << std::endl;
		std::cout << a->has(atoi(argv[i])) << std::endl;
		std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
		std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
	}

	t->clear();
	a->clear();

	const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
	tmp.print();
	tmp.has(1);

	set sa(*a);
	set st(*t);
	for (int i = 1; i < argc; i++)
	{
		st.insert(atoi(argv[i]));
		sa.insert(atoi(argv[i]));

		sa.has(atoi(argv[i]));
		sa.print();
		sa.get_bag().print();
		st.print();
		sa.clear();
		sa.insert((int[]){ 1, 2, 3, 4, }, 4);
		std::cout << std::endl;
	}

	// --- test d'unicité explicite : un set ne doit pas stocker les doublons ---
	searchable_array_bag uniq_a;
	set su_a(uniq_a);
	su_a.insert(42);
	su_a.insert(42);
	su_a.insert(42);
	std::cout << "unique array: ";
	su_a.print();                    // doit afficher 42 une seule fois

	searchable_tree_bag uniq_t;
	set su_t(uniq_t);
	su_t.insert(7);
	su_t.insert(7);
	su_t.insert(7);
	std::cout << "unique tree: ";
	su_t.print();                    // doit afficher 7 une seule fois

	// --- test clear puis has ---
	searchable_array_bag clr_bag;
	set sc(clr_bag);
	sc.insert(99);
	sc.clear();
	std::cout << "after clear has(99): " << sc.has(99) << std::endl; // doit afficher 0

	// --- test bulk insert ---
	searchable_array_bag blk_bag;
	set sb(blk_bag);
	int bulk[] = {10, 20, 30, 10};  // 10 en double
	sb.insert(bulk, 4);
	std::cout << "bulk has(10): " << sb.has(10) << std::endl;  // 1
	std::cout << "bulk has(20): " << sb.has(20) << std::endl;  // 1
	std::cout << "bulk has(99): " << sb.has(99) << std::endl;  // 0

	return (0);
}
