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
FText GetValidGuess();
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
	for (int32 count = 1; count <= MaxTries; count++) { // TODO Change from FORR loop to WHILE loop once validating tries
		FText Guess = GetValidGuess(); 

		//  Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	
	// TODO add game summary
}

// loop continually until the user gives a valid guess
FText GetValidGuess() { 
	// get a guess from the player
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Please enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);

	EGuessStatus Status = BCGame.CheckGuessValid(Guess);
	switch (Status) {
	case EGuessStatus::Wrong_Length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "Please enter a word without repeating letters. \n";
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "Please make sure your guess is all lowercase!\n";
		break;
	default:
		return Guess;
	}

	
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
