#include <iostream>
using namespace std;

const int MAX = 100;
class my_queue
{
private:
    int arr[MAX]; // 큐 최대범위 = 100
    int q_size, f_idx, b_idx;
public:
    my_queue(){
        q_size = 0; // 큐의 크기
        f_idx = 0; // 큐의 맨 앞
        b_idx = 0; // 큐의 맨 뒤
    }
    void Enqueue(int n){
        arr[b_idx] = n;
        b_idx += 1;
        q_size += 1;
    }
    void Dequeue(){
        if (q_size == 0) cout << "삭제할 원소 없음!" << endl;
        else f_idx += 1;
        q_size -= 1;
    }
    int Peek(){
        return arr[f_idx];
    }

};

int main()
{
    // Enqueue (큐의 꼬리에 데이터를 집어 넣는 것)
    // Dequeue (큐의 머리에서 데이터를 가져 오는 것)
    // Peek (머리의 데이터만 참조하는 것)

    my_queue q;

    // 내 마음대로 큐 구성 (my_queue class use)
    q.Dequeue();
    q.Enqueue(0);
    q.Enqueue(1);
    q.Enqueue(2);
    q.Dequeue();
    cout << q.Peek() << endl;
    q.Enqueue(3);
    q.Enqueue(4);
    q.Dequeue();
    cout << q.Peek() << endl;
    q.Enqueue(5);
    q.Dequeue();
    cout << q.Peek() << endl;

    return 0;
}