#include <iostream>
#include <time.h> //time func.h
#include <string> //stoi func.h
using namespace std;

void baseball();
int pInput();

int main()
{
	cout << "숫자 야구 게임" << endl;

	baseball();
}

void baseball()
{
	// random seed initialize
	srand(time(0));

	// Create an array & initialize it to 0
	int arr[3] = {};

	// arr[index]
	int index{ 0 };
	while (arr[2] == 0)
	{
		// Create random Number
		int num = rand() % 9 + 1;
		// for duplicate checking
		bool dup = false;

		// duplicate checking
		for (int i = 0; i < 3; i++)
			if (num == arr[i]) dup = true;

		// If no duplicates, assign a value to the array 
		if (!dup) arr[index++] = num;
	}

	// Random number output
	cout << "치트: ";
	for (int n : arr)
	{
		cout << n;
	}

	cout << endl;
	cout << endl;

	// Input
	int x = pInput();
	cout << "x= " << x;

}

/* Player input */
int pInput()
{
	string str;
	int input{0};
	while (1)
	{
		cout << "중복없이 연속되는 수 3개를 입력하세요: ";
		cin >> str;
	
		try 
		{
			input = stoi(str);
		}
		// string checking
		catch (const invalid_argument& e)
		{
			cout << "[ERROR] '문자'가 입력되었습니다." << endl;
			cout << endl;
			continue;
		}

		//overflow checking
		if ( input < 100 || input > 999) cout << "[ERROR] '값'이 작거나 큽니다." << endl;
		else
		{
			int x = input / 100,
				y = input % 100 / 10,
				z = input % 10;
			// 0 checking
			if (y == 0 || z == 0) cout << "[ERROR] '0'이 있습니다." << endl;
			// duplicate checking
			else if (x != y && x != z && y != z) break;
			else cout << "[ERROR] '중복되는 숫자'가 있습니다." << endl;
		}
			cout << endl;
	}

	return input;
}