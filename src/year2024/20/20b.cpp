
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <numeric>

using namespace std;

template <typename T,typename U> 
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}

template <typename T,typename U> 
std::pair<T,U> operator*(const std::pair<T,U> & l,const int & r) {   
    return {l.first*r,l.second*r};                                    
}

queue<pair<int, int>> examinedPath;
vector<string> labirynth;

vector<pair<int, int>> dd({{-1, 0}, {0, 1}, {1, 0}, {0, -1}}); // 0 - ^, 1 - >, 2 - v, 3 - <

int main()
{
    string line;
    for (int h = 0; getline(cin, line); h++) {
        if (h==0) {
            labirynth.push_back(string(line.size()+2, '#'));
        }
        labirynth.push_back("#"+line+"#");
        if (int w = line.find('S'); w != string::npos) {
            examinedPath.push({h+1, w+1});
        }
    }
    labirynth.push_back(string(line.size()+2, '#'));
    
    vector<vector<int>> cc(labirynth.size(), vector<int>(labirynth[0].size(), INT_MAX));
    auto p = examinedPath.front();
    cc[p.first][p.second] = 0;
    
    
    while (!examinedPath.empty()) {
        auto pos = examinedPath.front(); examinedPath.pop();
        //pair<int, int> pos{p.h, p.w};
        for (auto d: dd) {
            auto nexPos = pos + d;
            char &c = labirynth[nexPos.first][nexPos.second];
            if (c=='#') continue;
        
            
            int cost = cc[pos.first][pos.second] + 1;
            int &cost2 = cc[nexPos.first][nexPos.second];
            if (cost < cost2) {
                examinedPath.push({nexPos.first, nexPos.second});
                cc[nexPos.first][nexPos.second] = cost;
            }
        }
    }
    
    int result = 0;
    int size = labirynth.size();
    for (int h=0; h<labirynth.size(); h++) {
        for (int w=0; w<labirynth[h].size(); w++) {
            if (labirynth[h][w] == '#') continue;
            int cost = cc[h][w];
            pair<int, int> pos = {h, w};
            for (int hx = -20; hx <=20; hx++) {
                int maxWx = 20-abs(hx);
                for (int wx = - maxWx; wx <= maxWx; wx++) {
                    int h2 = h+hx;
                    int w2 = w+wx;
                    if (w2<0 || w2>=size || h2<0 || h2>=size) continue;
                    
                    int dist = abs(hx) + abs(wx);
                    if (labirynth[h2][w2] != '#') {
                        int cost2 = cc[h2][w2];
                        if (cost2 - cost - dist >= 100) {
                            //cout << "From[" << h << "," << w << "] to [" << pos2.first << "," << pos2.second << "], saved: " << cost2 -cost - 2 << endl;
                            result++;
                        }
                    }
                }
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}