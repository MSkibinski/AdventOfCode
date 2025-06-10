#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Info {
    vector<int> h = vector<int>(5, 0);  
};

vector<Info> keys;
vector<Info> locks;

int main()
{
    string line;
    do {
        getline(cin, line);
        auto &group = line[0] == '#' ? locks : keys;
    
        Info info;
        for (int i=0; i<6; i++) {
            getline(cin, line);
            for (int j=0; j<line.size(); j++) {
                if (line[j] == '#')
                    info.h[j]++;
            }
        }
        group.push_back(info);
        
    } while (getline(cin, line));
    
    int result = 0;
    for (auto key : keys) {
        for (auto lock : locks) {
            bool possible = true;
            for (int i=0; i<5; i++) {
                if (key.h[i] + lock.h[i] > 6) {
                    possible = false;
                    break;
                }
            }
            result += possible ? 1 : 0;
        }
    }
    
    cout << keys.size() << " " << locks.size() << endl;
    cout << result << endl;

    return 0;
}