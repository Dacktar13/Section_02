#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuess();
bool AskToPlayAgain();


// entry point of application
int main() {
	do {
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());
	return 0; // exit application
}


void PrintIntro() {
	// introduce the game
	constexpr int WORD_LENGTH = 5;
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}

void PlayGame(){
	// loop for the number of turns asking for guesses
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++) {
		string Guess = GetGuess();
		cout << "Your guess was " << Guess << endl;
		cout << endl;
	}
}

string GetGuess() {
	// get a guess from the player
	cout << "Please enter your guess: ";
	string Guess = "";
	getline(cin, Guess);
	return Guess;
}

bool AskToPlayAgain(){
	cout << "Do you want to play again? ";
	string Response = "";
	getline(cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
