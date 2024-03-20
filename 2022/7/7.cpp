#include <iostream>
#include <map>

using namespace std;

int result = 0;

struct Dir {
    Dir *parent;
    map<string, Dir> dirs;
    int size=0;

    int calculateSize() {
        for (auto &[name, child] : dirs)
            size += child.calculateSize();

        if (size <= 100000)
            result += size;

        return size;
    }
};

int main()
{
    Dir root;
    Dir *current = &root;

    string line;
    for (getline(cin, line); !cin.eof(); getline(cin, line)) {
        if (line[0] == '$') {
            if (line=="$ ls")
                continue;
            line = line.substr(5);
            current = line==".." ? current->parent : &current->dirs[line];
        }
        else {
            if (line[0] == 'd') {
                line = line.substr(4);
                auto &child = current->dirs[line];
                child.parent = current;
            }
            else {
                current->size += stoi(line);
            }
        }
    }
    root.calculateSize();
    cout << result << endl;
}