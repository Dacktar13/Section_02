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
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const {
	
	if (false) {
		return EGuessStatus::Not_Isogram; // if guess isn't isogram
	}
	else if (false) {
		return EGuessStatus::Not_Lowercase; // if guess isn't all lowercase
		}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length; // if guess length is wrong
	}
	else {
		return EGuessStatus::OK; // otherwise return ok
	}
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



