#include <iostream>
#include <vector>
#include <array>
#include <complex>
#include <queue>

using namespace std;

#define X real()
#define Y imag()

// enum Direction {
//     up,
//     left,
//     down,
//     right
// };

int up=0, left_=0, right_=0, down=0; 

int main()
{
    int x=0, y=0;
    char c;
    int len;
    string color;
    while (cin >> c >> len >> color) {
        switch (c) {
            case 'U': y -= len; up = min(up, y); break;
            case 'D': y += len; down = max(down, y); break;
            case 'L': x -= len; left_ = min(left_, x); break;
            case 'R': x += len; right_ = max(right_, x); break;
        }
    }

    cout << "y: " << up << " - " << down << endl;
    cout << "x: " << left_ << " - " << right_ << endl;
}
