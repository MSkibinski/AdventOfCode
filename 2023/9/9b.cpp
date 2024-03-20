#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    string line;

    int result = 0;
    for (getline(cin, line); line.size(); getline(cin, line)) {
        vector<int> v;
        istringstream iss(line);
        int x;
        while (iss >> x)
            v.push_back(x);
        
        vector<vector<int>> t(v.size(), vector<int>(v.size()));
        t[0] = v;
        bool zeroes = false;
        int i=1;
        while(!zeroes) {
            zeroes = true;
            for (int j=i; j<t[i-1].size(); j++) {
                t[i][j] = t[i-1][j] - t[i-1][j-1];
                if (t[i][j])
                    zeroes = false;
            }
            i++;
        }

        int sum=0;
        for (int j=0; j<i; j++)
            sum = j%2 ? sum-t[j][j] : sum+t[j][j];
        
        result += sum;
    }

    cout << result << endl;
}