#include <iostream>
using namespace std;

// 거듭제곱(n^k) 구하는 함수
long ipower(int n, int k)
{
    long result = 1;
    
    // k번 만큼 n을 곱함
    for (int i = 0; i < k; i++){
        result *= n;
    }
    return result;
}

int main()
{
	int num;
    cout << "input number: ";
    cin >> num;

    // 지수(k) : 0 ~ 10
    for (int i = 0; i <= 10; i++){
        cout << num << "^" << i << " = " << ipower(num, i) << endl;
    }
	return 0;
}