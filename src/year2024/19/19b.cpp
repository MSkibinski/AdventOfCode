
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    string line;
    getline(cin, line);
    
    istringstream is(line);
    string pattern;
    vector<string> patterns;
    while (is >> pattern) {
        if (pattern.back() == ',') pattern.pop_back();
        patterns.push_back(pattern);
    }
    
    getline(cin, line);
    long long result = 0;
    while (getline(cin, line)) {
        vector<long long> possible(line.size()+1, 0);
        possible[0] = 1;
        
        for (int i=0; i<possible.size()-1; i++) {
            if (!possible[i]) continue;
            
            for (auto p : patterns) {
                if (line.substr(i, p.size()) == p) {
                    possible[i+p.size()] += possible[i];
                }
            }
        }
        if (possible.back()) {
            result+= possible.back();
        }
    }
    
    cout << result << endl;

    return 0;
}