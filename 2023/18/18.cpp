#include <iostream>
#include <vector>
#include <array>
#include <complex>
#include <algorithm>

using namespace std;

#define X real()
#define Y imag()

// $ ./18a.exe < example.txt
// y: 0 - 9
// x: 0 - 6

// skibi@Komp2 MINGW64 /f/Programowanie/AdventOfCode/2023/18
// $ ./18a.exe < input.txt
// y: -307 - 8
// x: -125 - 231


// enum Direction {
//     up,
//     left,
//     down,
//     right
// };

int up=0, left_=0, right_=0, down=0;
int x=126, y=307;

vector<string> v;

void mark(int &p, int d, int n) {
    while (n--) {
        p += d;
        v[y][x] = '#';
    }
}

void fill(int y, int x) {
    if (v[y][x]=='#') return;
    v[y][x] = '#';
    fill(y-1, x);
    fill(y+1, x);
    fill(y, x-1);
    fill(y, x+1);

}

int main()
{
    char c;
    int len;
    string color;

    v = vector<string>(320, string(360, '.'));
    while (cin >> c >> len >> color) {
        switch (c) {
            case 'U': mark(y, -1, len); break;
            case 'D': mark(y, 1, len); break;
            case 'L': mark(x, -1, len); break;
            case 'R': mark(x, 1, len); break;
        }
    }

    fill(308, 128);

    int result = 0;
    for (auto &line : v)
        result += count_if(line.begin(), line.end(), [](char c){return c=='#';});

    cout << result << endl;
}
