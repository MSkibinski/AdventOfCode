#include <iostream>
#include <vector>
#include <complex>
#include <map>

#define X real()
#define Y imag()

using namespace std;

vector<string> m;
vector<complex<int>> moveDir{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct Node {
    int x, y;

    vector<pair<Node*, int>> n;
};

class Graph {
    vector<Node> nodes;
    map<pair<int, int>, int> coordinatesToId;
    vector<vector<bool>> used;

    int findLongestPath(Node* currNode, int depth) {
        if (currNode == &nodes.back()) {
            return 0;
        }
        
        used[currNode->y][currNode->x] = true;
        int longest = -1;
        for (auto &[node, d] : currNode->n) {
            if (used[node->y][node->x]) continue;
            auto dist = findLongestPath(node, depth+1);
            if (dist >= 0)
                longest = max(longest, dist+d);
        }
        used[currNode->y][currNode->x] = false;
        return longest;
    }

public:
    Graph() {
        used = vector<vector<bool>>(m.size(), vector<bool>(m[0].size(), false));
    }

    void addNode(int x, int y) {
        coordinatesToId[{x, y}] = nodes.size();
        nodes.push_back({x, y});
    }

    void calculateNeighbourDistance() {
        for (auto &node : nodes) {
            complex<int> pos{node.x, node.y};
            for (int i=0; i<4; i++) {
                int direction = i;
                auto p = pos + moveDir[direction];
                if (m[p.Y][p.X] == '#') continue;
                
                int dist = 1;
                while (m[p.Y][p.X] != 'N') {
                    for (int j=0; j<4; j++) {
                        if ((direction+2)%4 == j) continue;
                        auto p2 = p + moveDir[j];
                        if (m[p2.Y][p2.X] == '#') continue;
                        p = p2;
                        direction = j;
                        dist++;
                        break;
                    }
                }
                int id = coordinatesToId[{p.X, p.Y}];
                node.n.push_back({&nodes[id], dist});
            }
        }
    }

    int longestPath() {
        return findLongestPath(&nodes[0], 0);
    }
};

int main() {
    string line;
    while(cin >> line)
        m.push_back(line);

    int count = 0;
    for (int i=0; i<m.size(); i++) {
        for (int j=0; j<m[0].size(); j++) {
            if (m[i][j] == '#') continue;
            int n = 0;
            complex<int> pos{j, i};
            for (auto mo : moveDir) {
                auto p = pos + mo;
                if (m[p.Y][p.X] != '#')
                    n++;
            }
            if (n != 2) {
                m[i][j] = 'N';
                count++;
            }
        }
    }
    cout << count << endl;

    Graph g;
    for (int i=0; i<m.size(); i++)
        for (int j=0; j<m[0].size(); j++)
            if (m[i][j] == 'N')
                g.addNode(j, i);

    g.calculateNeighbourDistance();

    cout << g.longestPath() << endl;
}
