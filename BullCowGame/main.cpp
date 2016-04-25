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
void PrintGameSummary();
void GetWord();

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
	GetWord();
	
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "           }   {        ___ " << std::endl;
	std::cout << "           (o o)       (o o) " << std::endl;
	std::cout << "   /-------\\   /       \\   /-------\\ " << std::endl;
	std::cout << "  / | BULL |               | COW  | \\  " << std::endl;
	std::cout << " *  |-,----|               |______|  *  " << std::endl;
	std::cout << "    ^      ^               ^       ^    " << std::endl;
	std::cout << "Can you guess the " << FBullCowGame().GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame(){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	
	// loop asking for guesses while the game is NOT won 
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess(); 

		//  Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";
		if (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
			std::cout << "You have " << MaxTries - BCGame.GetCurrentTry() + 1 << " tries left.\n\n";
		}
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() { 
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Please enter your guess: ";
		
		std::getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValid(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please make sure your guess is all lowercase!\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
	
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again with the same word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations! You Have Won!\n\n";
	}
	else {
		std::cout << "Unlucky, Better Luck Next Time!\n\n";
	}
	return;
}

void GetWord() {
	FText WordLength = "";
	std::cout << "Please enter the length of the isogram you want. (3/4/5/6/7) ";
	std::getline(std::cin, WordLength);
	
	
	return;
}
	