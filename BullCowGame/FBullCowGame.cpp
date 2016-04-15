#include "FBullCowGame.h"
#include <map>
#define TMap std::map


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
	return bGameIsWon;
}

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const {
	
	if (!IsIsogram(Guess)) { 
		return EGuessStatus::Not_Isogram; // if guess isn't isogram
	}
	else if (!IsLowercase(Guess)) { 
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
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
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
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} 
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// check for single letter or zero letter string as true.
	if (Word.length() <= 1) {
		return true;
	}
	
	TMap<char, bool> LetterSeen;
		
	for (auto Letter : Word) { // for all letters of the word
		Letter = tolower(Letter); 
		if (LetterSeen[Letter]) { // check each letter in map
			return false; // we do not have a isogram
		}
		else {
			LetterSeen[Letter] = true; // otherwise add to map
		}
	}
		return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
