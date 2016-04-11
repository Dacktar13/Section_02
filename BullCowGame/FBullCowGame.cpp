#include "FBullCowGame.h"


FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetMaxTries() const {
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const {
	return false;
}

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "seth";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::CheckGuessValid(FString) const {
	return false;
}

// recives a valid guess, increments try, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
	// increment return number
	MyCurrentTry++;
	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // if not increment cows
				}
			}
		}
	}

	return BullCowCount;
}



