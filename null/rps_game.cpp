﻿#include <iostream>
#include <string>
#include <time.h>
using namespace std;

void rpsGame();
int inputRPS();
int inputOP();

int main() 
{
	cout << "가위 바위 보 게임!!" << endl;
	cout << "게임은 5판 3선승제입니다." << endl;
	cout << endl;

	rpsGame();
}

void rpsGame()
{
	string choice[] = { "가위", "바위", "보" };

	int plaWin{ 0 }, comWin{ 0 }, cnt{ 5 }, player, com;
	srand((unsigned)(time(0)));

	while (cnt > 0)
	{
		cout << "\tPlayer \tComputer" << endl;
		cout << "점수 \t" << plaWin << "\t" << comWin << endl;

		com = rand() % 3 +1;
		player = inputRPS();

		cout << "플레이어는 [" << player << "]" << choice[player-1] << ", ";
		cout << "컴퓨터는 [" << com << "]" << choice[com-1] <<"를 냈다." << endl;
		cout << "따라서 이번게임은.. ";


		int result = (player - com + 3) % 3;

		if (result == 0) cout << "비겼다." << endl;
		else if (result == 1)
		{
			cout << "플레이어의 승!" << endl;
			plaWin++;
			cnt--;
		}
		else
		{
			cout << "컴퓨터의 승..." << endl;
			comWin++;
			cnt--;
		}
		cout << endl;

		if (plaWin > 2 || comWin > 2)
		{
			cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
			cout << "\"" << (plaWin > comWin ? "플레이어" : "컴퓨터") << "\"가 먼저 3점을 획득해서 승리했습니다." << endl;
			int option{ inputOP() };

			if (option == 1) rpsGame();
			else exit(1);
			break;
		}
	}
}

int inputRPS()
{
	int x;

	while (1)
	{
		cout << endl;
		cout << "[1]가위 [2]바위 [3]보, 숫자를 입력하세요: ";
		string str;
		cin >> str;

		if (str == "1" || str == "2" || str == "3") 
		{
			x = stoi(str);
			break;
		}
		else
			cout << "잘못된 입력입니다. 숫자를 입력하세요. "<< endl;
	}

	return x;
}

int inputOP()
{
	int x;

	while (1)
	{
		cout << "[1]다시하기 [2]종료하기, 게임을 다시 하시겠습니까? ";
		string str;
		cin >> str;

		if (str == "1" || str == "2")
		{
			x = stoi(str);
			break;
		}
		else
			cout << "잘못된 입력입니다. 숫자를 입력하세요. " << endl;
	}

	cout << endl;
	return x;
}