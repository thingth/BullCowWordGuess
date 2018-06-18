/*Game logic w/o direct user interaction*/
#pragma once
#include <string>

//Unreal friendly syntax
using FString = std::string;
using int32 = int;

struct FBCCount //Structure used when data is simple, no function, and no public data
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessCheck //Error Checking
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Lowercase_Only
};

class FWordGuess
{
public:
	FWordGuess(); //Constructor**

	void Reset(int32&);
	bool IsGameWon() const;

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString SetHiddenWordFromLength(int32&) const;
	EGuessCheck GuessValidity(FString) const;
	FBCCount SummtValidGuess(FString);

private:
	int32 CurrentTry;
	FString HiddenWord;
	bool GameResult;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
