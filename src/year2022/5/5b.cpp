#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

int main()
{
    auto start = chrono::steady_clock::now();
    vector<string> st(9);
    string line;
    for (getline(cin, line); !isdigit(line[1]); getline(cin, line)) {
        for (int i=1, j=0; i<line.size(); i+=4, j++)
            if (line[i]!=' ')
                st[j].push_back(line[i]);
    }

    getline(cin, line);

    int nr, from, to;
    string s;
    while (cin >> s >> nr >> s >> from >> s >> to) {
       from--;
       to--;

       auto m = st[from].substr(0, nr);
       st[from].erase(0, nr);
       st[to].insert(0,m);
    }

    for (auto &line : st)
        if (!line.empty())
            cout << line[0];
    cout << endl;

    auto end = chrono::steady_clock::now();
    cout << chrono::duration <double, milli> (end-start).count() << " ms" << endl;
}
