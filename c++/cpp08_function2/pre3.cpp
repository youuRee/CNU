#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str, new_str;
    int len, new_len, cnt = 1;

    cout << "input number: ";
    cin >> str; // 숫자를 문자열 형식으로 입력받기

    // 입력받은 문자열 길이 (length() -> string 라이브러리)
    len = str.length();
    new_str = str[len-1];

    // new_str : reverse str -> stack(LIFO) 원리 이용
    for (int i = len-2; i >= 0; i--){
        new_str += str[i];
        cnt += 1;
        // new_str에 3번씩 추가(cnt==3)될 때 마다 ',' 붙이기
        if (cnt == 3 && (i != 0)) {
            new_str += ',';
            cnt = 0;
        }
        // cout << new_str << endl;
    }
    
    new_len = new_str.length();
    // new_str 거꾸로 출력
    for (int j = new_len-1; j >= 0; j--){
        cout << new_str[j];
    }
    cout << endl;
    return 0;
}