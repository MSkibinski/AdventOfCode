#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string line;
    vector<string> v;

    int r=0;
    while (!cin.eof()) {
        v.clear();
        for (getline(cin, line); !line.empty(); getline(cin, line))
            v.push_back(line);
        
        int result = 0;
        for (int i=1; i<v.size() && !result; i++) {
            if (v[i] == v[i-1]) {
                result = i;
                for (int j=i-2, k=i+1; j>=0 && k<v.size() && result; j--, k++) {
                    if (v[j] != v[k])
                        result = 0;
                }
            }
        }
        result *=100;

        if (!result) {
            vector<string> v2;
            for (int i=0; i<v[0].size(); i++) {
                string s;
                for (int j=0; j<v.size(); j++)
                    s += v[j][i];
                
                v2.push_back(s);
            }
            v = v2;

            for (int i=1; i<v.size() && !result; i++) {
                if (v[i] == v[i-1]) {
                    result = i;
                    for (int j=i-2, k=i+1; j>=0 && k<v.size() && result; j--, k++) {
                        if (v[j] != v[k])
                            result = 0;
                    }
                }
            }
        }
        cout << result << endl;
        r += result;
    }

    cout << r << endl;
}
