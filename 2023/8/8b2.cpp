#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

const int ZZZ = 17575;

vector<pair<int, int>> nodes(ZZZ+1);

int strToId(const string &s) {
    int id = (s[2]-'A')*pow(26,2) + (s[1]-'A')*pow(26,1) + (s[0]-'A');
    // cout << s << " " << id << endl;
    return id;
}

const int minZ = strToId("AAZ");
const int maxA = strToId("ZZA");

int main() {
    string directions, line;
    getline(cin, directions);

    getline(cin, line);

    vector<int> current;
    for (getline(cin, line); line.size(); getline(cin, line)) {
        int nodeId = strToId(line.substr(0,3));
        int left = strToId(line.substr(7,3));
        int right = strToId(line.substr(12,3));
        nodes[nodeId] = {left, right};
        if (nodeId <= maxA)
            current.push_back(nodeId);
    }

    vector<long long> results;
    for (auto nodeId : current) {
        int result = 0;
        for (int dirId=0; nodeId < minZ; dirId = (dirId+1) % directions.size()) {
            nodeId = directions[dirId]=='L' ? nodes[nodeId].first : nodes[nodeId].second;
            result++;
        }
        results.push_back(result);
    }
    
    long long result = 1;

    for (auto r : results) {
        result = lcm(result, r);
    }

    cout << result << endl;
}