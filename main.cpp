#include <iostream>
#include<cstdlib>
using namespace std;

enum enWinner {Player = 1,Computer = 2,Draw = 3};

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
struct stRoundInfo
{

	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string RoundWinnerName;
};
struct stGameResult
{
	short GameRounds=0;
	short PlayerWinTimes=0;
	short ComputerWinTimes=0;
	short DrawTimes=0;
	enWinner GameWinner;
	string GameWinnerNAme;
};

int RandomNumber(int From, int To) {

	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;
}

int GameRounds() {
	int GameRounds;
	do {
		cout << "How Many round do you want to play from 1 to 10 " << endl;
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10);
	return GameRounds;
}

enGameChoice ReadPlayerChoice() {
	short PlayerChoice;
	do {
		cout << "Enter your choice : Stone[1] ; Paper[2] ; Sessior[3] ? " << endl;
		cin >> PlayerChoice;
	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return enGameChoice(PlayerChoice);
}

enGameChoice GetComputerChoice() {
	return enGameChoice(RandomNumber(1, 3));
}

string ChoiceName(enGameChoice Choice) {
	string ArrChoice[3] = { "Stone","Paper","Sesoir" };
	return ArrChoice[Choice - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors) 
			return enWinner::Computer;
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone) 
		return enWinner::Computer ;
		break;
	}
	return enWinner::Player;
}

string WinnerName(enWinner Winner) {
	string ArrWinner[3] = { "Player","Computer","Draw" };
	return ArrWinner[Winner - 1];
}

void SetColorScrren(enWinner winner) {
	switch (winner)
	{
	case Player:
		system("color 2F");
		break;
	case Computer:
		cout << "\a";
		system("color 4F");
		break;
	case Draw:
		system("color 6F");
		break;
	}
}

void PrintRoundInfo(stRoundInfo RoundInfo) {
	cout << "______________________________________________________\n";
	cout << "Player choise : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer choise : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round winner : " << RoundInfo.RoundWinnerName << endl;
	cout << "______________________________________________________\n";
}
enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes) {
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (ComputerWinTimes > PlayerWinTimes) 
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResult FillTheGameResult(short GameRounds, short PlayerWinTimes, short ComputerWinTimes,short DrawTimes) {
	stGameResult GameResult;
	GameResult.GameRounds = GameRounds;
	GameResult.PlayerWinTimes = PlayerWinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResult.GameWinnerNAme = WinnerName(GameResult.GameWinner);
	return GameResult;
}
string tabs(int HowManyTabs) {
	string t = "";
	for (int i = 1;i <= HowManyTabs;i++) {
		t = t + "\t";
	}
	return t;
}

stGameResult PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;

	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;

	for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++) {
		cout << tabs(2) << "Round [" << GameRound << "] begins :\n\n";
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);
		SetColorScrren(RoundInfo.RoundWinner);
	
		if (RoundInfo.RoundWinner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundInfo(RoundInfo);
	}
	return FillTheGameResult(HowManyRounds,PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOver() {
	string line = "===================================================";
	cout << "\n" << tabs(2) << line << endl;
	cout << tabs(4) << "  G A M E   O V E R  " << endl;
	cout << tabs(2) << line << "\n\n";
}void ShowTheFinalRsult(stGameResult GameResults) {
	cout << tabs(2) << "___________________[Game Results]_______________\n\n";
	cout << tabs(2) << "Game Rounds             :" << GameResults.GameRounds << endl;
	cout << tabs(2) << "Player Won Times        :" << GameResults.PlayerWinTimes << endl;
	cout << tabs(2) << "Computer Won Times      :" << GameResults.ComputerWinTimes << endl;
	cout << tabs(2) << "Draw Times              :" << GameResults.DrawTimes << endl;
	cout << tabs(2) << "FinalWinner             :" <<WinnerName(GameResults.GameWinner) << endl;
	cout << tabs(2) << "_________________________________________________\n\n";

	SetColorScrren(GameResults.GameWinner);
}

void ResetScreen() {

	system("cls");
	system("Color 0F");
}
void StartGame() {
	char PlayAgain;
	do {
		ResetScreen();
		stGameResult GameResult = PlayGame(GameRounds());
		ShowGameOver();
		ShowTheFinalRsult(GameResult);
		cout << endl << tabs(3) << "Do you want to play again Y/N \n";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

