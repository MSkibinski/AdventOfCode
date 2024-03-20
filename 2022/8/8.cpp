#include <iostream>
#include <vector>

using namespace std;

vector<string> t;
vector<vector<bool>> v;
int visible = 0;
int maxH = 0;

void check(int i, int j) {
    if (t[i][j] > maxH) {
        if (!v[i][j]) {
            visible++;
            v[i][j] = true;
        }
        maxH = t[i][j];
    }
}

int main()
{
    
    string line;
    while (cin >> line)
        t.push_back(line);

    v = vector<vector<bool>>(t.size(), vector<bool>(t[0].size()));

    for (int i=0; i<t.size(); i++) {
        maxH = 0;
        for (int j=0; j<t[0].size(); j++)
            check(i, j);
        maxH = 0;    
        for (int j=t[0].size()-1; j>=0; j--)
            check(i, j);
    }
    for (int j=0; j<t[0].size(); j++) {
        maxH = 0;
        for (int i=0; i<t.size(); i++)
            check(i, j);
        maxH = 0;    
        for (int i=t.size()-1; i>=0; i--)
            check(i, j);
    }

    cout << visible << endl;
}
