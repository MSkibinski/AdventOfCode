#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> grid;

bool adjacentToSymbol(int y, int start, int end) {
    for (int x = start-1; x <= end+1; x++) {
        if (grid[y-1][x] != '.' && (grid[y-1][x]<'0' || grid[y-1][x]>'9'))
            return true;
        if (grid[y+1][x] != '.' && (grid[y+1][x]<'0' || grid[y+1][x]>'9'))
            return true;
    }
    if (grid[y][start-1] != '.' && (grid[y][start-1]<'0' || grid[y][start-1]>'9'))
            return true;
    if (grid[y][end+1] != '.' && (grid[y][end+1]<'0' || grid[y][end+1]>'9'))
            return true;
    return false;
}

int main() {
    string line;
    
    for (getline(cin, line); !cin.eof(); getline(cin, line)) {
        grid.push_back(line);
        // cout << line << endl;
    }

    int result = 0;
    for (int y=0; y<grid.size(); y++) {
        for (int x=0; x<grid[y].size(); x++) {
            if (grid[y][x]>='0' && grid[y][x]<='9') {
                int number = grid[y][x]-'0';
                int start=x; 
                while (x+1 < grid[y].size() && grid[y][x+1]>='0' && grid[y][x+1]<='9') {
                    x++;
                    number = number*10 + grid[y][x]-'0';
                }

                if(adjacentToSymbol(y, start, x)) {
                    result += number;
                }
            }
        }
    }
    
    cout << result << endl;
}