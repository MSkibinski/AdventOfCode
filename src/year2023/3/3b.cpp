#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

vector<string> grid;
map<pair<int, int>, vector<int>> gear;

void addToGear(int value, int y, int start, int end) {
    for (int x = start-1; x <= end+1; x++) {
        if (grid[y-1][x] == '*')
            gear[{y-1, x}].push_back(value);
        if (grid[y+1][x] == '*')
            gear[{y+1, x}].push_back(value);
    }
    if (grid[y][start-1] == '*')
        gear[{y, start-1}].push_back(value);
    if (grid[y][end+1] == '*')
        gear[{y, end+1}].push_back(value);
}

int main() {
    string line;
    
    for (getline(cin, line); !cin.eof(); getline(cin, line))
        grid.push_back(line);

    for (int y=0; y<grid.size(); y++) {
        for (int x=0; x<grid[y].size(); x++) {
            if (grid[y][x]>='0' && grid[y][x]<='9') {
                int number = grid[y][x]-'0';
                int start=x; 
                while (x+1 < grid[y].size() && grid[y][x+1]>='0' && grid[y][x+1]<='9') {
                    x++;
                    number = number*10 + grid[y][x]-'0';
                }

                addToGear(number, y, start, x);
            }
        }
    }

    int result = 0;
    for (auto& [coor, values] : gear) {
        if (values.size() == 2)
            result += values[0]*values[1];
    }
    
    cout << result << endl;
}