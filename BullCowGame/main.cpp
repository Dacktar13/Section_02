/* This is the concole executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// entry point of application
int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0; // exit application
}


void PrintIntro() {
	// introduce the game
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << FBullCowGame().GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame(){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	// TODO Change from FORR loop to WHILE loop once validating tries
	for (int32 count = 1; count <= MaxTries; count++) {
		FText Guess = GetGuess(); // TODO make loop check for valid guesses

		//  Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// print number of bulls and cows 
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		
		std::cout << "Your guess was " << Guess << std::endl;
		std::cout << std::endl;
	}
	
	// TODO add game summary
}

FText GetGuess() {
	int32 CurrentTry = BCGame.GetCurrentTry();

	// get a guess from the player
	std::cout << "Try " << CurrentTry << ". Please enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
