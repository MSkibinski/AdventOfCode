#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

struct Sensor {
    int x, y, r;
};

int main()
{
    string line;
    vector<Sensor> s;
    while (getline(cin, line)) {
        line.erase(0, string("Sensor at x=").size());
        size_t p;
        int x = stoi(line, &p);
        line.erase(0, p+string(", y=").size());
        int y = stoi(line, &p);
        line.erase(0, p+string(": closest beacon is at x=").size());
        int bx = stoi(line, &p);
        line.erase(0, p+string(", y=").size());
        int by = stoi(line, &p);

        int r = abs(x-bx) + abs(y-by);
        s.push_back({x, y, r});
    }
    for (int y=0; y<4000000; y++) {
        vector<pair<int, int>> v;
        for (auto &sensor : s) {
            int dx = sensor.r - abs(sensor.y-y);
            if (dx >= 0)
               v.push_back({sensor.x-dx, sensor.x+dx});
        }
        sort(v.begin(), v.end());
        int prev = -1;
        for (auto [x1, x2] : v) {
            if (x2<=prev) continue;
            if (x1>prev) {
                cout << prev << "-" << x1 << ", " << y << endl;
                cout << 4000000ll*(x1-1) + 2638237 << endl;
            }
            prev = x2;
            if (prev > 4000000)
                break;
        }
    }

    // 5073497
    // 5073491
}
