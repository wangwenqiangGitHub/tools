#include "People.h"
#include "Card.h"
#include <memory>

int main(int argc, char *argv[])
{
	auto alice = std::make_shared<People>("Alice");

	auto card1= std::make_shared<Card>("622-1234", alice);
	auto card2= std::make_shared<Card>("622-5678", alice);

	alice->add_card(card1);
	alice->add_card(card2);

	alice->show_card();
	card1->show_ower();
	card2->show_ower();

	return 0;
}
