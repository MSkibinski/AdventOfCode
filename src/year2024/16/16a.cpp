
#include <iostream>
#include <vector>
#include <set>
#include <climits> 

using namespace std;

template <typename T,typename U> 
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}

struct PathInfo {
    int cost;
    int h, w;
    int dir;
    
    bool operator< (const PathInfo &p) const {
        return cost != p.cost ? cost < p.cost :
            h != p.h ? h < p.h :
            w != p.w ? w < p.w :
            dir < p.dir;
    }
};

set<PathInfo> examinedPath;
vector<string> labirynth;

vector<pair<int, int>> dd({{-1, 0}, {0, 1}, {1, 0}, {0, -1}}); // 0 - ^, 1 - >, 2 - v, 3 - <

int main()
{
    string line;
    for (int h = 0; getline(cin, line); h++) {
        labirynth.push_back(line);
        if (int w = line.find('S'); w != string::npos) {
            //startingPos = {h, w};
            examinedPath.insert({1000, h, w, 0});
            examinedPath.insert({0, h, w, 1});
            examinedPath.insert({1000, h, w, 2});
            examinedPath.insert({2000, h, w, 3});
        }
    }
    
    vector<vector<vector<int>>> cc(labirynth.size(), vector<vector<int>>(labirynth[0].size(), vector<int>(4, INT_MAX)));
    
    int result = 0;
    int nodesCalculated = 0;
    while (true) {
        auto p = *examinedPath.begin();
        examinedPath.erase(examinedPath.begin());
        pair<int, int> pos{p.h, p.w};
        pos = pos + dd[p.dir];
        char &c = labirynth[pos.first][pos.second];
        int cost = p.cost+1;
        if (c=='#') {
            continue;
        }
        if (c=='E') {
            result = cost;
            break;
        }
        else {
            if (cost < cc[pos.first][pos.second][p.dir]) {
                examinedPath.insert({cost, pos.first, pos.second, p.dir});
                cc[pos.first][pos.second][p.dir] = cost;
                int dir2 = (p.dir+1)%4;
                int dir3 = (p.dir+3)%4;
                if (cost+1000 < cc[pos.first][pos.second][dir2]) {
                    examinedPath.insert({cost+1000, pos.first, pos.second, dir2});
                    cc[pos.first][pos.second][dir2] = cost+1000;
                }
                if (cost+1000 < cc[pos.first][pos.second][dir3]) {
                    examinedPath.insert({cost+1000, pos.first, pos.second, dir3});
                    cc[pos.first][pos.second][dir3] = cost+1000;
                }
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}