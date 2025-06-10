#include <iostream>
#include <sstream>
#include <vector>
#include <complex>

using namespace std;

enum Dir {
    up,
    right,
    down,
    left
};
vector<complex<int>> delta = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

#define X real()
#define Y imag()

int main() {
    string line;

    int result = 0;
    vector<string> t;
    complex<int> pos;
    for (getline(cin, line); line.size(); getline(cin, line)) {
        if (int p = line.find('S'); p != string::npos) {
            pos = {p, t.size()};
        }
        t.push_back(line);
    }

    int length = 0;
    Dir dir = Dir::down;
    do {
        pos += delta[dir];
        length++;
        char c = t[pos.Y][pos.X];
        switch(c) {
            case '|': dir = dir==Dir::up ? Dir::up : Dir::down; break;
            case '-': dir = dir==Dir::left ? Dir::left : Dir::right; break;
            case 'F': dir = dir==Dir::up ? Dir::right : Dir::down; break;
            case '7': dir = dir==Dir::up ? Dir::left : Dir::down; break;
            case 'J': dir = dir==Dir::down ? Dir::left : Dir::up; break;
            case 'L': dir = dir==Dir::down ? Dir::right : Dir::up; break;
        }
    } while(t[pos.Y][pos.X] != 'S');

    cout << length/2 << endl;
}