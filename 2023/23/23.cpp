#include <iostream>
#include <vector>
#include <queue>
#include <complex>

#define X real()
#define Y imag()

using namespace std;

vector<string> m;

vector<complex<int>> moveDir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main() {
    string line;
    while(cin >> line)
        m.push_back(line);

    vector<vector<int>> path(m.size(), vector<int>(m[0].size(), 0));
    queue<complex<int>> curr;
    curr.push({1,1});

    while(!curr.empty()) {
        auto pos = curr.front(); curr.pop();
        int value = path[pos.Y][pos.X];
        for (auto mo : moveDir) {
            auto p = pos + mo;
            int val = value+1;
            if(m[p.Y][p.X] == 'v') {
                p += complex<int>{0, 1};
                val++;
            }
            if(m[p.Y][p.X] == '^') {
                p += complex<int>{0, -1};
                val++;
            }
            if(m[p.Y][p.X] == '>') {
                p += complex<int>{1, 0};
                val++;
            }
            if(m[p.Y][p.X] == '<') {
                p += complex<int>{-1, 0};
                val++;
            }

            if (m[p.Y][p.X]!='.' || p == pos) continue;
            if (path[p.Y][p.X]!=0 && (val-path[p.Y][p.X]==2 || val<path[p.Y][p.X])) continue;
            path[p.Y][p.X] = val;
            curr.push(p);
        }
    }
    // for (auto &line : path) {
    //     for (auto v : line) {
    //         cout << v << '\t';
    //     }
    //     cout << endl;
    // }
    for (auto v : path[path.size()-2]) {
        if (v != 0)
            cout << v << endl;
    }
}
