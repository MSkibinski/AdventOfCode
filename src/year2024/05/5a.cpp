#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> rules(100);


int main()
{
    string line;
    for (getline(cin, line); !line.empty(); getline(cin, line)) {
        istringstream is(line);
        
        int a, b;
        char c;
        is >> a >> c >> b;
        rules[a].push_back(b);
    }
    
    int sum = 0;
    while(getline(cin, line)) {
        line.push_back(',');
        istringstream is(line);
        
        vector<int> printed;
        
        int a;
        char c;
        bool correct = true;
        while (is >> a >> c) {
            const auto result = std::find_first_of(printed.begin(), printed.end(),
                                               rules[a].begin(), rules[a].end());
            if (result != printed.end()) {
                //cout << "breaking rule for " << a << endl;
                correct = false;
                break;
            }
            printed.push_back(a);
        }
        if (correct) {
            sum += printed[printed.size()/2];
        }
    }
    cout << sum << endl;
    return 0;
}