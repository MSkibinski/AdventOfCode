#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> directoriesSizes;

struct Dir {
    Dir *parent;
    map<string, Dir> dirs;
    int size=0;

    int calculateSize() {
        for (auto &[name, child] : dirs)
            size += child.calculateSize();

        directoriesSizes.push_back(size);
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
    int spaceRequired = root.calculateSize() - 40'000'000;

    int result = 70'000'000;
    for (auto v : directoriesSizes) {
        if (v >= spaceRequired && v < result)
            result = v;
    }

    cout << result;
}