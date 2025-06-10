
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> dd = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
vector<string> lines;

int sum=0;

void check(int h, int w) {
    int M = 0;
    int S = 0;
    for (auto d : dd) {
        char c = lines[h+d.first][w+d.second];
        if (c == 'M') M++;
        if (c == 'S') S++;
    }
    if (M==2 && S==2) {
        if (lines[h+dd[0].first][w+dd[0].second] != lines[h+dd[2].first][w+dd[2].second])
            sum++;
    }
}

int main()
{
    
    string line;
    while (cin >> line) {
        lines.push_back(line);
    }
    
    int h_max = lines.size();
    int w_max = lines.front().size();
    for (int h=1; h<h_max-1; h++) {
        for (int w=1; w<w_max-1; w++) {
            if (lines[h][w] == 'A') {
                check(h, w);
            }
        }
    }
    
    std::cout << sum;

    return 0;
}