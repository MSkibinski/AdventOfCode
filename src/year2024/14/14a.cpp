
#include <iostream>
#include <vector>

using namespace std;


int main()
{
    char c;
    int px, py, vx, vy;
    
    //int height = 7;
    //int width = 11;
    int height = 103;
    int width = 101;
    int t = 100;
    
    vector<int> sum(4);
    
    vector<string> room(height, string(width, '.'));
    
    while (cin >> c >> c >> px >> c >> py >> c >> c >> vx >> c >> vy) {
        int x = (px + vx*t) % width;
        int y = (py + vy*t) % height;
        if (x<0) x+= width;
        if (y<0) y+= height;
        //cout << x << " " << y << endl;
        if (room[y][x] == '.') room[y][x] = '1';
        else room[y][x]++;
        
        if (x < width / 2) {
            if (y < height / 2) {
                sum[0]++;
            }
            else if (y > height / 2) {
                sum[1]++;
            }
        }
        else if (x > width / 2) {
            if (y < height / 2) {
                sum[2]++;
            }
            else if (y > height / 2) {
                sum[3]++;
            }
        }
        //cout << px << " " << py << " " << vx << " " << vy << endl;
    }
    int result = 1;
    for (auto s : sum) {
        cout << s << endl;
        result *= s;
    }
    
    for (auto line : room) {
        //cout << line << endl;
    }
    
    cout << result;

    return 0;
}