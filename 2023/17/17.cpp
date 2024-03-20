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
    vector<vector<array<int, 12>>> best;
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

        best = vector<vector<array<int, 12>>>(height, vector<array<int, 12>>(width, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    int findPath() {
        struct Coord {
            int val;
            complex<int> p;
            Direction dir;
            int len;

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
                else if (len != c2.len){
                    return len < c2.len;
                }
                return dir < c2.dir;
            }
        };

        priority_queue<Coord> q;
        q.push({0, {0, 0}, Direction::right, 0});
        q.push({0, {0, 0}, Direction::down, 0});

        while (true) {
            auto coord = q.top(); q.pop();
            coord.p += d[coord.dir];
            
            if (coord.p.X < 0 || coord.p.X == width || coord.p.Y < 0 || coord.p.Y==height)
                continue;
            coord.len++;
            coord.val += m[coord.p.Y][coord.p.X];
            if (coord.p.X == width-1 && coord.p.Y == height-1) return coord.val;

            auto &b = best[coord.p.Y][coord.p.X][coord.dir*3+coord.len-1];
            if (b != 0) continue;
            
            b = coord.val;
            //cout << coord.p.Y << " " << coord.p.X << " " << coord.val << " " << dir2str[coord.dir] << endl;
            if (coord.len<3)
                q.push(coord);
            coord.len = 0;
            coord.dir = static_cast<Direction>((coord.dir+1)%4);
            q.push(coord);
            coord.dir = static_cast<Direction>((coord.dir+2)%4);
            q.push(coord);
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
