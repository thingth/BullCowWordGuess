#pragma once
#include "FWordGuess.h"
#include <map>
#define TMap std::map

FWordGuess::FWordGuess() { /*/Reset();*/ } //default constuctor

bool FWordGuess::IsGameWon() const { return GameResult; }
int32 FWordGuess::GetCurrentTry() const { return CurrentTry; }
int32 FWordGuess::GetHiddenWordLength() const { return HiddenWord.length(); }

FString FWordGuess::SetHiddenWordFromLength(int32 &WordLength) const
{
	TMap<int32, FString> WordFromLength{ {3,"sun"},{4,"star"},{5,"cloud"},{6,"planet"} }; //Hidden word must be an isogram
	return WordFromLength[WordLength];
}

void FWordGuess::Reset(int32 &WordLength)
{
	GameResult = false;
	FString Hidden_Word = SetHiddenWordFromLength(WordLength);
	HiddenWord = Hidden_Word;

	CurrentTry = 1;
}

int32 FWordGuess::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,3},{4,3},{5,4},{6,5} };
	return WordLengthToMaxTries[HiddenWord.length()];
}

EGuessCheck FWordGuess::GuessValidity(FString GuessWord) const
{
	if (!IsLowercase(GuessWord))
	{
		return EGuessCheck::Lowercase_Only;
	}
	else if (!IsIsogram(GuessWord))
	{
		return EGuessCheck::Not_Isogram;
	}
	else if (GuessWord.length() != GetHiddenWordLength())
	{
		return EGuessCheck::Wrong_Length;
	}
	else
	{
		return EGuessCheck::OK;
	}
}

FBCCount FWordGuess::SummtValidGuess(FString GuessWord) //Count B and C and increase # of tries
{
	CurrentTry++;
	FBCCount BCCount;
	int32 WordLength = HiddenWord.length();

	for (int32 i = 0; i < WordLength; i++) //Loop through all letter in hidden word
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			if (HiddenWord[i] == GuessWord[j])
			{
				if (i == j)
				{
					BCCount.Bulls++;
				}
				else
				{
					BCCount.Cows++;
				}
			}
		}
	}
	if (BCCount.Bulls == WordLength) { GameResult = true; }
	else { GameResult = false; }
	return BCCount;
}

bool FWordGuess::IsIsogram(FString Word) const
{
	//treat 0 and 1 length as isogram
	if (Word.length() <= 1) { return true; }

	//setup map
	TMap<char, bool> LetterSeen;
	for (char Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //check mixed case as lowercase
		if (LetterSeen[Letter]) //if letter is already in the map
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;//add letter to the map
		}
	}
	return true;
}

bool FWordGuess::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
				return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}
