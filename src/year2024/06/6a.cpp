

#include <iostream>
#include <vector>
#include <complex>

using namespace std;

vector<string> m;

int h, w;

vector<complex<int>> dd {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

complex<int> guard_pos;
int directionId = 0;

char& get_m(complex<int> pos) {
    return m[pos.real()][pos.imag()];
}

int main()
{
    string line;
    for (int i=0; cin >> line; i++) {
        m.push_back(line);
        if (auto pos = line.find('^'); pos != string::npos) {
            guard_pos = {i, pos};
        }
    }

    int sum = 1;
    int h_max = m.size();
    int w_max = m[0].size();
    get_m(guard_pos) = 'X';
    
    while (true) {
        complex<int> next_pos = guard_pos + dd[directionId];
         if(next_pos.real() < 0 || next_pos.real() >= h_max ||
            next_pos.imag() < 0 || next_pos.imag() >= w_max) break;
        
        if (get_m(next_pos) == '#') {
            directionId = (directionId+1) % 4;
        }
        else {
            guard_pos = next_pos;
            if (auto &field = get_m(guard_pos); field != 'X') {
                field = 'X';
                sum++;
            }
        }
    }
    
    cout << sum;

    return 0;
}