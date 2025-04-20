#include "Card.h"
#include "People.h"
#include <iostream>
#include <memory>

Card::Card(const std::string &num, std::shared_ptr<People> owner)
    : number(num)
    , owner(owner)
{
}

void Card::show_ower() const
{
    if (auto sp = owner.lock())
    {
        std::cout << "Card" << number
                  << "belongs to " << sp->name << "\n";
    }
    else
    {
        std::cout << "Card" << number << "has no valid owner\n";
    }
}
