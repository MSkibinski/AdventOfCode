#include <iostream>
#include <vector>
#include <cmath>

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
        if (nodeId <= maxA) {
            current.push_back(nodeId);
            cout << line.substr(0,3) << endl;
        }
        if (nodeId >= minZ) {
            cout << "   " << line.substr(0,3) << endl;
        }
    }
    
    long long result = 0;
    int dirId = 0;
    bool finish;
    do {
        finish=true;
        int finishers=0;
        for (auto &nodeId : current) {
            nodeId = directions[dirId]=='L' ? nodes[nodeId].first : nodes[nodeId].second;
            if (nodeId < minZ)
                finish = false;
            else
                finishers++;
        }
        

        dirId = (dirId+1) % directions.size();
        result++;
        if (finishers>3)
            cout << finishers << " " << result << endl;
    }while(!finish);

    cout << result << endl;
}