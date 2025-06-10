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

set<int> result;

int strToId(string s) {
    return (s[0]-'a') * 26 + (s[1]-'a');
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
    
    for (int i=0; i<nodes.size(); i++) {
        if (i/26 == 't'-'a') {
            auto &n1 = nodes[i].neighbours;
            if (n1.empty()) continue;
            
            for (auto n2Id : n1) {
                auto &n2 = nodes[n2Id].neighbours;
                
                for (auto n3Id : n2) {
                    if (std::find(n1.begin(), n1.end(), n3Id) != n1.end()) {
                        vector<int> interconected = {i, n2Id, n3Id};
                        sort(interconected.begin(), interconected.end());
                        result.insert(interconected[0] * 1000000 + interconected[1] + 1000 + interconected[2]);
                    }
                }
            }
        }
    }
    
    std::cout << result.size();

    return 0;
}