#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

int main()
{
    string line;
    vector<pair<int, int>> r;
    set<int> becons;
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

        int dist = abs(x-bx) + abs(y-by);
        int dx = dist - abs(y-2000000);
        if (dx >= 0)
            r.push_back({x-dx, x+dx});
        if (by==2000000)
            becons.insert(bx);
    }
    sort(r.begin(), r.end());
    int prev = numeric_limits<int>::min();
    int sum = 0;
    for (auto [x, y] : r) {
        if (prev < x) {
            sum += y-x+1;
            prev = y;
        }
        else if (prev<y) {
            sum += y-prev;
            prev = y;
        }

    }
    cout << sum-becons.size() << endl;
    // 5073497
    // 5073491
}
