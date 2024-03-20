#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();
    string line;
    

    int r=0;
    size_t maxSize = 0;
    while (!cin.eof()) {
        vector<string> v;
        for (getline(cin, line); !line.empty(); getline(cin, line))
            v.push_back(line);

        vector<string> v2;
        for (int i=0; i<v[0].size(); i++) {
            string s;
            for (int j=0; j<v.size(); j++)
                s += v[j][i];
            
            v2.push_back(s);
        }
        maxSize = max(maxSize, v.size());
        maxSize = max(maxSize, v2.size());
        
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
            vector<string> v3;
            for (int i=0; i<v[0].size(); i++) {
                string s;
                for (int j=0; j<v.size(); j++)
                    s += v[j][i];
                
                v3.push_back(s);
            }

            for (int i=1; i<v3.size() && !result; i++) {
                if (v3[i] == v3[i-1]) {
                    result = i;
                    for (int j=i-2, k=i+1; j>=0 && k<v3.size() && result; j--, k++) {
                        if (v3[j] != v3[k])
                            result = 0;
                    }
                }
            }
        }
        int oldResult = result;
        result = 0;

        for (int i1=0; i1<v.size() && !result; i1++)
        for (int i2=0; i2<v[0].size() && !result; i2++) {
            if (v[i1][i2]=='.') {
                v[i1][i2]='#';
                v2[i2][i1]='#';
            }
            else {
                v[i1][i2]='.';
                v2[i2][i1]='.';
            }
            for (int i=1; i<v.size() && !result; i++) {
                if (v[i] == v[i-1]) {
                    result = 100*i;
                    if (result == oldResult)
                        result = 0;
                    for (int j=i-2, k=i+1; j>=0 && k<v.size() && result; j--, k++) {
                        if (v[j] != v[k])
                            result = 0;
                    }
                }
            }

            if (!result) {
                for (int i=1; i<v2.size() && !result; i++) {
                    if (v2[i] == v2[i-1]) {
                        result = i;
                        if (result == oldResult)
                            result = 0;
                        for (int j=i-2, k=i+1; j>=0 && k<v2.size() && result; j--, k++) {
                            if (v2[j] != v2[k])
                                result = 0;
                        }
                    }
                }
            }

            if (v[i1][i2]=='.') {
                v[i1][i2]='#';
                v2[i2][i1]='#';
            }
            else {
                v[i1][i2]='.';
                v2[i2][i1]='.';
            }
        }
        if (result==0) {
            cout << "ERROR" << endl;
            return 0;
        }
        
        r += result;
    }

    cout << r << endl;
    cout << maxSize << endl;

    auto end = chrono::steady_clock::now();
    cout << chrono::duration <double, milli> (end-start).count() << " ms" << endl;
}
