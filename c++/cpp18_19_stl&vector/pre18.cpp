#include <iostream>
#include <vector>
#include <map>
using namespace std;

class phonebook
{
  map<int, vector<string> > table;

public:
  int hash(const string &s)
  {
    int ret = 0;
    for(auto i: s) ret += i;
    return ret%8;
  }

  void input(const string &name, const string &number)
  {
    // name = chonnam (문자열), &name = address(주소) => number도 마찬가지
    // name == key
    // + key -> 이미 존재하는 key -> 그 key에 해당하는 table의 vecl에 연결해서 자장
    int key = hash(name);

    // key 없는 경우 -> 새로운 vector 만들어서 table의 값(table[key])에 저장
    if (table.count(key) == 0){
        vector <string> vecl;
        vecl.push_back(number);
        table[key] = vecl;
    }
    // key 이미 존재 -> 해당되는 table의 값 자리에 이어서 저장
    else {
        table[key].push_back(number);
    } 

  }


  void get(const string &name) 
  {
    int key = hash(name);
    cout << "***get: " << name << " / key: " << key << endl;

    if (table[key].size() == 0) {
        cout << table[key][0] << endl;
    }
    else {
        for(int i = 0; i < table[key].size(); i++)
            cout << table[key][i] << endl;
    }
    cout << endl;
  }
};



int main() {

    phonebook p;

    p.input("chonnam", "111-1111");
    p.input("national", "222-2222");
    p.input("university", "333-3333");
    p.input("c++", "444-4444");
    p.input("programming", "555-5555");
    p.input("and", "666-6666");
    p.input("practice", "777-7777");

    p.get("chonnam");
    p.get("national");
    p.get("university");
    p.get("c++");
    p.get("programming");
    p.get("and");
    p.get("practice");

}

