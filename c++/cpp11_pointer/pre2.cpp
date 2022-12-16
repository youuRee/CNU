#include <iostream>
using namespace std;

void *my_memcpy(void *destination, const void *source, size_t num)
{
    // 해당 시스템에서 어떤 객체나 값이 포함할 수 있는 최대 크기의 데이터를 
    // 표현하는 타입으로 반드시 unsigned 형 (32bit 운영체제 -> unsigned 32bit 정수)
    char i;

    if (destination == NULL && source == NULL)
        return destination;

    for (i = 0; i < num; i++){
        cout << "source[i] : " << ((unsigned char *)source)[i] << endl;
        cout << sizeof(((unsigned char *)source)[i]) << endl; // 1byte -> idx를 지정해 원소를 가르킴
        // 왜 한 글자가 아니라 전체가 출력? and 주소가 아니라 글자가 나오는 이유? -> Maybe 주소를 문자 타입으로 바꿔서? (Hello가 그냥 주소)
        // 0x12345678 -> 이 주소에 각각 어떤 값이 들어있는지 확인, ex) 12 -> a, 34 -> c ...
        cout << "source + i : " << ((unsigned char *)source)+ i << endl;
        cout << sizeof(((unsigned char *)source)+i) << endl; // 8byte -> 주소 그 자체라서
        // 1byte -> *를 사용해서 주소보단 배열과 비슷
        cout << "*(source + i) : " << *((unsigned char *)source+i) << endl; // arr[i] == *(arr+i)
        ((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
    }

    return destination;
}


int main()
{
  char *csrc = "Hello";

  char cdst[16];

  int isrc = 12345678;
  int idst;

  my_memcpy(cdst, csrc, sizeof(csrc));
  my_memcpy(&idst, &isrc, sizeof(isrc));

  cout << cdst << endl;
  cout << idst << endl; 

  return 0;

}