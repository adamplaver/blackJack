#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <stdexcept>

struct card {
	int value;
};

class deck {
	// Made of 52 card entities
private:
	std::vector<card> deckOfCards;
	unsigned currentCard;
public:
	deck() {
		unsigned num = 0; // Card number
						  // This controls the suit of the card
		for (unsigned i = 0; i < 4; i++) {
			// Controls the rank of the card.
			for (unsigned n = 1; n < 14; n++) {
				// Creates a new card for the deck
				card tempCard;
				tempCard.value = n;
				deckOfCards.push_back(tempCard);
				//num++; // Increases card count
			}
		}
		currentCard = 0;
	}

	card deal() {
		// Out of bounds check
		if (currentCard <= 52) {
			currentCard++;
			return deckOfCards[currentCard - 1];
		} else {
			// oh no
			throw std::logic_error("Out of cards");
			card tempCard;
			tempCard.value = 0;
			return tempCard;
		}
	}
};

class chips {
	// Betting
public:
private:
	int houseMoney, userMoney;
};

int main() {
	// Tests the card class.
	deck theDeck;
	card tempCard = theDeck.deal();
	std::cout << tempCard.value << std::endl;
	return 0;
}