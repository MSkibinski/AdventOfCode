#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<string> v;

struct Vertex {
    long long x, y;
    int idNext;
    int idPrev;
};

class Polygon {
    vector<Vertex> v;

public:
    void read() {
        char c;
        int len;
        string s;
        long long x=0, y=0;
        int id = 0;
        v.push_back({x, y, id+1, id-1});
        while (cin >> c >> len >> s) {
            // (#556903)
            int dir = s[7]-'0';
            int val = stoi(s.substr(2, 5), nullptr, 16);
            switch (dir) {
                case 0: x += val; break; 
                case 1: y += val; break;
                case 2: x -= val; break;
                case 3: y -= val; break;
            }
            id++;
            v.push_back({x, y, id+1, id-1});
        }
        v[0].idPrev = v.size()-1;
        v.back().idNext = 0;

        int topVertexId = 0;
        for (int i=1; i<v.size(); i++) {
            if (v[i].y <= v[topVertexId].y)
                if (v[i].x < v[topVertexId].x)
                    topVertexId = i;
        }
        if (v[v[topVertexId].idNext].y > v[topVertexId].y) {
            // need to revert
            cout << "need to revert" << endl;
        }
    }

    long long getVolume() {
        auto compare = [&](int a, int b) { return v[a].y != v[b].y ? v[a].y < v[b].y : v[a].x < v[b].x; };
        priority_queue<int, vector<int>, decltype(compare)> vertexIds(compare);

        for (int i=0; i<v.size(); i++) {
            vertexIds.push(i);
        }

        // for (auto &p : vertexIds) {
        //     cout << p << " " << v[p].y << " " << v[p].x << endl;
        // }

        long long volume = 0;
        while (!vertexIds.empty()) {
            int id = vertexIds.top(); vertexIds.pop();
            int idNext = vertexIds.top(); vertexIds.pop();

            auto &c = v[id];
            auto &n = v[c.idNext];
            auto &p = v[c.idPrev];

            if (c.idPrev == idNext) {
                volume += p.x - c.x + 1;
                p.idNext = c.idNext;
                n.idPrev = c.idPrev;
                vertexIds.push(idNext);
                continue;
            }

            
            cout << id << " " << c.y << " " << c.x << endl;
            if (c.idNext == 0 && c.idPrev == 0) continue;
            auto &n = v[v[id].idNext];
            if (n.y != c.y) continue;

            auto &n2 = v[n.idNext];
            auto &p = v[v[id].idPrev];

            if (n.idNext == c.idPrev) {
                volume += n.x - c.x + 1;
                c.idNext = c.idPrev = 0;
                n.idNext = n.idPrev = 0;
                p.idNext = p.idPrev = 0;
            }
            else if (p.y <= n2.y) { // going down till p
                volume += (abs(c.x-n.x) + 1) * (p.y-c.y);

                if (p.x > c.x)
                    volume += p.x - c.x;
                n.y = p.y;
                n.idPrev = c.idPrev;
                p.idNext = c.idNext;
                c.idNext = c.idPrev = 0;
            }
            else if (n2.y < p.y) {
                volume += (abs(c.x-n.x) + 1) * (n2.y-c.y);
                if (n2.x < n.x)
                    volume += n.x - n2.x;
                c.y = n2.y;
                vertexIds.push(id);
                c.idNext = n.idNext;
                n2.idPrev = id;
                n.idNext = n.idPrev = 0;

            }
            // else {
            //     volume += (abs(c.x-n.x) + 1) * (p.y-c.y+1);
            // }
        }
        return volume;
    }
};

int main()
{
    Polygon p;
    p.read();

    cout << p.getVolume() << endl;
}
