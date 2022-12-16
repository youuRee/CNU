#include <iostream>
using namespace std;

int main()
{
    int *iptr;
    char *cptr = "Hello";
    void *vptr;

    cout << cptr << endl;
    cout << sizeof(cptr) << endl;
    
    cout << sizeof(*cptr) << endl;
    cout << "=================" << endl;

    for (int i = 0; i < sizeof(cptr); i++){
        cout << &(cptr)+i << endl;
        cout << *(&(cptr)+i) << endl;
        cout << cptr+i << endl;
        cout << (char)(*cptr+i) << endl;
        cout << &(*cptr+i) << endl;
        cout << endl;
    }
    

    return 0;
}