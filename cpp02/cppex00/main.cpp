#include "ClapTrap.hpp"
/*
int main()
{
    ClapTrap claptrap("Claptrap");

    claptrap.attack("Jack");
    claptrap.takeDamage(5);
    claptrap.beRepaired(10);
    return 0;
}*/



int main()
{
	std::cout << "### TESTING CLAPTRAP ###\n" << std::endl;
	{
		std::cout << "\033[34mConstructing\033[0m" << std::endl;
		ClapTrap a;
		ClapTrap b("Cody");

		std::cout << "\033[34mTesting\033[0m" << std::endl;
		a.attack("some other robot");
		a.takeDamage(7);
		a.takeDamage(10);
        printf("i am here\n");
		a.beRepaired(5);
		a.attack("some other other robot");
		b.beRepaired(3);
		for (int i = 0; i < 12; i++)
			b.attack("Cody-clone");
		b.beRepaired(3);
		std::cout << "\033[34mDeconstructing\033[0m" << std::endl;
	}
	return (0);
}