// 1. Touring the 2D array with a pointer 
#include <iostream>
using namespace std;

int main()
{ 
  int arr[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
  int **ptr2;
  int *ptr1;

  // Solve 1
  cout << "Only ptr1" << endl;
  for (int i = 0; i < 3; i++){
    ptr1 = &arr[i][0]; // ptr1 : i행의 모든 열(원소)
    for (int j = 0; j < 4; j++){
      cout << *ptr1 + j << " ";
    }
    cout << endl;
  }
  // Solve 2
  cout << endl;
  cout << "Use ptr2" << endl;
  for (int i = 0; i < 3; i++){
    ptr1 = &arr[i][0]; // ptr1 : i행의 모든 열(원소)
    ptr2 = &ptr1; // ptr2 : ptr1을 가르키는 2차원 포인터
    for (int j = 0; j < 4; j++){
      cout << **ptr2 + j << " "; // ptr2는 ptr1의 주소르 가르킴, ptr1 + j와 동치
    }
    cout << endl;
  }
  
  return 0;
}