#include <iostream>
#include <vector>
#include <ctime>
#include <string>

class card {
	/* A single card.
	** Usage -----------------------------------------------------------
	** Card x = new Card(4,1);    // Ace of Spade
	** Card y = new Card(3,12);   // Jack of Heart
	** Suits -----------------------------------------------------------
	** suit[0]		| suit[1]	| suit[2]		| suit[3]
	** d - Diamonds	| c - Clubs	| h - Hearts	| s	- Spades
	** -----------------------------------------------------------------
	**/
public:
	const char suit[4] = { 'd', 'c', 'h', 's' };
	const std::string rank[14] = { "*", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	card(unsigned newSuit, unsigned newRank) {
		// Constructor
		// Stores the given details
		if (newRank == 0) {
			// If the card rank is 0, stores it as an ace
			cardRank = 13;
		} else {
			cardRank = newRank;
		}
		cardSuit = newSuit;
	};

	~card() {
		// Deconstructor. Not sure what to do with this
	};

	char getSuit() {
		return suit[cardSuit];
	};

	std::string getRank() {
		return rank[cardRank];
	}

	std::string cardString() {
		std::cout << cardRank << std::endl;
		std::string temp = getRank();
		temp += getSuit();
		return temp;
	}

private:
	unsigned cardSuit;
	unsigned cardRank;
};

class deck {
	// Made of 52 card entities
private:
	std::vector<card> deckOfCards;
	unsigned currentCard;
public:
	deck(){
		unsigned num = 0; // Card number
		// This controls the suit of the card
		for (unsigned i = 0; i <= 3; i++ ) {
			// Controls the rank of the card.
			for (unsigned n = 0; n <= 13; n++) {
				// Creates a new card for the deck
				deckOfCards.push_back(card(i, n));
				num++; // Increases card count
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
			//throw std::logic_error("Out of cards");
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
	card one(1, 12);
	std::string tempString = one.cardString();
	std::cout << tempString << std::endl;
	deck theDeck;
	card myCard = theDeck.deal();
	tempString = myCard.cardString();
	std::cout << tempString << std::endl;
	return 0;
}