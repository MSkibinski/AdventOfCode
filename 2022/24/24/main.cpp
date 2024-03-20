#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int height = 39;
const int width = 102;

// const int height = 8;
// const int width = 8;

vector<string> grid(height);
vector<string> nextGrid;
vector<string> emptyGrid(height, string(width, '.'));

struct Blizzard {
    char c;
    int w;
    int h;

    void move() {
        switch (c){
            case '>': w++; if (w==width-1) w=1; break;
            case '<': w--; if (w==0) w=width-2; break;
            case '^': h--; if (h==1) h=height-3; break;
            case 'v': h++; if (h==height-2) h=2; break;
        }
    }
};

vector<Blizzard> blizzards;

int main()
{
    grid[0] = string(width, '#');
    grid[height-1] = string(width, '#');
    for (int i=1; i<height-1; i++) {
        cin >> grid[i];
        for (int j=1; j<width; j++)
            if (grid[i][j]!='.' && grid[i][j]!='#')
                blizzards.push_back({grid[i][j], j, i});
    }
    emptyGrid[0] = grid[0];
    emptyGrid[1] = grid[1];
    emptyGrid[height-2] = grid[height-2];
    emptyGrid[height-1] = grid[height-1];
    for (int i=2; i<height-2; i++) {
        emptyGrid[i][0] = emptyGrid[i][width-1] = '#';
    }
    grid[1][1] = 'E';

    int turn = 0;
    while(true) {
        turn ++;

        // for (auto &line : grid)
        //     cout << line << endl;
        // cout << endl;

        nextGrid = emptyGrid;
        for (auto &b : blizzards) {
             b.move();
             nextGrid[b.h][b.w] = '&';
        }

        for (int i=1; i<height-1; i++)
            for (int j=1; j<width-1; j++)
                if (grid[i][j]=='E') {
                    if (nextGrid[i][j] == '.') nextGrid[i][j] = 'E';
                    if (nextGrid[i-1][j] == '.') nextGrid[i-1][j] = 'E';
                    if (nextGrid[i+1][j] == '.') nextGrid[i+1][j] = 'E';
                    if (nextGrid[i][j-1] == '.') nextGrid[i][j-1] = 'E';
                    if (nextGrid[i][j+1] == '.') nextGrid[i][j+1] = 'E';
                }
        grid = nextGrid;
        if (grid[height-2][width-2] == 'E')
            break;
    }

    for (int i=1; i<height-2; i++)
        for (int j=1; j<width-1; j++)
            if (grid[i][j]=='E')
                grid[i][j]='.';

    while(true) {
        turn ++;
        nextGrid = emptyGrid;
        for (auto &b : blizzards) {
             b.move();
             nextGrid[b.h][b.w] = '&';
        }

        for (int i=1; i<height-1; i++)
            for (int j=1; j<width-1; j++)
                if (grid[i][j]=='E') {
                    if (nextGrid[i][j] == '.') nextGrid[i][j] = 'E';
                    if (nextGrid[i-1][j] == '.') nextGrid[i-1][j] = 'E';
                    if (nextGrid[i+1][j] == '.') nextGrid[i+1][j] = 'E';
                    if (nextGrid[i][j-1] == '.') nextGrid[i][j-1] = 'E';
                    if (nextGrid[i][j+1] == '.') nextGrid[i][j+1] = 'E';
                }
        grid = nextGrid;
        if (grid[1][1] == 'E')
            break;
    }

    for (int i=2; i<height-1; i++)
        for (int j=1; j<width-1; j++)
            if (grid[i][j]=='E')
                grid[i][j]='.';
    while(true) {
        turn ++;
        nextGrid = emptyGrid;
        for (auto &b : blizzards) {
             b.move();
             nextGrid[b.h][b.w] = '&';
        }

        for (int i=1; i<height-1; i++)
            for (int j=1; j<width-1; j++)
                if (grid[i][j]=='E') {
                    if (nextGrid[i][j] == '.') nextGrid[i][j] = 'E';
                    if (nextGrid[i-1][j] == '.') nextGrid[i-1][j] = 'E';
                    if (nextGrid[i+1][j] == '.') nextGrid[i+1][j] = 'E';
                    if (nextGrid[i][j-1] == '.') nextGrid[i][j-1] = 'E';
                    if (nextGrid[i][j+1] == '.') nextGrid[i][j+1] = 'E';
                }
        grid = nextGrid;
        if (grid[height-2][width-2] == 'E')
            break;
    }

    cout << turn << endl;

    return 0;
}
