/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Node {
    vector<int> neighbours;
};

vector<Node> nodes(26*26);

int strToId(string s) {
    return (s[0]-'a') * 26 + (s[1]-'a');
}

string idToStr(int id) {
    string strId="aa";
    strId[0] = id/26 + 'a';
    strId[1] = id%26 + 'a';
    return strId;
}

vector<int> result;

void getBiggestCluster(int currentId, vector<int> &cluster) {
    bool possible = true;
    //cout << "currentId: " << currentId << endl;
    for (int id : cluster) {
        if (find(nodes[id].neighbours.begin(), nodes[id].neighbours.end(), currentId) == nodes[id].neighbours.end()) {
            possible = false;
            break;
        }
    }
    if (!possible) return;
    
    cluster.push_back(currentId);
    if (cluster.size() > result.size()) result = cluster;
    
    auto &currentNeighbours = nodes[currentId].neighbours;
    int id = 0;
    while (id<currentNeighbours.size() && currentNeighbours[id] < currentId) id++;
    for (; id < currentNeighbours.size(); id++) {
        getBiggestCluster(currentNeighbours[id], cluster);
    }
    cluster.pop_back();
}

int main()
{
    string line;
    while (cin >> line) {
        string node1 = line.substr(0, 2);
        string node2 = line.substr(3, 2);
        int id1 = strToId(node1);
        int id2 = strToId(node2);
        nodes[id1].neighbours.push_back(id2);
        nodes[id2].neighbours.push_back(id1);
    }
    
    for (auto &node : nodes) {
        sort(node.neighbours.begin(), node.neighbours.end());
    }
    
    for (int i=0; i<nodes.size(); i++) {
        vector<int> cluster;
        getBiggestCluster(i, cluster);
    }
    
    string sep = "";
    for (int id : result) {
        cout << sep << idToStr(id);
        sep = ",";
    }

    return 0;
}