#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> rules(100);
vector<vector<int>> whoNeedsToBeBefore(100);


int main()
{
    string line;
    for (getline(cin, line); !line.empty(); getline(cin, line)) {
        istringstream is(line);
        
        int a, b;
        char c;
        is >> a >> c >> b;
        rules[a].push_back(b);
        whoNeedsToBeBefore[b].push_back(a);
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
                correct = false;
            }
            printed.push_back(a);
        }
        
        
        if (!correct) {
            vector<int> result;
            
            while (!printed.empty()) {
                for(int i = 0; i<printed.size(); i++) { // czy da rade zamienic na petle for-range
                    int value = printed[i];
                    const auto f_result = std::find_first_of(printed.begin(), printed.end(),
                                               whoNeedsToBeBefore[value].begin(), whoNeedsToBeBefore[value].end());
                    if (f_result == printed.end()) {
                        result.push_back(value);
                        printed.erase(printed.begin()+i);
                        break;
                    }   
                }
            }
            sum += result[result.size()/2];
        }
    }
    cout << sum << endl;
    return 0;
}