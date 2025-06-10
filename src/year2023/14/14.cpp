#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main()
{
    //auto start = chrono::steady_clock::now();
    string line;
    vector<string> v;

    while (cin >> line)
        v.push_back(line);

    int len = v[0].size();
    vector<int> r(len);

    int result = 0;
    for (int row = 0, i=v.size()-1; i>=0; row++, i--) {
        for (int j=0; j<len; j++) {
            if (v[i][j]=='O')
                r[j]++;
            else if (v[i][j]=='#' && r[j]) {
                result += (2*row - (r[j]-1)) * r[j] / 2;
                r[j] = 0;
            }
        }
    }
    for (int j=0; j<len; j++)
        result += (2*v.size() - (r[j]-1)) * r[j] / 2;

    cout << result << endl;
    // auto end = chrono::steady_clock::now();
    // cout << chrono::duration <double, milli> (end-start).count() << " ms" << endl;
}
