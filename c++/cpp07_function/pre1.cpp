#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// srand(time(NULL));

bool match(int n, int r)
{
	cout << r << " ";

	if (n == r) return true;
	else return false;
}

void place(int n)
{
	if (n == 6) cout << "You are in 1th place!" << endl;
	else if (n == 5) cout << "You are in 2th place!" << endl;
	else if (n == 4 || n == 3) cout << "You are in 3th place!" << endl;
	else cout << "You didn't rank..." << endl;
}
int main()
{
	int match_cnt = 0, num1, num2, num3, num4, num5, num6;

	srand(time(NULL));
	// cout << "Number: "
	cout << "Guess lottery numbers:" << endl;
	cin >> num1;
	cin >> num2;
	cin >> num3;
	cin >> num4;
	cin >> num5;
	cin >> num6;

	cout << "Number: ";
	if (match(num1, rand() % 50)) match_cnt += 1;
	if (match(num2, rand() % 50)) match_cnt += 1;
	if (match(num3, rand() % 50)) match_cnt += 1;
	if (match(num4, rand() % 50)) match_cnt += 1;
	if (match(num5, rand() % 50)) match_cnt += 1;
	if (match(num6, rand() % 50)) match_cnt += 1;
	cout << endl;

	cout << "You match " << match_cnt << " number! ";
	place(match_cnt);

	return 0;
}

