#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// user 번호 입력 함수
int userInput()
{
    int n;
    cin >> n;
    return n;
}

// 등수 함수
void place(int n)
{
    // 6개 -> 1등, 5개 -> 2등, 4, 3개 -> 3등, 그 이하 -> 순위권 밖
	if (n == 6) cout << "You are in 1th place!" << endl;
	else if (n == 5) cout << "You are in 2th place!" << endl;
	else if (n == 4 || n == 3) cout << "You are in 3th place!" << endl;
	else cout << "You didn't rank..." << endl;
}

int main()
{
    // random 변수 6개
    int random1, random2, random3, random4, random5, random6;
    int number, cnt = 0;

    srand(time(NULL));

    random1 = rand() % 50;
    random2 = rand() % 50;
    random3 = rand() % 50;
    random4 = rand() % 50;
    random5 = rand() % 50;
    random6 = rand() % 50;

    cout << "Guess lottery numbers: " << endl;
    for (int i = 0; i < 6; i++){
        number = userInput(); // 사용자 입력 번호 -> 함수 호출

        // 사용자 입력 번호와 랜덤 번호 matching --> 맞는게 있으면 cnt 증가
        if (number == random1) cnt += 1;
        else if (number == random2) cnt += 1;
        else if (number == random3) cnt += 1;
        else if (number == random4) cnt += 1;
        else if (number == random5) cnt += 1;
        else if (number == random6) cnt += 1;
    }
    cout << "Number: " << random1 << " " << random2 << " " << random3 << " "
    << random4 << " " << random5 << " " << random6 << endl;

    cout << "You match " << cnt << " numbers!";
    place(cnt); 

    return 0;
}