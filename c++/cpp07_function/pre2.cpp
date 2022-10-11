#include <iostream>
using namespace std;

// 소수 판별 함수
bool is_prime(int n)
{
    bool result = true; // default = true(소수)
    // 소수가 아닌 경우
    if (n == 0 || n == 1) result = false;
    else{
        for (int i = 1; i < n; i ++){
            if (i != 1 && n % i == 0){
                result = false;
                break;
            }
        }
    }
    return result;
}
int main()
{
	int num;

    while(true){
        cout << "input number: ";
        cin >> num;

        if (num == -1) break; // num = -1이면 반복문 종료

        // 소수인 경우와 소수가 아닌 경우 출력 다르게
        if(is_prime(num)){
            cout << num << " is a prime number." << endl;
        }
        else{
            cout << num << " is not a prime number." << endl;
        }

    }
    cout << "Done." << endl;
	return 0;
}