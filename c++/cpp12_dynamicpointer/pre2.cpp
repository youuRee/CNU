// 2. Reverse linked list
#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct list {
    T value;
    struct list<T> *next;
};

template <typename T>
list<T> *append(T value)
{
    list<T> *node = new(list<T>);
    node->value = value;
    node->next = NULL;

    return node;
}

template <typename T>
list<T> *append(list<T> *tail, T value)
{
    list<T> *node = new(list<T>);
    node->value = value;
    node->next = NULL;

    tail = tail->next = node;

    return node;
}

template <typename T>
list<T>* reverse(list<T> *head){
	list<T> *cur, *prev, *tmp; // 3개의 연결리스트 생성
    cur = head;
    prev = NULL;

    // prev는 cur을 따라가고 tmp는 prev를 따라감
    // prev의 그 자체는 cur을 따라가지만 prev의 다음 노드는 tmp를 가르킴
    while(cur != NULL){
        tmp = prev;
        prev = cur;
        cur = cur->next;
        prev->next = tmp;
    }
    head = prev; // prev는 reverse된 연결리스트
    return prev;
}

int main()
{
    list<int> *head;
    list<int> *loop;
    list<int> *tail;
    list<int> *r_head;

    tail = head = append(10);
    tail = append(tail, 20);
    tail = append(tail, 30);
    tail = append(tail, 40);

    for( loop = head ; loop != NULL; loop = loop->next)
    {
      cout << loop->value << endl;
    }

    r_head = reverse(head);
    cout << "Reversed" << endl;

    for( loop = r_head ; loop != NULL; loop = loop->next)
    {
      cout << loop->value << endl;
    }

    return 0;

}