#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    
    string line;
    getline( cin, line );
    
    int sum = 0;
    while (getline( cin, line )) {
        vector<int> v;
        istringstream is( line );
        int n;
        while( is >> n ) {
            //cout << n << " ";
            v.push_back(n);
        }
        
        int kind = 0;
        bool isSafe = true;
        if (v[0] < v[1]) kind = 1;
        if (v[0] > v[1]) kind = -1;
        for (int i=1; i<v.size(); i++) {
            int diff = (v[i] - v[i-1]) * kind;
            if (diff <=0 || diff >3) {
                isSafe = false;
                break;
            }
        }
        
        //cout << isSafe << endl;
        
        if (isSafe)
            sum++;
    }
    
    std::cout << sum << endl;

    return 0;
}