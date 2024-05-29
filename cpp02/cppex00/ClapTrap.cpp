#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("ClapTrap"), hitpoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << name << " is created" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitpoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << name << " is created" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << name << " is destroyed" << std::endl;
}

/* don't forget attack damge variable */

int check_energy(int energyPoints)
{
    if (energyPoints == 0)
        return (std::cout << "\033[31mClapTrap default is not able to repair itself, because he doesn't have enough energy points.\033[0m" << std::endl, 0);
    return 1;
}

int check_hitpoints_repair(int hitpoints, std::string name, int mount)
{
    (void)mount;
    (void)name;
    if (hitpoints == 0)
        return (std::cout << "\033[31mClapTrap default is not able to repair itself, because he doesn't have enough hit points\033[0m" << std::endl, 0);
    if (hitpoints == 10)
        return (std::cout << "\033[31mClapTrap default is not able to repair itself, because he is already at full health.\033[0m" << std::endl, 0);
    return 1;
}

int check_hitpoints(int hitpoints, std::string name, int flag, int mount)
{
    (void)mount;
    if (flag && hitpoints == 10)
        return (std::cout << "ClapTrap " << name << " is already at full health!" << std::endl, 0);
    if (hitpoints == 0)
        return (std::cout << "\033[33mClapTrap default is already dead, stop beating it.\033[0m" << std::endl, 0);
    return 1;
}
void ClapTrap::attack(std::string const &target)
{
    if (check_energy(energyPoints) == 0)
        return;
    if (hitpoints == 0)
        return (std::cout << "\033[31mClapTrap " << target << " is not able to attack, because he doesn't have enough hit points.\033[0m" << std::endl, void());
    energyPoints--;
    std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
    attackDamage++;
}
void ClapTrap::takeDamage(unsigned int amount)
{

    if (check_hitpoints(hitpoints, name, 0, amount) == 0)
        return;
    if (check_energy(energyPoints) == 0)
        return;
    hitpoints -= amount;
    if (hitpoints < 0)
        hitpoints = 0;
    std::cout << "ClapTrap default was attacked and lost " << amount << " hit points, he now has " << hitpoints << " hit points." << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (check_hitpoints_repair(hitpoints, name, amount) == 0)
        return;
    if (check_energy(energyPoints) == 0)
        return;
    if (energyPoints >= 10)
        return (std::cout << "ClapTrap " << name << " is already at full energy!" << std::endl, void());
    energyPoints++;
    hitpoints += amount;
    std::cout << "ClapTrap " << name << " is repaired for " << amount << " points!" << std::endl;
}