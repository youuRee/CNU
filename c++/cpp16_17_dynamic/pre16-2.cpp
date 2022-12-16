#include <iostream>
using namespace std;

struct node {
	int data;
	node* next;
    int index;

    node(int d, node* n, int i) : data(d), next(n), index(i) {}
};

class slist
{
private:
    node* head;
    node* current;
    node *tail;
    int index;
public:
    slist() : head(0), current(0), index(0), tail(0) {}
    // push front : stack과 유사 -> 10 - 20 - 30 (head)
    // AA(d=10 head=0) -> BB(d=20 head=AA) -> CC(d=30 head=BB)
    void push_front(const int &d) 
    {
        head = new node(d, head, index++);
    }
    
    void push_back(const int &d) 
    {
        //node* temp = new node(d, NULL, index++);
        // node 값 == NULL -> 연결 안됨, 무조건 값 채우기!!
        if(!head){
            tail = new node(d, NULL, index++);
            head = tail;
        }
        else {
            tail->next = new node(d, NULL, index++);
            tail = tail->next;
        }
    }

    slist& next()
    {
        if (!current) current = head;
        else current = current->next;

        return *this;
    }
    int get() { return current->data; }

    // list를 배열처럼 출력 -> 연산자 오버로딩 이용!
    int operator[ ](int i)
    {
        node* s;
        // s의 index가 i가 아닐때 까지 반복 (i이면 그떄의 s 리턴)
        for(s = head; s->index != i; s = s->next);
        return s->data;
    }

    void printall() {
        node* temp;
        temp = head;

        while(temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    cout << endl;
    }
};

int main()
{
    slist s;

    cout << "push front" << endl;
    s.push_front(10);
    s.push_front(20);
    s.push_front(30);

    cout << s.next().get() << endl;
    cout << s.next().get() << endl;
    cout << s.next().get() << endl;
    s.printall();
    cout << endl;

    cout << "list like to array" << endl;
    cout << s[0] << endl;
    cout << s[1] << endl;
    cout << s[2] << endl;
    cout << endl;

    slist s2;

    s2.push_back(40);
    s2.push_back(50);
    s2.push_back(60);

    cout << "push back" << endl;
    cout << s2.next().get() << endl;
    cout << s2.next().get() << endl;
    cout << s2.next().get() << endl;
    s2.printall();
    cout << endl;

    cout << "list like to array" << endl;
    cout << s2[0] << endl;
    cout << s2[1] << endl;
    cout << s2[2] << endl;
    cout << endl;

}