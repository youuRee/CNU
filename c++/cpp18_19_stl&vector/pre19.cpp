#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()

{

  vector<char> v{ 'a', 'b', 'b', 'a', 'e', 'd', 'd', 'b'};

  for(auto i: v) cout << i << " "; cout << endl; // a b b a e d d b
  
  // unique : 연달아 나온 중복된 숫자들을 뒤로 보냄
  // 1,1,2,3,3,4 -> 1,2,3,4,1,3 (ret 주소 = 중복된 숫자의 첫부분)
  
  // 정렬x -> unique => a b a e d b
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());

  for(auto i: v) 
    cout << i << " "; 
    
  cout << endl; // a b d e

}