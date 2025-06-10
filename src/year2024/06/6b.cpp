

#include <iostream>
#include <vector>
#include <complex>
#include <set>

using namespace std;

vector<complex<int>> dd {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int h_max;
int w_max;

class Map {
    vector<string> m;
    
    complex<int> guard_pos, gp;
    int directionId = 0, dId = 0;
    
    
    
public:
    void read() {
        string line;
        for (int i=0; cin >> line; i++) {
            m.push_back(line);
            if (auto pos = line.find('^'); pos != string::npos) {
                gp = {i, int(pos)};
            }
        }
        
        h_max = m.size();
        w_max = m[0].size();
    }
    
    bool guardInside() {
        return guard_pos.real() >= 0 && guard_pos.real() < h_max &&
            guard_pos.imag() >= 0 && guard_pos.imag() < w_max;
    }
    
    bool loopPossible() {
        guard_pos = gp;
        directionId = dId;
        set<int> visitedWalls;
        
        while (true) {
            complex<int> next_pos = guard_pos + dd[directionId];
            
            if(next_pos.real() < 0 || next_pos.real() >= h_max ||
                next_pos.imag() < 0 || next_pos.imag() >= w_max) {
                return false;        
            }
            
            if (m[next_pos.real()][next_pos.imag()] == '#') {
                int w = next_pos.real() * 1000000 + next_pos.imag()*1000 + directionId;
                if (visitedWalls.contains(w))
                    return true;
                else
                    visitedWalls.insert(w);
                
                directionId = (directionId+1) % 4;
            }
            else {
                guard_pos = next_pos;
            }
        }
    }
    
    
    void position()
    {
        cout << guard_pos.real() << " " << guard_pos.imag() << endl;
    }
    
    char& getC(int h, int w) {
        return m[h][w];
    }
};


int main()
{
    Map m;
    m.read();
    
    int sum = 0;
    int i = 0;
    
    for (int h=0; h<h_max; h++) {
        for (int w=0; w<w_max; w++) {
            if (m.getC(h, w) != '.') continue;
            
            m.getC(h, w) = '#';
            sum += m.loopPossible() ? 1 : 0;
            m.getC(h, w) = '.';
        }
    }
    
    cout << sum;

    return 0;
}