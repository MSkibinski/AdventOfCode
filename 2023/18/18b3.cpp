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


};

int main()
{
    Polygon p;
    p.read();

}
