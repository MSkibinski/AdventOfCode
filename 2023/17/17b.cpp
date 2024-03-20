#include <iostream>
#include <vector>
#include <array>
#include <complex>
#include <queue>

using namespace std;

#define X real()
#define Y imag()

enum Direction {
    up,
    left,
    down,
    right
};

vector<string> dir2str{"up", "left", "down", "right"};

class Crucible {
    vector<vector<int>> m;
    vector<vector<array<int, 4>>> best;
    int height;
    int width;

    static vector<complex<int>> d;

public:
    void init() {
        string line;
        while (cin >> line) {
            m.push_back(vector<int>(line.size()));
            auto &row = m.back();
            for (int i=0; i<line.size(); i++)
                row[i] = line[i]-'0';
        }
        height = m.size();
        width = m[0].size();

        best = vector<vector<array<int, 4>>>(height, vector<array<int, 4>>(width, {0, 0, 0, 0}));
    }

    int findPath() {
        struct Coord {
            int val;
            complex<int> p;
            Direction dir;

            bool operator<(const Coord &c2) const {
                if (val != c2.val)
                    return val > c2.val;
                else if (p != c2.p) {
                    int a = p.X + p.Y;
                    int b = c2.p.X + c2.p.Y;
                    if (a != b)
                        return a < b;
                    return p.X < c2.p.X;
                }
                return dir < c2.dir;
            }
        };

        priority_queue<Coord> q;
        q.push({0, {0, 0}, Direction::right});
        q.push({0, {0, 0}, Direction::down});

        int result = 1'000'000;
        while (true) {
            auto coord = q.top(); q.pop();
            if (coord.val >= result) return result;

            for (int i=1; i<=10; i++) {
                coord.p += d[coord.dir];
                
                if (coord.p.X < 0 || coord.p.X == width || coord.p.Y < 0 || coord.p.Y==height)
                    break;

                coord.val += m[coord.p.Y][coord.p.X];
                if (i < 4) continue;

                if (coord.p.X == width-1 && coord.p.Y == height-1) {
                    result = min(result, coord.val);
                }

                auto &b = best[coord.p.Y][coord.p.X][coord.dir];
                if (b && b <= coord.val) continue;

                b = coord.val;
                // cout << coord.p.Y << " " << coord.p.X << " " << coord.val << " " << dir2str[coord.dir] << endl;
                auto coord2 = coord;
                coord2.dir = static_cast<Direction>((coord2.dir+1)%4);
                q.push(coord2);
                coord2.dir = static_cast<Direction>((coord2.dir+2)%4);
                q.push(coord2);
            }
        }
    }
};

vector<complex<int>> Crucible::d{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int main()
{
    Crucible crucible;
    crucible.init();

    cout << crucible.findPath() << endl;
}
