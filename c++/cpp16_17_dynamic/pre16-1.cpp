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

    void printall();
    // + : append
    // ll + 100 + 200 ... == ll.append(100).append(200)
    my_list& operator +(int n) {
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
	// ll + l
    my_list& operator +(my_list &ref) {
        // 현재 tail : ll의 맨 끝
        // l을 인자로 받은 ref의 head가 ll의 tail과 연결
        tail->next = ref.head;
        return *this;
    }
    // - : remove
    my_list& operator -(int n) {
        node* temp = new node;
        temp = head;

        // n-1번 idx를 temp에 저장 (for문 이용)
        for (int i = 1; i < n; i++) {
            temp = temp->next;
        }
        // n-1번 idx의 next는 n의 next(n-1의 next next)
        temp->next = temp->next->next;

        return *this;
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

void my_list::printall() {
    node* temp = new node;
    temp = head;

    while(temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    my_list l;
    my_list ll;

    l.append(10).append(20).append(30).append(40);
    l.next().next();

    cout << l.get() << endl; // print out 30
    // nb1 + nb2 = nb1.operator+(nb2)
    // ll + 100 + 200 = ll.operator+(100).operator+(200)
    ll = ll + 100 + 200 + 300; // append values 100, 200 and 300 to ll.

    ll.next();
    cout << ll.get() << endl; // print out 200

    ll = ll + l; // concatenate the list 'l' to the list 'll';

    // The list 'll' would be '[100][200][300][10][20][30][40]'

    // index:   0    1    2   3   4   5   6

    ll.printall();

    ll.next().next().next();
    cout << ll.get() << endl; // print out 20
    // 5 -> operator -의 인자
    ll = ll - 5; // remove the 5-th node.
    ll.next();
    cout << ll.get() << endl; // print out 40, not 30. 
    ll.printall();


}