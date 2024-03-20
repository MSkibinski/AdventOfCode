#include <iostream>
#include <vector>
#include <complex>

using namespace std;

#define X real()
#define Y imag()

vector<complex<int>> currPositions, nextPositions;
vector<string> t;

int main() {
    string line;
    while (getline(cin, line)) {
        t.push_back(line);
        if (auto pos = line.find('S'); pos != string::npos)
            currPositions.push_back({static_cast<int>(pos), static_cast<int>(t.size())-1});
        cout << line << endl;
    }

    int result = 1;
    vector<complex<int>> m{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int maxX = t[0].size();
    int maxY = t.size();
    for (int i=0; i<64; i++) {
        for (auto pos : currPositions) {
            for (auto move : m) {
                auto nPos = pos + move;
                if (nPos.X >= 0 && nPos.X < maxX && nPos.Y >=0 && nPos.Y < maxY) {
                    if (t[nPos.Y][nPos.X] == '.') {
                        t[nPos.Y][nPos.X] = '#';
                        nextPositions.push_back(nPos);
                    }
                }
            }
        }

        swap(currPositions, nextPositions);
        nextPositions.clear();
        if(i%2) {
            // cout << currPositions.size() << endl;
            result += currPositions.size();
        }
    }

    cout << result << endl;
}
