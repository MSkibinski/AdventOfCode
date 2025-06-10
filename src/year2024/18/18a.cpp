
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

template <typename T,typename U> 
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}     

vector<pair<int, int>> dd({{1, 0}, {-1, 0}, {0, 1}, {0, -1}});

int main()
{
    int h, w;
    char c;
    
    bool test = false;
    
    int size;
    int inputSize;
    if (test) {
        size = 7;
        inputSize = 12;
    }
    else {
        size = 71;
        inputSize = 1024;
    }
    
    vector<string> memory(size, string(size, '.'));
    vector<vector<int>> steps(size, vector<int>(size, INT_MAX));
    
    for (int i=0; i<inputSize; i++) {
        cin >> w >> c >> h;
        memory[h][w] = '#';
    }
    
    steps[0][0] = 0;
    queue<pair<int, int>> currPos;
    currPos.push({0, 0});
    pair<int, int> fin{size-1, size-1};
    
    while (true) {
        auto pos = currPos.front(); currPos.pop();
        for (auto d : dd) {
            auto nextPos = pos + d;
            if (nextPos.first < 0 || nextPos.first >= size || nextPos.second < 0 || nextPos.second >= size) continue;
                
            int step = steps[pos.first][pos.second] + 1;
            if (nextPos == fin) {
                cout << step;
                return 0;
            }
            
            if (memory[nextPos.first][nextPos.second]=='#') continue;
            auto &s = steps[nextPos.first][nextPos.second];
            if (step < s) {
                s = step;
                currPos.push(nextPos);
            }
        }
    }
    
    return 0;
}