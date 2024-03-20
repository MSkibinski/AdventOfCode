#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>

using namespace std;

int findReflectionLine(const vector<bitset<17>> &v, const int difference) {
    for (int i=1; i<v.size(); i++) {
        int diff = 0;
        for (int j=i-1, k=i; j>=0 && k<v.size() && diff <= difference; j--, k++) {
            diff += (v[j] ^ v[k]).count();
        }
        if (diff == difference)
            return i;
    }
    return 0;
}

int main()
{
    auto start = chrono::steady_clock::now();
    string line;
    
    int result = 0;
    while (!cin.eof()) {
        vector<string> vs;
        vector<bitset<17>> v;
        for (getline(cin, line); !line.empty(); getline(cin, line)) {
            vs.push_back(line);
            v.push_back(bitset<17>(line, 0, line.size(), '.', '#'));
        }

        int res = findReflectionLine(v, 1) * 100;
        if (!res) {
            v.clear();
            for (int i=0; i<vs[0].size(); i++) {
                string s;
                for (int j=0; j<vs.size(); j++)
                    s += vs[j][i];
                
                v.push_back(bitset<17>(s, 0, s.size(), '.', '#'));
            }
            res = findReflectionLine(v, 1);
        }

        result += res;
    }

    cout << result << endl;
    auto end = chrono::steady_clock::now();
    cout << chrono::duration <double, milli> (end-start).count() << " ms" << endl;
}
