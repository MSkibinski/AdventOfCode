/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> dd = {{1,0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
vector<string> lines;

int sum=0;
int h_max;
int w_max;

void check(int hh, int ww) {
    string s = "MAS";
    for (auto d : dd) {
        int i, h, w;
        for (i=0, h=hh, w=ww; i<3; i++) {
            h += d.first;
            w += d.second;
            if (h<0 || h>=h_max || w<0 || w>=w_max) break;
            if (lines[h][w] != s[i]) break;
        }
        if (i==3)
            sum++;
    }
}

int main()
{
    
    string line;
    while (cin >> line) {
        lines.push_back(line);
    }
    
    h_max = lines.size();
    w_max = lines.front().size();
    for (int h=0; h<h_max; h++) {
        for (int w=0; w<w_max; w++) {
            if (lines[h][w] == 'X') {
                check(h, w);
            }
        }
    }
    
    std::cout << sum;

    return 0;
}