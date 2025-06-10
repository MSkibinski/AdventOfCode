#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Point {
    int h, w;
    
    Point operator+(const Point &p) {
        Point r;
        r.h = h + p.h;
        r.w = w + p.w;
        return r;
    }
    
    Point operator-(const Point &p) {
        Point r;
        r.h = h - p.h;
        r.w = w - p.w;
        return r;
    }
    
    bool operator<(const Point &p) const {
        return h != p.h ? h<p.h : w<p.w;
    }
};

int main()
{
    vector<vector<Point>> antenas(256);
    set<Point> antinodes;
    
    int max_h = 0;
    for(string line; cin >> line; max_h++) {
        for (int w=0; w<line.size(); w++) {
            if (line[w] != '.') {
                Point p(max_h, w);
                for (auto antena : antenas[line[w]]) {
                    Point diff = p - antena;
                    antinodes.insert(p+diff);
                    antinodes.insert(antena-diff);
                }
                antenas[line[w]].push_back(p);
            }
        }
    }
    
    int sum = 0;
    for (auto antinode : antinodes) {
        if (antinode.h >= 0 && antinode.h < max_h &&
            antinode.w >= 0 && antinode.w < max_h)
            sum++;
    }
    
    std::cout << sum;

    return 0;
}