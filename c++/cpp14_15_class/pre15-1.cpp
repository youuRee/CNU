#include <iostream>
using namespace std;

struct node {
	int data;
	node* next;
};

class my_list
{
private:
	node* head;
	node* tail;
    node* cur;
    // len : 리스트 길이 (append() 실행할 때 마다 +1)
    // cur_idx : 현재 index (nest() 실행할 때 마다 +1)
	int len, cur_idx;
public:
	my_list() {
		//head 와 tail의 포인터를 초기화;
		head = NULL;
		tail = NULL;
        cur = NULL;
		len = 0;
		cur_idx = 0;
	}

    // 체이닝 함수
    my_list& append(int n);
    my_list& next();
	
    int get() {return cur->data;}

	int rewind(){	
		cur_idx = 0;
		cur = head;
		return cur_idx;
	}

    void info() {
        cout << "length: " << len << ", current: " << cur_idx << endl;
    }
};

my_list& my_list::append(int n) {
	node* temp = new node; // temp: 현재 추가할 노드
	len += 1;
	
    // 새로운 노드 생성
	temp->data = n;
	temp->next = NULL;

    // linkedlist  비어있는 경우
	if (head == NULL) {
		head = temp;
		tail = temp;
	}
	
	else {
        // 새로운 노드를 linked list의 맨 끝 (tail)과 연결
		tail->next = temp;
		tail = temp;
	}
    //cout << tail << endl;
    return *this;
}

my_list& my_list::next() {
    if (cur == NULL) {
        // next() 처음 실행 시 cur은 NULL
        // next() 처음 실행하면 head의 다음 노드가 나와야 함
        cur = head->next;
    }
    else {
        cur = cur->next;
    }
	cur_idx += 1;
    //cout << cur << endl;
    return *this;
}

int main()
{
    my_list l;

    l.append(10).append(20).append(30).append(40); // 체이닝 사용!
    l.next().next();
    cout << l.get() << endl; // print out 30

    l.info(); // print out 'length: 4, current: 2 (or 3 depending on your start index)'
    l.rewind();
    cout << l.get() << endl; // print out 10 

    return 0;
}

