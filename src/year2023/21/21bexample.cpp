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
        if (auto pos = line.find('S'); pos != string::npos){
            currPositions.push_back({static_cast<int>(pos)+500*11, static_cast<int>(t.size())-1+500*11});
            t.back()[pos] = '.';
        }
        // cout << line << endl;
    }

    for (auto &row : t) {
        string s = row;
        row.reserve(1000*row.size());
        for (int i=1; i<1000; i++)
            row += s;
    }
    t.reserve(1000*t.size());
    for (int i=1; i<1000; i++) {
        for (int j=0; j<11; j++)
            t.push_back(t[j]);
    }
    // cout << t.size() << " " << t.back().size() << endl;
    t[currPositions[0].Y][currPositions[0].X] = '#';

    int result = 1;
    vector<complex<int>> m{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    for (int i=0; i<5000; i++) {
        for (auto pos : currPositions) {
            for (auto move : m) {
                auto nPos = pos + move;
                if (nPos.X >= 0  && nPos.Y >=0) {
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

    for (auto &row : t) {
        cout << row << endl;
    }

    cout << result << endl;
}
