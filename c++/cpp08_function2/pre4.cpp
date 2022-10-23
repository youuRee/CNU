#include <iostream>
using namespace std;

/*
하노이탑 알고리즘 원리
원판 n개를 A -> C 이동
1. n-1개를 먼저 중간에 있는 B에 두기
(이동시킬 원판보다 한단계 큰 원판은 C에 두기)
3. n-1개의 원판은 B -> C 이동
*/

void hanoi(int n, char start, char end, char mid)
{
    if (n == 1){
        cout << n << " : " << start << " -> " << end << endl;
    }
    else{
        hanoi(n-1, start, mid, end);
        cout << n << " : " << start << " -> " << end << endl;
        hanoi(n-1, mid, end, start);
    }

}
int main()
{
    int disk;
    cout << "Enter the number of disks: ";
    cin >> disk;
    hanoi(disk, 'A', 'C', 'B');

    return 0;
}