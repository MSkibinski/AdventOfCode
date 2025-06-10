#include <iostream>
#include <vector>
#include <complex>
#include <numeric>

using namespace std;

#define X real()
#define Y imag()

enum Direction {
    up,
    down,
    left,
    right
};

class Contraption {
    int height;
    int width;
    vector<string> grid;
    vector<vector<bool>> energized;

    static vector<complex<int>> d;

public:
    void init() {
        string line;
        while (cin >> line)
            grid.push_back(line);
        height = grid.size();
        width = grid[0].size();

        energized = vector<vector<bool>>(height, vector<bool>(width, false));
    }

    void processBeam(complex<int> pos, Direction dir) {
        for (pos += d[dir]; pos.X >= 0 && pos.X < width && pos.Y >= 0 && pos.Y < height; pos += d[dir]) {
            // cout << pos.Y << " " << pos.X << endl;
            switch (grid[pos.Y][pos.X]) {
                case '-':
                    if (energized[pos.Y][pos.X]) return;
                    if (dir == Direction::up || dir == Direction::down) {
                        energized[pos.Y][pos.X] = true;
                        processBeam(pos, Direction::left);
                        processBeam(pos, Direction::right);
                        return;
                    }
                    break;
                case '|':
                    if (energized[pos.Y][pos.X]) return;
                    if (dir == Direction::left || dir == Direction::right) {
                        energized[pos.Y][pos.X] = true;
                        processBeam(pos, Direction::up);
                        processBeam(pos, Direction::down);
                        return;
                    }
                    break;
                case '\\':
                    switch (dir) {
                        case Direction::up:    dir = Direction::left; break;
                        case Direction::down:  dir = Direction::right; break;
                        case Direction::left:  dir = Direction::up; break;
                        case Direction::right: dir = Direction::down; break;
                    }
                    break;
                case '/':
                    switch (dir) {
                        case Direction::up:    dir = Direction::right; break;
                        case Direction::down:  dir = Direction::left; break;
                        case Direction::left:  dir = Direction::down; break;
                        case Direction::right: dir = Direction::up; break;
                    }
            }
            energized[pos.Y][pos.X] = true;
        }
    }

    int getEnergy() {
        int result = 0;
        for (auto &line : energized)
            result += accumulate(line.begin(), line.end(), 0);
        return result;
    }
};

vector<complex<int>> Contraption::d{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int getHash(const string &s) {
    int hash = 0;
    for (auto c : s)
        hash = ((hash + c) * 17) % 256;
    return hash;
}

int main()
{
    Contraption contraption;
    contraption.init();

    contraption.processBeam({-1, 0}, Direction::right);
    cout << contraption.getEnergy() << endl;
}
