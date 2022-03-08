// Ashley Bryan, Ian Campion, Joshua Barkey
// 10/14/2020
// BlackJack Final Project
// It's a program... which allows you to play BlackJack.
// Craig, the rubber duck, https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program, https://mathbits.com/MathBits/CompSci/LibraryFunc/rand.htm

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <vector>

using namespace std;


vector <string> userHandShown{};														// vector representing cards currently in user'Ås hand
vector <string> dealerHandShown{};														// vector representing cards currently in dealerÅEs hand
vector <int> VALUE_OF_CARD{};															// vector representing the value of each card
vector <string> DECK_OF_CARDS{};														// vector representing card names
int userHandValue = 0;																	// value of user's hand
int dealerHandValue = 0;																// value of dealer's hand

void sleep(float seconds)																// do nothing until the elapsed time has passed.
{
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	while (clock() < startClock + secondsAhead);

	return;
}


int randomCardDrawPlayer(vector<string>& DECK_OF_CARDS, vector<int>& VALUE_OF_CARD)		//Random Card Draw for the player
{
	int i = rand() % (DECK_OF_CARDS.size() - 1);
	userHandShown.push_back(DECK_OF_CARDS.at(i));
	userHandValue = userHandValue + VALUE_OF_CARD.at(i);

	for (int z = 0; z < DECK_OF_CARDS.size() - 1; ++z)
	{
		if (z >= i)
		{
			DECK_OF_CARDS.at(z) = DECK_OF_CARDS.at(z + 1);
			VALUE_OF_CARD.at(z) = VALUE_OF_CARD.at(z + 1);
		}
	}

	DECK_OF_CARDS.pop_back();
	VALUE_OF_CARD.pop_back();

	return i;
}

int randomCardDrawDealer(vector<string>& DECK_OF_CARDS, vector<int>& VALUE_OF_CARD)		//Random Card Draw for the dealer
{
	int i = rand() % (DECK_OF_CARDS.size() - 1);
	dealerHandShown.push_back(DECK_OF_CARDS.at(i));
	dealerHandValue = dealerHandValue + VALUE_OF_CARD.at(i);

	for (int z = 0; z < DECK_OF_CARDS.size() - 1; ++z)
	{
		if (z >= i)
		{
			DECK_OF_CARDS.at(z) = DECK_OF_CARDS.at(z + 1);
			VALUE_OF_CARD.at(z) = VALUE_OF_CARD.at(z + 1);
		}
	}

	DECK_OF_CARDS.pop_back();
	VALUE_OF_CARD.pop_back();

	return i;
}

void displayDealerHand() {
	cout << "Dealer's current hand is: " << endl;										//display dealer's cards

	for (int h = 0; h < dealerHandShown.size(); ++h)
	{
		cout << dealerHandShown.at(h) << ", ";
	}
	cout << endl
		<< "totaling: " << dealerHandValue << endl << endl;								//display dealer's hand value
	return;
}

void displayUserHand() {
	cout << "Your current hand is: " << endl;											//display user's cards
	for (int h = 0; h < userHandShown.size(); ++h)
	{
		cout << userHandShown.at(h) << ", ";
	}
	cout << endl
		<< "totaling: " << userHandValue << endl << endl;								//diplay user's hand value

	return;
}



