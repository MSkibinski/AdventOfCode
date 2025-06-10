#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isSafe(vector<int> &v) {
    int kind = 0;
    if (v[0] < v[1]) kind = 1;
    if (v[0] > v[1]) kind = -1;
    for (int i=1; i<v.size(); i++) {
        int diff = (v[i] - v[i-1]) * kind;
        if (diff <=0 || diff >3)
            return false;
    }
    
    return true;
}

int main() {
    
    string line;
    
    int sum = 0;
    while (getline( cin, line )) {
        vector<int> v;
        istringstream is( line );
        int n;
        while( is >> n ) {
            v.push_back(n);
        }
        
        bool wasSafe = false;
        for (int i=0; i<v.size(); i++) {
            vector<int> tmp = v;
            tmp.erase(tmp.begin() + i);
            if (isSafe(tmp)) {
                wasSafe = true;
                sum++;
                break;
            }
        }
        
        if (wasSafe == false) {
            for (auto elem: v) {
                cout << elem << " ";
            }
            cout << endl;
            for (int i=1; i<v.size() ;i++) {
                int diff = v[i] - v[i-1];
                if (diff < -3 || diff == 0 || diff >3)
                    cout << diff << " ";
            }
            cout << endl;
        }
    }
    
    std::cout << sum << endl;

    return 0;
}