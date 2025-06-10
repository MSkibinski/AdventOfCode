
#include <iostream>
#include <vector>
#include <queue>
#include <climits> 

using namespace std;

template <typename T,typename U> 
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
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
            examinedPath.push({h, w+1});
        }
    }
    labirynth.push_back(string(line.size()+2, '#'));
    
    vector<vector<int>> cc(labirynth.size(), vector<int>(labirynth[0].size(), INT_MAX));
    auto p = examinedPath.front();
    cc[p.first][p.second] = 0;
    
    int result = 0;
    bool finish=false;
    while (!finish) {
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
                cc[nexPos.first][nexPos.second] = cost+1;
            }
        
            if (c=='E') {
                finish = true;
            }
        }
    }
    
    for (int h=0; h<labirynth.size(); h++) {
        for (int w=0; w<labirynth[h].size(); w++) {
            if (cc[h][w] < INT_MAX)
                labirynth[h][w] = 'O';
            if (labirynth[h][w] == '.')
                result++;
        }
    }
    
    cout << result << endl;
    
    return 0;
}