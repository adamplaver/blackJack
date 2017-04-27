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
			//std::cout << "Dealing..." << std::endl;
			card tempCard = deckOfCards[currentCard];
			currentCard++;
			return tempCard;
		} else {
			// oh no
			throw std::logic_error("Out of cards");
			card tempCard;
			tempCard.value = 0;
			return tempCard;
		}
	}
	
	void shuffleDeck() {
		card tempCard;
		//std::cout << "Shuffling";
		for (int k = 0; k <= 52; k++) {
			unsigned i = rand()%52 + 1; // Picks a card from deck
			// Swap the two cards
			//if (k % 2 == 0) { std::cout << "."; }
			tempCard = deckOfCards[k];
			deckOfCards[k].value = deckOfCards[i].value;
			deckOfCards[i].value = tempCard.value;
		}
		//std::cout << std::endl;
		currentCard = 0; // Reset current card to top of deck
		return;
	}
};

class chips {
	// Betting
public:
private:
	int houseMoney, userMoney;
};

int main() {
	srand(time(NULL)); // Generates a random seed for shuffle function.

	/* This tests the card struct and the deck function
	card tempCard = theDeck.deal();
	std::cout << tempCard.value << std::endl;
	tempCard = theDeck.deal();
	std::cout << tempCard.value << std::endl;
	theDeck.shuffleDeck();
	tempCard = theDeck.deal();
	std::cout << tempCard.value << std::endl;
	*/

	std::cout << "\n";
	std::cout << "/~~~~~~~~~~~~~~~~~~  Blackjack  ~~~~~~~~~~~~~~~~~~/" << std::endl;
	std::cout << "/                                                 /" << std::endl;
	std::cout << "/Rules ___________________________________________/" << std::endl;
	std::cout << "1. Dealer stands above 16\n";
	std::cout << "2. Aces are worth 11 or 1.\n\n\n";

	const char ranks[14] = {'*', 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
	bool playing = true;	// Loop toggler
	deck theDeck;	// Intializes the deck
	theDeck.shuffleDeck(); // Shuffles the deck
	
	while (playing) {

		card dealerCard = theDeck.deal();
		card dealerCard2 = theDeck.deal();
		card yourCard = theDeck.deal();
		card yourCard2 = theDeck.deal();

		int dealerSum = dealerCard.value + dealerCard2.value;
		int sum = yourCard.value + yourCard2.value;

		// Face cards are only worth 10.
		if (yourCard2.value >= 11) {
			sum = yourCard.value + 10;
		}
		else if (yourCard.value >= 11) {
			sum = yourCard2.value + 10;
		}

		if (dealerCard.value >= 11) {
			dealerSum = yourCard.value + 10;
		}
		else if (dealerCard2.value >= 11) {
			dealerSum = dealerCard2.value + 10;
		}


		if (yourCard.value == 1 || yourCard2.value == 1) {
			// Ace detection
			std::cout << "Your cards are: " << ranks[yourCard.value] << " and " << ranks[yourCard2.value] << std::endl;
			std::cout << "You were dealt an ace. What would you like your ace to be? (1) or (11)?\n";
			if (yourCard.value == 1) {
				std::cin >> yourCard.value;
				std::cout << "Your cards are: " << 'A' << " and " << ranks[yourCard2.value] << std::endl;
			} else {
				std::cin >> yourCard2.value;
				std::cout << "Your cards are: " << ranks[yourCard.value] << " and " << 'A' << std::endl;
			}
			sum = yourCard2.value + yourCard.value; // Sum up dealt cards
		} else {
			std::cout << "Your cards are: " << ranks[yourCard.value] << " and " << ranks[yourCard2.value] << std::endl;
		}

		std::cout << "Dealers card is: " << ranks[dealerCard.value] << std::endl;
		std::cout << "(H)it or (S)tand?" << std::endl;
		char hos; 
		//hos='h';// !!! For testing only
		std::cin >> hos; // Breaks a lot of things if you ask for input in VS

		// Hit or stand
		if(hos == 'h' || hos == 'H'){
			// Hit
			while (sum <= 21) {
				// This loop continues until the user gets above 21 (bust)
				// or stands.
				card yourCardN = theDeck.deal(); // Deal the n(th) card
				std::cout << "You were dealt a " << ranks[yourCardN.value] << std::endl;

				if (yourCardN.value >= 11) {
					// Face cards have a value of 10
					sum = sum + 10;
				} else if (yourCardN.value == 1) {
					// Ace detection
					std::cout << "You were dealt an ace. What would you like your ace to be? (1) or (11)?\n";
					std::cin >> yourCardN.value;
					sum = yourCardN.value + sum; // Sum up dealt cards
				} else {
					sum = yourCardN.value + sum; // Sum up dealt cards
				}
				//std::cout << "You currently have: " << sum << std::endl;
				if (sum > 21) {
					break;
				}
				std::cout << "(H)it or (S)tand?\n";
				std::cin >> hos; // see above about cin and VS
				std::cout << std::endl;
				if (hos == 's' || hos == 'S') {
					// Break out of loop
					break;
				}
			}
		}
		// Dealer's turn
		// Dealer reveals second card and plays
		std::cout << "The dealers cards are a " << ranks[dealerCard.value] << " and a " << ranks[dealerCard2.value] << std::endl;
		while (dealerSum <= 16) {
			// Dealer stands above 16
			card dealerCardN = theDeck.deal(); // Deal the n(th) card
			std::cout << "The dealer dealt a " << ranks[dealerCardN.value] << std::endl;
			if (dealerCardN.value >= 11) {
				// Ace detection
				dealerSum = dealerSum + 10;
			} else if (dealerCardN.value == 1) {
				if (sum + 11 > 21) {
					dealerCardN.value = 1;
				} else {
					dealerCardN.value == 11;
				}
				dealerSum = dealerCardN.value + dealerSum; // Sum up dealt cards
			} else {
				dealerSum = dealerCardN.value + dealerSum; // Sum up dealt cards
			}
			//std::cout << "They currently have " << dealerSum << std::endl;
		}

		// See who won
		if (dealerSum > 21) {
			// Dealer busts
			if (sum <= 21) {
				// If the player doesn't bust as well
				// they win
				std::cout << "You win!" << std::endl;
			} else {
				// It's a draw
				std::cout << "Draw." << std::endl;
			}
		} else {
			// Dealer did not bust
			if (sum <= 21) {
				if (dealerSum > sum) {
					// Player loses
					std::cout << "You lose." << std::endl;
				}else if(dealerSum == sum ){
					std::cout << "Draw.\n";
				} else {
					// Player wins
					std::cout << "You win!" << std::endl;
				}
			} else {
				//Player busts
				std::cout << "You lose." << std::endl;
			}
		}

		std::cout << std::endl << std::endl;

		std::cout << "Would you like to play again? (Y/N)" << std::endl;
		char tempChar;
		//tempChar = 'n'; // for testing
		std::cin >> tempChar;
		if (tempChar == 'N' || tempChar == 'n') {
			playing = false;
		}
	}

	return 0;
}