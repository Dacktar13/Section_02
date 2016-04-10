#pragma once
#include <string>

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); //make a more rich return value back
	bool CheckGuessValid(std::string);




private:
	int MyCurrentTry;
	int MyMaxTries;
	
};