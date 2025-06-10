
#include <iostream>
#include <vector>

using namespace std;

vector<string> garden;

vector<pair<int, int>> dd{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

pair<int, int> count(int h, int w) {
    vector<pair<int, int>> region{{h, w}};
    char plant = garden[h][w];
    
    int perimeter = 0;
    char alreadyCount = '#';
    garden[h][w] = alreadyCount;
    for (int i=0; i<region.size(); i++) {
        for (auto [dh, dw] : dd) {
            int h = region[i].first + dh;
            int w = region[i].second + dw;
            
            if (garden[h][w] == plant) {
                region.push_back({h, w});
                garden[h][w] = alreadyCount;
            }
            else if (garden[h][w] != alreadyCount) {
                perimeter++;
            }
        }
        garden[region[i].first][region[i].second] = alreadyCount;
    }
    int area = region.size();
    
    for (auto [h, w] : region) {
        garden[h][w] = ' ';
    }
    return {area, perimeter};
}

int main()
{
    string line;
    
    int size = 0;
    while (cin >> line) {
        if (garden.empty()) {
            garden.push_back(string(line.size()+2, ' '));
            size = line.size();
        }
        garden.push_back(" " + line + " ");
    }
    garden.push_back(string(line.size()+2, ' '));
    
    int sum=0;
    for (int h = 1; h <= size; h++) {
        for (int w = 1; w <= size; w++) {
            if (char c = garden[h][w]; c!=' ') {
                // vector<pair<int, int>> region({h, w});
                // garden[h][w] = '#';
                auto [area, perimeter] = count(h, w);
                sum += area*perimeter;
                
                // cout << c << " " << area << " " << perimeter << endl;
            }
        }
    }
    
    cout << sum;

    return 0;
}