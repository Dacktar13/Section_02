#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame() {
	Reset();
} //default constructor

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const {
	return bGameIsWon;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
		
	MyHiddenWord = GetHiddenWord("6");
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

EWordStatus FBullCowGame::DiffulcutySelected(FString Diffulcuty) const {
	if (Diffulcuty == "3"){
		return EWordStatus::Three;
	}
	else if (Diffulcuty == "4"){
		return EWordStatus::Four;
	}
	else if (Diffulcuty == "5") {
		return EWordStatus::Five;
	}
	else if (Diffulcuty == "6") {
		return EWordStatus::Six;
	}
	else {
		return EWordStatus::Seven;
	}

}

FString FBullCowGame::GetHiddenWord(FString length) const {
	srand(time(NULL)); // seed for random generater
	FString WordArray[3];
	int32 len = sizeof(WordArray) / sizeof(*WordArray);

	FString ThreeWordArray[] = { "cat","box","fan" };
	FString FourWordArray[] = { "bats","drop","road" };
	FString FiveWordArray[] = { "lives","rains","float" };
	FString SixWordArray[] = { "planet","spouce","plants" };
	FString SevenWordArray[] = { "bawling","pitched","snorted" };

	EWordStatus WordLength = DiffulcutySelected(length);
	switch (WordLength) {
	case EWordStatus::Three:
		for (int i = 0; i < len; i++) {
			WordArray[i] = ThreeWordArray[i];
		}
		break;
	case EWordStatus::Four:
		for (int i = 0; i < len; i++) {
			WordArray[i] = FourWordArray[i];
		}
		break;
	case EWordStatus::Five:
		for (int i = 0; i < len; i++) {
			WordArray[i] = FiveWordArray[i];
		}
		break;
	case EWordStatus::Six:
		for (int i = 0; i < len; i++) {
			WordArray[i] = SixWordArray[i];
		}
		break;
	case EWordStatus::Seven:
		for (int i = 0; i < len; i++) {
			WordArray[i] = SevenWordArray[i];
		}
		break;
	default:
		break;
	return WordArray[rand() % len];
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
