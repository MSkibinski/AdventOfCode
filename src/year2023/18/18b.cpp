#include <iostream>
#include <vector>

using namespace std;

vector<string> v;

struct Vertex {
    long long x, y;
};

class Polygon {
    vector<Vertex> v;

public:
    void read() {
        char c;
        int len;
        string s;
        long long x=0, y=0;
        v.push_back({x, y});

        int pMove = 3;
        int ppMove = 3;
        while(cin >> c >> len >> s) {
            int dir = s[7]-'0';
            int val = stoi(s.substr(2, 5), nullptr, 16);
            if (dir != ppMove && v.size()>1) {
                if (dir == (pMove+1)%4) {
                    switch (pMove) {
                        case 0: x++; break; 
                        case 1: y++; break;
                        case 2: x--; break;
                        case 3: y--; break;
                    }
                }
                else {
                    switch (pMove) {
                        case 0: x--; break; 
                        case 1: y--; break;
                        case 2: x++; break;
                        case 3: y++; break;
                    }
                }
                v.back() = {x, y};
            }

            switch (dir) {
                case 0: x += val; break; 
                case 1: y += val; break;
                case 2: x -= val; break;
                case 3: y -= val; break;
            }
            v.push_back({x, y});

            ppMove = pMove;
            pMove = dir;
        }
        v.back() = {0, 0};
    }

    long long getVolume() {
        long long volume = 0;
        for (int i=1; i<v.size(); i++) {
            auto &a = v[i-1];
            auto &b = v[i];
            volume += (a.x + b.x) * (a.y - b.y);
        }

        return volume/2;
    }
};

int main()
{
    Polygon p;
    p.read();

    cout << abs(p.getVolume()) << endl;
}
