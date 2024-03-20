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
        char &c = t[pos.Y][pos.X];
        switch(c) {
            case '|':
                c = '6'; 
                dir = dir==Dir::up ? Dir::up : Dir::down;
                break;
            case '-':
                c = '0';
                dir = dir==Dir::left ? Dir::left : Dir::right;
                break;
            case 'F':
                c = '1';
                dir = dir==Dir::up ? Dir::right : Dir::down;
                break;
            case '7':
                c = '4';
                dir = dir==Dir::up ? Dir::left : Dir::down;
                break;
            case 'J':
                c = '5';
                dir = dir==Dir::down ? Dir::left : Dir::up;
                break;
            case 'L':
                c = '2';
                dir = dir==Dir::down ? Dir::right : Dir::up;
                break;
        }
    } while(t[pos.Y][pos.X] != 'S');
    t[pos.Y][pos.X] = '6';

    int result = 0;
    for (auto &line : t) {
        cout << line << endl;
        int i=0;
        bool inside = false;
        for (auto c : line) {
            if (c == '0') continue;
            else if (c >= '1' && c <= '6') {
                i += c-'0';
                if (i==6) {
                    inside = !inside;
                    i = 0;
                }
                else if (i==7 || i==5) {
                    i = 0;
                }
            }
            else if (inside) {
                result++;
            }
        }
    }

    cout << result << endl;
}