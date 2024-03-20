#include <iostream>
#include <vector>
#include <complex>
#include <set>

using namespace std;

auto cmp = [](const complex<int> &a, const complex<int> &b) { 
    return a.real() != b.real() ? a.real()<b.real() : a.imag()<b.imag();
};
set<complex<int>, decltype(cmp)> visited(cmp);

class Snake {
    vector<complex<int>> body;

public:
    Snake() : body(10) {}

    void move(complex<int> &dd) {
        body[0] += dd;
        for (int i=1; i<10; i++) {
            auto x = body[i-1] - body[i];
            if (abs(x) >= 2) {
                if (abs(x.real()) == 2) x.real(x.real()/2);
                if (abs(x.imag()) == 2) x.imag(x.imag()/2);
                body[i] += x;
            }
        }
        visited.insert(body[9]);
    }
};

int main() {
    char dir;
    int n;

    Snake snake;
    
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
