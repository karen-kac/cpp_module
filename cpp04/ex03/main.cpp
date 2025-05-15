#include <iostream>
#include "AMateria.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"

int main()
{
	std::cout << "=== STEP 1: Create source and learn materia ===" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	// 4つ以上学習しないことの確認
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice()); // ←追加されないはず

	std::cout << "\n=== STEP 2: Create characters ===" << std::endl;
	ICharacter* me = new Character("me");
	ICharacter* bob = new Character("bob");

	std::cout << "\n=== STEP 3: Create and equip materia ===" << std::endl;
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	// 存在しないタイプを作成
	tmp = src->createMateria("fire");
	if (!tmp)
		std::cout << "[INFO] Unknown materia type 'fire' was not created.\n";

	std::cout << "\n=== STEP 4: Equip more materias to test max slots ===" << std::endl;
	me->equip(src->createMateria("ice"));
	me->equip(src->createMateria("cure"));
	me->equip(src->createMateria("ice")); // 5つ目 → 無視される

	std::cout << "\n=== STEP 5: Use materias ===" << std::endl;
	me->use(0, *bob); // ice
	me->use(1, *bob); // cure
	me->use(2, *bob); // ice
	me->use(3, *bob); // cure
	me->use(4, *bob); // 無効なスロット

	std::cout << "\n=== STEP 6: Unequip and test slot clearing ===" << std::endl;
	me->unequip(1);
	me->use(1, *bob); // 何も起きないはず

	std::cout << "\n=== STEP 7: Copy character and use copy ===" << std::endl;
	Character copy = *(dynamic_cast<Character*>(me));
	copy.use(0, *bob); // copyが正しく使えるか確認

	std::cout << "\n=== STEP 8: Clean up ===" << std::endl;
	delete bob;
	delete me;
	delete src;

	std::cout << "[INFO] All dynamic memory freed.\n";

	return 0;
}


// int main()
// {
// 	IMateriaSource* src = new MateriaSource();
// 	src->learnMateria(new Ice());
// 	src->learnMateria(new Cure());
// 	ICharacter* me = new Character("me");
// 	AMateria* tmp;
// 	tmp = src->createMateria("ice");
// 	me->equip(tmp);
// 	tmp = src->createMateria("cure");
// 	me->equip(tmp);
// 	ICharacter* bob = new Character("bob");
// 	me->use(0, *bob);
// 	me->use(1, *bob);
// 	delete bob;
// 	delete me;
// 	delete src;
// 	return 0;
// }
