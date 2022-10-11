#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 주사위 눈 확률 그리는 함수
void draw(int n, int c)
{
    for (int i = 0; i < c; i++){
        cout << "@";
    }
    for (int j = 0; j < n-c; j++){
        cout << "*";
    }
    cout << endl;
}

int main()
{
	int n, dice;
    int one = 0, two = 0, three = 0, four = 0, five = 0, six = 0;
    srand(time(NULL));

    cout << "Roll a dice 'n' times: ";
    cin >> n;

    for (int i = 0; i < n; i++){
        dice = rand() % 6 + 1; // 주사위 눈 랜덤
        
        // 주사위 눈에 따른 count
        switch(dice)
        {
        case 1:
            one += 1;
            break;
        case 2:
            two += 1;
            break;
        case 3:
            three += 1;
            break;
        case 4:
            four += 1;
            break;
        case 5:
            five += 1;
            break;
        case 6:
            six += 1;
            break;
        default:
            break;
        }
    }

    // one ~ six, draw() 호출
    // +) "1:" << draw(n, one) 같이 출력 안됨
    cout << "1:";
    draw(n, one);
    cout << "2:";
    draw(n, two);
    cout << "3:";
    draw(n, three);
    cout << "4:";
    draw(n, four);
    cout << "5:";
    draw(n, five);
    cout << "6:" ;
    draw(n, six);

	return 0;
}