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
    
    bool inside(int max_v) {
        return h >= 0 && h < max_v && w >= 0 && w < max_v;
    }
};


int main()
{
    vector<vector<Point>> antenas(256);
    set<Point> antinodes;
    
    string line;
    int max_h = 0;
    for(int h=0; cin >> line; h++) {
        max_h = line.size();
        for (int w=0; w<line.size(); w++) {
            if (line[w] != '.') {
                Point p(h, w);
                auto &ant = antenas[line[w]];
                if (ant.size() == 1) {
                    antinodes.insert(ant[0]);
                }
                if (ant.size() >= 1) {
                    antinodes.insert(p);
                }
                for (auto antena : ant) {
                    Point diff = p - antena;
                    for (Point p2 = p+diff; p2.inside(max_h); p2 = p2+diff) {
                        antinodes.insert(p2);
                    }
                    for (Point p2 = antena-diff; p2.inside(max_h); p2 = p2-diff) {
                        antinodes.insert(p2);
                    }
                }
                ant.push_back(p);
            }
        }
    }
    
    std::cout << antinodes.size();

    return 0;
}