#pragma once
#include <memory>
#include <vector>
#include <string>

class Card;

class People
{
public:
	std::string name;
	explicit People(const std::string& name);
	void add_card(std::shared_ptr<Card> card);
	void show_card() const;
private:
	std::vector<std::shared_ptr<Card>> cards;
};

