#include <iostream>
using namespace std;

//노드 struct 구현 (data값과 nextNode가 존재)
struct node {
	int data;
	node* nextNode;
};

//링크드 리스트 클래스 생성
class LinkedList {
private:
	node* head;
	node* tail;
    node* cur;
	int len, cur_idx;
public:
	LinkedList() {
		//head 와 tail의 포인터를 초기화;
		head = NULL;
		tail = NULL;
        cur = NULL;
		len = 0;
		cur_idx = 0;
	}

	//마지막의 node 추가
	LinkedList& addNode(int n);
    LinkedList& next();
	
    int get() {return cur->data;}
	int info() {return len;}

	int rewind(){	
		cur_idx = 0;
		cur = head;
		return cur_idx;
	}
	//첫번째 노드 가져오기
	node* getHead() {
		return head;
	}
	//LinkedList 출력
	void display(node* head);
};


//마지막의 node 추가
LinkedList& LinkedList::addNode(int n) {
	node* temp = new node;
	len += 1;
	//temp의 데이터는 n
	temp->data = n;
	//temp의 nextNode = NULL값
	temp->nextNode = NULL;

	//LinkedList가 비어있으면
	if (head == NULL) {
		//첫 node는 temp
		head = temp;
		//마지막 node는 temp
		tail = temp;
	}
	//LinkedList에 데이터가 있으면
	else {
		//현재 마지막 node의 nextNode는 temp
		tail->nextNode = temp;
		//마지막 node는 temp
		tail = temp;
	}
    cout << tail << endl;
    return *this;
}

LinkedList& LinkedList::next() {
    if (cur == NULL) {
        cur = head;
    }
    else {
        cur = cur->nextNode;
    }
	cur_idx += 1;
    cout << cur << endl;
    return *this;
}

//LinkedList 출력
void LinkedList::display(node* head) {
	if (head == NULL) {
		cout << "\n";
	}
	else {
		cout << head->data << " ";
		display(head->nextNode);
	}
	cout << endl;
}

//메인 함수
int main() {
	LinkedList a;

	a.addNode(1).addNode(2).addNode(3);
	a.next().next();
	cout << a.get() << endl;
    
	a.rewind();
    cout << a.get() << endl;

    return 0;
}
