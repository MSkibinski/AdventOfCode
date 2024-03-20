#include <iostream>
#include <vector>
#include <complex>

using namespace std;

#define X real()
#define Y imag()

const int STEPS = 26'501'365;
const int SIZE = 131;
const int fullBlocksInOneDir = (STEPS / SIZE) - 1;
const long long blocksNegative = static_cast<long long>(fullBlocksInOneDir+1) * static_cast<long long>(fullBlocksInOneDir+1);
const long long blocksLikeStarting = static_cast<long long>(fullBlocksInOneDir) * static_cast<long long>(fullBlocksInOneDir);

// corner in starting block is positive


vector<string> t;

int calculate(complex<int> pos, int steps) {
    vector<complex<int>> currPositions, nextPositions;
    vector<complex<int>> m{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    vector<string> t2 = t;

    currPositions.push_back(pos);
    t2[pos.Y][pos.X] = '#';
    int result = steps%2==0 ? 1 : 0;
    for (int i=0; i<steps; i++) {
        for (auto pos : currPositions) {
            for (auto move : m) {
                auto nPos = pos + move;
                if (nPos.X >= 0 && nPos.X < SIZE && nPos.Y >=0 && nPos.Y < SIZE) {
                    if (t2[nPos.Y][nPos.X] == '.') {
                        t2[nPos.Y][nPos.X] = '#';
                        nextPositions.push_back(nPos);
                    }
                }
            }
        }

        swap(currPositions, nextPositions);
        nextPositions.clear();
        if((steps - i) % 2) {
            // cout << currPositions.size() << endl;
            result += currPositions.size();
        }
    }
    return result;
}

int main() {
    string line;
    while (getline(cin, line))
        t.push_back(line);

    int positive = calculate({0, 0}, 500);
    int negative = calculate({0, 0}, 501);

    cout << "positive: " << positive<< " , negative: " << negative << endl;
    cout << "blocksLikeStarting: " << blocksLikeStarting<< " , blocksNegative: " << blocksNegative << endl;
    cout << "fullBlocksInOneDir: " << fullBlocksInOneDir << endl;

    long long result = blocksNegative * positive + blocksLikeStarting * negative;
    result += fullBlocksInOneDir * calculate({0, 0}, 131+64);
    result += fullBlocksInOneDir * calculate({0, 130}, 131+64);
    result += fullBlocksInOneDir * calculate({130, 0}, 131+64);
    result += fullBlocksInOneDir * calculate({130, 130}, 131+64);

    result += (fullBlocksInOneDir+1) * calculate({0, 0}, 64);
    result += (fullBlocksInOneDir+1) * calculate({0, 130}, 64);
    result += (fullBlocksInOneDir+1) * calculate({130, 0}, 64);
    result += (fullBlocksInOneDir+1) * calculate({130, 130}, 64);

    result += calculate({0, 65}, 130);
    result += calculate({130, 65}, 130);
    result += calculate({65, 0}, 130);
    result += calculate({65, 130}, 130);

    cout << result << endl;
}
