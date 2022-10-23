#include <iostream>
#include <cmath>
using namespace std;

template <typename T> // 편하게 타입 지정은 템플릿으로~!
T dist_2d(T x1, T x2, T y1, T y2)
{
    // 두 점 사이의 거리 바로 반환
    // sqrt : 제곱근, pow : n제곱 -> 둘다 cmath 라이브러리
    return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}

int main()
{
    double x1, x2, y1, y2;

    //  좌표 입력
    cout << "input x1, y1: ";
    cin >> x1 >> y1;
    cout << "input x2, y2: ";
    cin >> x2 >> y2;

    // 거리 출력
    cout << "Distance: " << dist_2d(x1, x2, y1, y2) << endl;
    return 0;
}