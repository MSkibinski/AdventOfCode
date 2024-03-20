#include <iostream>
#include <complex>
#include <set>

using namespace std;

auto cmp = [](const complex<int> &a, const complex<int> &b) { 
    return a.real() != b.real() ? a.real()<b.real() : a.imag()<b.imag();
};
set<complex<int>, decltype(cmp)> visited(cmp);

class Snake {
    complex<int> head;
    complex<int> tail;

public:
    void move(complex<int> &dd) {
        auto last = head;
        head += dd;
        if (abs(tail-head) >= 2) {
            tail = last;
            visited.insert(tail);
        }
    }
};

int main() {
    char dir;
    int n;

    Snake snake;
    visited.insert({0, 0});
    while (cin >> dir >> n) {
        complex<int> dd;
        switch (dir) {
            case 'U': dd = { 0,  1}; break;
            case 'D': dd = { 0, -1}; break;
            case 'R': dd = { 1,  0}; break;
            case 'L': dd = {-1,  0}; break;
        }
        while (n--) {
            snake.move(dd);
        }
    }

    cout << visited.size() << endl;
}
