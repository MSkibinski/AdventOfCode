#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int ZZZ = 17575;

vector<pair<int, int>> nodes(ZZZ+1);

int strToId(const string &s) {
    int id = (s[0]-'A')*pow(26,2) + (s[1]-'A')*pow(26,1) + (s[2]-'A');
    // cout << s << " " << id << endl;
    return id;
}

int main() {
    string directions, line;
    getline(cin, directions);

    getline(cin, line);
    for (getline(cin, line); line.size(); getline(cin, line)) {
        int nodeId = strToId(line.substr(0,3));
        int left = strToId(line.substr(7,3));
        int right = strToId(line.substr(12,3));
        nodes[nodeId] = {left, right};
    }
    
    int result = 0;
    for (int id = strToId("AAA"), dirId=0; id != ZZZ; dirId = (dirId+1) % directions.size()) {
        id = directions[dirId]=='L' ? nodes[id].first : nodes[id].second;
        result++;
    }

    cout << result << endl;
}