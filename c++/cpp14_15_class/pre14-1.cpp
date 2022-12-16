#include <iostream>
using namespace std;

class my_calc
{
private:
    int a, b;
public:
    // my_clac : 생성자 (class 이름과 같음)
    my_calc(int x, int y):a(x), b(y) // 초기화 리스트
    {
    }
    int add(){
        return a+b;
    }
    int sub(){
        return a-b;
    }
    int mul(){
        return a*b;
    }
    int div(){
        if (b == 0) cout << "0으로 나눌 수 없음!" << endl;
        return a/b;
    }
}; // class 끝에 ; 필수!

int main()
{
    my_calc c(10,20);

    cout << c.add() << endl;
    cout << c.sub() << endl;
    cout << c.mul() << endl;
    cout << c.div() << endl;

    return 0;
}