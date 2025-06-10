
#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T,typename U> 
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}      

vector<string> warehouse;
pair<int, int> robot;

vector<pair<int, int>> dd({{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
map<char, int> dirToId({{'v', 0}, {'^', 1}, {'>', 2}, {'<', 3}});

int main()
{
    string line;
    getline(cin, line);
    for(int h=0; !line.empty(); getline(cin, line), h++) {
        warehouse.push_back(line);
        if (auto pos = line.find('@'); pos != string::npos) {
            robot = {h, pos};
        }
    }
    
    while(getline(cin, line)) {
        //cout << line << endl;
        for (auto c : line) {
            auto d = dd[dirToId[c]];
            auto nextPosition = robot + d;
            
            auto &nextC = warehouse[nextPosition.first][nextPosition.second];
            if (nextC == '.') {
                warehouse[robot.first][robot.second] = '.';
                nextC = '@';
                robot = nextPosition;
            }
            else if (nextC == 'O') {
                auto nP = nextPosition + d;
                while (warehouse[nP.first][nP.second] == 'O') {
                    nP = nP + d;
                }
                char &firstAfterBoxes = warehouse[nP.first][nP.second];
                if (firstAfterBoxes == '.') {
                    firstAfterBoxes = 'O';
                    warehouse[robot.first][robot.second] = '.';
                    nextC = '@';
                    robot = nextPosition;
                }
            }
        }
    }
    
    int size = warehouse.size();
    int sum = 0;
    for (int h=0; h<size; h++) {
        for (int w=0; w<size; w++) {
            if (warehouse[h][w] == 'O') {
                sum += h*100 + w;
            }
        }
    }
    
    cout << sum << endl;

    return 0;
}