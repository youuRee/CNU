// 1. mystrcat
#include <iostream>
#include <string>
using namespace std;

char* mystrcat(const char *str1, const char *str2)
{
    char tmp[20];
    // tmp : str1 + str2
    // strcat : 두 문자열 합치는 함수
    strcat(tmp, str1);
    strcat(tmp, str2);

    const int size = strlen(tmp) + 1; // tmp 문자열 길이
    char* s = new char[size]; // tmp 길이 만큼 동적 할당
    strcpy(s, tmp); // tmp를 s에 복사

    return s;
}

int main()
{
    char *str = mystrcat("Hello!", "World!");
    cout << str << endl;   

    return 0;
}

