#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<pair<int, int>> g;

    string line;
    for (int h=0, hexpand=0; cin >> line; h++, hexpand++) {
        bool empty = true;
        for (int w=0; w<line.size(); w++) {
            if (line[w]=='#') {
                g.push_back({w, hexpand});
                empty = false;
            }
        }
        if (empty)
            hexpand += (1000000-1);
    }
    sort(g.begin(), g.end());

    int expand = 0;
    int prev = -1;
    for (auto &[w, h] : g) {
        if (w != prev) {
            if (w-prev>1)
                expand += (w-prev-1)*(1000000-1);
            prev = w;
        }
        w += expand;
        cout << w << " " << h << endl;
    }

    long long result = 0;
    for (int i=0; i<g.size()-1; i++) {
        for (int j=i+1; j<g.size(); j++) {
            result += abs(g[i].first-g[j].first) + abs(g[i].second-g[j].second);
        }
    }
    cout << result << endl;
}
