#pragma once
#include <string>

class FBullCowGame {
public:
	void Reset(); //make a more rich return value back
	int GetMaxTries();
	int GetCurrentTry();
	bool IsGameWon();
	bool CheckGuessValid(std::string);



private:
	int MyCurrentTry;
	int MyMaxTries;
};