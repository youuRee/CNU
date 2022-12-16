#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define clrscr() system("clear");
#define getKey() getchar();

class AbstractMenu {
    string title;
public:
    AbstractMenu(string s) : title(s) {}
    virtual ~AbstractMenu() {}

    string getTitle() {return title;}

    virtual void commend() = 0;
};

class MenuItem : public AbstractMenu {
    int id;
public:
    MenuItem(string s, int n) : AbstractMenu(s), id(n) {}

    virtual void commend() {
        cout << getTitle() << " is selected." << endl;
        getKey();
    }
};

class PopupMenu : public AbstractMenu {
    vector<AbstractMenu*> v;
public:
    PopupMenu(string s) : AbstractMenu(s) {}
    ~PopupMenu() {
        for (int i = 0; i < v.size(); i++)
            delete v[i];
    }
    void addMenu(AbstractMenu* p) { v.push_back(p); }

    virtual void commend() {
        while(true) {
            clrscr();

            int size = v.size();

            for (int i = 0; i < size; i++)
                cout << i + 1 << " " << v[i]->getTitle() << endl;
            cout << size + 1 << ". << Back";
            cout << "Select an item >> ";
            
            int cmd;
            cin >> cmd;

            if(cmd == size+1) break;
            if(cmd < 1 || cmd > size+1) continue;

            v[cmd-1]->commend();
            //cout << v[cmd-1] << " Execute! " << endl;
        }
    }
};

int main()
{
    PopupMenu* menubar = new PopupMenu("MENUBAR");

    PopupMenu* p1 = new PopupMenu("File");
    PopupMenu* p2 = new PopupMenu("Edit");

    menubar->addMenu(p1);
    menubar->addMenu(p2);

    p1->addMenu(new MenuItem("New file", 11));
    p1->addMenu(new MenuItem("New file", 12));
    p1->addMenu(new MenuItem("New file", 13));

    p2->addMenu(new MenuItem("Copy", 21));
    p2->addMenu(new MenuItem("Paste", 22));

    PopupMenu* p3 = new PopupMenu("Find");
    p2->addMenu(p3);

    p3->addMenu(new MenuItem("Find", 31));
    p3->addMenu(new MenuItem("Find and Replace", 32));

    menubar->commend();
    delete menubar;

}