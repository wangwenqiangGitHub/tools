#include <iostream>
#include "People.h"
#include "Card.h"
People ::People(const std::string &name)
    : name(name)
{
}

void People::add_card(std::shared_ptr<Card> card)
{
    cards.push_back(card);
}

void People::show_card() const
{
    std::cout << name << "has cards:\n";
    for (const auto &card : cards)
    {
        std::cout << "->" << card->number << "\n";
    }
}