int main()
{
	bool userFlag = false;																//Ace can = 1 while false
	bool dealerFlag = false;															//Ace can = 1 while false
	char playAgain;																		//play again?
	char userChar = 'a';																//Hit?
	int counter;																		//big loop counter
	char anyKey;																		//any key to move forward

	srand(time(NULL));																	//seeds random number from time of game start


	cout << "Welcome to BlackJack!" << endl << endl << endl;							//Welcome to comments!

	cout << "The goal of blackjack is to beat the dealer's hand" << endl
		<< "without going over 21." << endl << endl

		<< "Face cards are worth 10." << endl
		<< "Aces are worth 1 or 11, whichever makes a better hand." << endl
		<< "Aces can only be used in this fashion one time." << endl << endl

		<< "Each player starts with two cards." << endl
		<< "To 'Hit' is to ask for another card." << endl
		<< "To 'Stand' is to hold your total and" << endl
		<< "end your turn." << endl << endl

		<< "If you go over 21 you bust, and the dealer" << endl
		<< "wins regardless of the dealer's hand." << endl << endl

		<< "Dealer will hit until his / her cards total" << endl
		<< "16 or higher." << endl << endl;

	sleep(8);

	cout << "Enter any key to begin:" << endl;
	cin >> anyKey;
	cout << endl << endl << endl;

	do
	{

		VALUE_OF_CARD.resize(52);
		DECK_OF_CARDS.resize(52);

		vector <string> DECK_NUMBERS{
			"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
		};
		vector <string> SUITS{
			"Hearts", "Diamonds", "Clubs", "Spades"
		};
		counter = 0;
		for (int i = 0; i < 4; ++i)														//This will give the value for each card which shares the same index as DECK_OF_CARDS
		{
			for (int j = 0; j < 13; ++j)
			{
				if (j < 8) {
					VALUE_OF_CARD.at(counter) = j + 2;
				}
				else if ((j >= 8) and (j < 12)) {
					VALUE_OF_CARD.at(counter) = 10;
				}
				else if (j == 12) {
					VALUE_OF_CARD.at(counter) = 11;
				}

				++counter;
			}
		}

		counter = 0;																	//reset counter
		for (int i = 0; i < 4; i++) {													//creates the deck with words
			for (int j = 0; j < 13; j++) {
				DECK_OF_CARDS.at(counter++) = DECK_NUMBERS.at(j) + " of " + SUITS.at(i);
			}
		}

		cout << "Shuffling and dealing hands" << endl;									//Deals cards into player and dealer's hands by calling and returning functions listed above
		randomCardDrawPlayer(DECK_OF_CARDS, VALUE_OF_CARD);
		randomCardDrawDealer(DECK_OF_CARDS, VALUE_OF_CARD);
		randomCardDrawPlayer(DECK_OF_CARDS, VALUE_OF_CARD);
		randomCardDrawDealer(DECK_OF_CARDS, VALUE_OF_CARD);

		for (int i = 0; i < 9; ++i) {
			sleep(.5);																	//pause added for funsies
			cout << ".";
		}
		cout << endl << endl;
		while (userChar != 's' and userChar != 'S' and userHandValue < 21 and dealerHandValue < 21)
		{
			displayUserHand();
			sleep(2);
			displayDealerHand();
			sleep(2);

			cout << "Hit or Stay? 'H' to hit, 'S' to stay." << endl;
			cin >> userChar;
			cout << endl;


			if (userChar == 'H' or userChar == 'h')										//Verifies valid input and directs to user's choice
			{
				randomCardDrawPlayer(DECK_OF_CARDS, VALUE_OF_CARD);						//add a card to user's hand
				if (userFlag == false)													//Ace can only count as 1 instead of 11 once a hand 
				{																		//'flag == false' verifies it hasn't been reduced yet 
					for (int i = 0; i < userHandShown.size(); ++i)						//searches user's hand for Ace of suit
					{
						if (((userHandShown.at(i) == "A of Spades") or (userHandShown.at(i) == "A of Hearts")
							or (userHandShown.at(i) == "A of Clubs") or (userHandShown.at(i) == "A of Diamonds"))
							and (userHandValue > 21)) {

							userHandValue = userHandValue - 10;							//Ace becomes 1
							userFlag = true;											//cannot repeat this branch when userFlag = true
						}
					}
				}

			}
			else if (userChar != 's' and userChar != 'S')
			{
				cout << "Invalid input, H to hit, S to stay" << endl;					//verify user's input is valid
			}

			if (dealerHandValue <= 16 && userHandValue <= 21)							//dealer will always hit if it's hand value is under 16
			{
				cout << "Dealer hits" << endl;
				randomCardDrawDealer(DECK_OF_CARDS, VALUE_OF_CARD);
				if (dealerFlag == false)												//Ace can only count as 1 instead of 11 once a hand 
				{																		//'flag == false' verifies it hasn't been reduced yet 
					for (int i = 0; i < dealerHandShown.size(); ++i)					//searches dealer's hand for Ace of suit
					{
						if (((dealerHandShown.at(i) == "A of Spades") or (dealerHandShown.at(i) == "A of Hearts")
							or (dealerHandShown.at(i) == "A of Clubs") or (dealerHandShown.at(i) == "A of Diamonds"))
							and (dealerHandValue > 21)) {

							dealerHandValue = dealerHandValue - 10;						//Ace becomes 1
							dealerFlag = true;											//cannot repeat this branch when dealerrFlag = true
						}
					}
				}
				displayDealerHand();
				sleep(1);
			}
		}

		if (userHandValue <= 21)
		{
			while (dealerHandValue <= 16)												//dealer will hit, even if the user stops, until dealer's hand value is >= 16
			{
				cout << "Dealer hits" << endl;
				randomCardDrawDealer(DECK_OF_CARDS, VALUE_OF_CARD);
				if (dealerFlag == false)												//Ace can only count as 1 instead of 11 once a hand 
				{																		//'flag == false' verifies it hasn't been reduced yet 
					for (int i = 0; i < dealerHandShown.size(); ++i)					//searches dealer's hand for Ace of suit
					{
						if (((dealerHandShown.at(i) == "A of Spades") or (dealerHandShown.at(i) == "A of Hearts")
							or (dealerHandShown.at(i) == "A of Clubs") or (dealerHandShown.at(i) == "A of Diamonds"))
							and (dealerHandValue > 21)) {

							dealerHandValue = dealerHandValue - 10;						//Ace becomes 1
							dealerFlag = true;											//cannot repeat this branch when dealerrFlag = true
						}
					}
				}
				displayDealerHand();
				sleep(1);
			}
		}

		sleep(1);
		cout << "Your final hand value: " << userHandValue << endl << endl;				//display the results of the game
		sleep(1);
		cout << "Dealers final hand value: " << dealerHandValue << endl << endl;
		sleep(1);

		if (userHandValue > 21) {
			cout << "Bust! Better luck next time!" << endl;
		}
		else if (dealerHandValue > 21) {
			cout << "Dealer busts! You're in luck!" << endl;
		}
		else if (dealerHandValue == 21) {
			cout << "Dealer BlackJack! Darn!" << endl;
		}
		else if (userHandValue == 21) {
			cout << "BlackJack! Time to buy a lottery ticket!" << endl;
		}
		else if ((dealerHandValue > userHandValue) or (dealerHandValue == userHandValue)) {
			cout << "Dealer wins! You'll have em in the next round!" << endl;
		}
		else if (userHandValue > dealerHandValue) {
			cout << "You win! Way to go!" << endl;
		}

		cout << endl << "Want to try your luck again? 'Y' for yes, or 'N' for no." << endl; //Do you want to play again?  execute "do/while" loop
		cin >> playAgain;
		cout << endl;

		if ((playAgain != 'y') and (playAgain != 'Y')										//Checks user input
			and (playAgain != 'n') and (playAgain != 'N'))
		{
			cout << "You didn't enter the right thing." << endl
				<< "'Y' for yes, or 'N' for no." << endl;

			cin >> playAgain;
			cout << endl;
		}

		if (playAgain == 'y' or playAgain == 'Y')
		{																					//Reset values and clears screen if replayed
			userHandShown.resize(0);
			dealerHandShown.resize(0);
			userHandValue = 0;
			dealerHandValue = 0;
			userFlag = false;
			dealerFlag = false;
			userChar = 'a';
			cout << string(50, '\n');
		}

	} while (playAgain == 'y' or playAgain == 'Y');
	cout << endl;
	cout << "Gambling problem? Call the gambling addiction helpline! 1-800-522-4700. Thanks for playing!" << endl;
	return 0;
}
