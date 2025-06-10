
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <numeric>

using namespace std;

int main()
{
    string line;
    vector<string> a;
    while (cin >> line) {
        a.push_back(line);
    }
    int size = a[0].size();
    
    std::string area = std::accumulate(a.begin(), a.end(), std::string(""));
    
    map<int, set<int>> reachableNines;
    for (int i=0; i<area.size(); i++)
        if (area[i] == '9')
            reachableNines[i].insert(i);
    
    
    for(int i = 8; i>=0; i--) {
        map<int, set<int>> reachableNinesInLowerLewel;
        for (auto &[position, reachable9] : reachableNines) {
            vector<int> neighboursPosition;
            if (int neighbour = position - size; neighbour >= 0) neighboursPosition.push_back(neighbour);
            if (int neighbour = position + size; neighbour < area.size()) neighboursPosition.push_back(neighbour);
            if (int neighbour = position - 1; position%size != 0) neighboursPosition.push_back(neighbour);
            if (int neighbour = position + 1; neighbour%size != 0) neighboursPosition.push_back(neighbour);
            
            for (auto neighbourPosition : neighboursPosition) {
                if (area[neighbourPosition]-'0' == i) {
                    reachableNinesInLowerLewel[neighbourPosition].insert(reachable9.begin(), reachable9.end());
                }
            }
        }
        reachableNines = reachableNinesInLowerLewel;
    }
    
    int sum = 0;
    for (auto &[position, reachable9] : reachableNines) {
        sum += reachable9.size();
    }
    
    std::cout << sum;

    return 0;
}