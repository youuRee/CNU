#include <iostream>
#include <vector>
using namespace std;

class my_queue: private vector<int> { 
private:
    vector<int> v;
public:

/*
    vector<int> v; 

 - 원소 앞부분(index [0])에 추가: v.insert(v.begin(), [value]);

 - 가장 끝부분 원소 읽기: v.back();

 - 가장 마지막 원소 삭제: v.pop_back();
*/

  // 큐의 꼬리에 데이터를 집어 넣기
    void enqueue(int value) {
        v.insert(v.begin(), value);
  }
  
  // 큐의 머리에서 데이터를 제거
    void dequeue() {
        v.pop_back();
  }

  // 머리의 데이터만 참조
    int peek() {
        return v.back();
  }

};

int main()
{
    my_queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    cout << q.peek() << endl; // 10
    q.dequeue();
    cout << q.peek() << endl; // 20
    q.dequeue();
    cout << q.peek() << endl; // 30
    q.dequeue();
    cout << q.peek() << endl; // 40
    q.dequeue();

}