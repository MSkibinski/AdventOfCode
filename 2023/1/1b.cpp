#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, int> values{
        {"0", 0},
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9}
    };
    
    
    string line;
    int result = 0;
    int val_first, val_last;
    
    while(cin >> line) {
        int pos_first = 10000;
        int pos_last = 0;
        for (auto &[name, val] : values) {
            if(auto pos = line.find(name); pos != string::npos && pos < pos_first) {
                pos_first = pos;
                val_first = val;
            }
            if(auto pos = line.rfind(name); pos != string::npos && pos >= pos_last) {
                pos_last = pos;
                val_last = val;
            }
        }

        result += 10 * val_first + val_last;
    }

    cout << result << endl;
    return 0;
}
