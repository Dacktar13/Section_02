#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all varaibles inigalised to 0
struct FBullCowCount{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	bool CheckGuessValid(FString) const; // TODO make a more rich return value back

	void Reset(); // TODO make a more rich return value back
	FBullCowCount SubmitGuess(FString);


private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};