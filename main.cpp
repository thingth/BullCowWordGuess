#pragma once
#include <iostream> //std::cout, FText, etc
#include <string> //std::cin
#include "FWordGuess.h"

//Unreal friendly syntax
using FText = std::string;
using int32 = int;

void PrintIntro();
void Play();
int32 GetDifficulty();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();

FWordGuess BCGame; //Class and instance; instantiate a new game

int main()
{
	do
	{
		PrintIntro();
		Play();
	} while (PlayAgain() == 1);

	return 0; //Exit
}

void PrintIntro()
{
	std::cout << std::endl << " Welcome to the Word Guessing Game: BULLS & COWS!\n";
}

void Play()
{
	int32 LengthOption = GetDifficulty();
	BCGame.Reset(LengthOption);

	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess_Word = GetValidGuess();
		FBCCount BCCount = BCGame.SummtValidGuess(Guess_Word);

		std::cout << "Bulls = " << BCCount.Bulls << " Cows = " << BCCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

int32 GetDifficulty()
{
	int32 LengthOption = 0;
	do
	{
		std::cout << "Please choose length of word you want to play (3 to 6): ";
		std::cin >> LengthOption;
		std::cin.ignore();
		if (LengthOption < 3 || LengthOption > 6)
		{
			std::cout << "Please choose length between 3 to 6.\n";
		}
	} while (LengthOption < 3 || LengthOption > 6);

	std::cout << "You choose word with " << LengthOption << " letters!\n";

	return LengthOption;
}

FText GetValidGuess()
{
	EGuessCheck Status = EGuessCheck::Invalid_Status;
	FText Guess_Word = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Turn: " << CurrentTry << "/" << BCGame.GetMaxTries() << " Please enter your guess: ";
		std::getline(std::cin, Guess_Word); //get full word in line with space included

		Status = BCGame.GuessValidity(Guess_Word);
		switch (Status)
		{
		case EGuessCheck::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessCheck::Lowercase_Only:
			std::cout << "Please enter lowercase letter.\n\n";
			break;
		case EGuessCheck::Not_Isogram:
			std::cout << "Please enter an isogram word (no duplicate letter).\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessCheck::OK);
	return Guess_Word;
}

bool PlayAgain()
{
	std::cout << "Play again? (Y/N)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATION! YOU WON!\n\n";
	}
	else
	{
		std::cout << "YOU LOSE! Better luck next time!\n\n";
	}
}