#include <iostream>
using namespace std;

// overloading : 함수 이름 같지만 파라미터(인자)의 타입, 개수 다름
// templates : template <typename x>

// template으로 함수 설정
template <typename T, typename U> // 받을 인자 타입 2개 -> T, U 설정
T calculation (U oper, T x, T y)
{
    T result;
    // operator에 따라 달라지는 result -> if문
    if (oper == '+') result =  x+y;
    else if (oper == '-') result = x-y;
    else if (oper == '*') result = x*y;
    else result = x/y;
    return result;
}

int main()
{
    char oper;
    int n1, n2;

    while(true){
        
        cout << "Select an operator: ";
        cin >> oper;
        if (oper == 'Q') break; // Q 입력 -> 종료

        cout << "Input two number: ";
        cin >> n1 >> n2;
        cout << "Answer: " << calculation(oper, n1, n2) << endl;
    }

    return 0;
}
