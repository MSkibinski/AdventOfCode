
#include <iostream>
#include <vector>
#include <map>
#include <regex>

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
        line = regex_replace(line, regex("#"), "##");
        line = regex_replace(line, regex("\\."), "..");
        line = regex_replace(line, regex("O"), "[]");
        line = regex_replace(line, regex("@"), "@.");

        warehouse.push_back(line);
        if (auto pos = line.find('@'); pos != string::npos) {
            robot = {h, pos};
        }
    }
    
    /*for (auto &line : warehouse) {
        cout << line << endl;
    }*/
    
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
            else if (nextC == '[' || nextC == ']') {
                if (c == '<' || c=='>') {
                    auto nP = nextPosition + d + d;
                    while (warehouse[nP.first][nP.second] == '[' || warehouse[nP.first][nP.second] == ']') {
                        nP = nP + d + d;
                    }
                    char &firstAfterBoxes = warehouse[nP.first][nP.second];
                    if (firstAfterBoxes == '.') {
                        auto &line = warehouse[robot.first];
                        int di = c=='<' ? 1 : -1;
                        for (int i = nP.second; i!=robot.second; i += di) {
                            line[i] = line[i+di];
                        }
                        line[robot.second] = '.';
                        robot = nextPosition;
                    }
                }
                else {
                    vector<pair<int, int>> boxPositions;
                    boxPositions.push_back({nextPosition.first, nextC=='[' ? nextPosition.second : nextPosition.second - 1});
                    
                    bool possible = true;
                    for (int i=0; i<boxPositions.size(); i++) {
                        auto nP = boxPositions[i] + d;
                        char c1 = warehouse[nP.first][nP.second];
                        char c2 = warehouse[nP.first][nP.second+1];
                        if (c1 == '#' || c2 == '#') {
                            possible = false;
                            break;
                        }
                        if (c1 == '[') {
                            boxPositions.push_back(nP);
                        }
                        else {
                            if (c1 == ']') {
                                boxPositions.push_back({nP.first, nP.second-1});
                            }
                            if (c2 == '[') {
                                boxPositions.push_back({nP.first, nP.second+1});
                            }
                        }
                    }
                    
                    if (possible) {
                        for (int i = boxPositions.size()-1; i>=0; i--) {
                            auto nP = boxPositions[i] + d;
                            warehouse[nP.first][nP.second] = '[';
                            warehouse[nP.first][nP.second+1] = ']';
                            warehouse[boxPositions[i].first][boxPositions[i].second] = '.';
                            warehouse[boxPositions[i].first][boxPositions[i].second+1] = '.';
                        }
                        warehouse[robot.first][robot.second] = '.';
                        nextC = '@';
                        robot = nextPosition;
                    }
                }
            }
        }
    }
    
    /*for (auto &line : warehouse) {
        cout << line << endl;
    }*/
    
    int sizeh = warehouse.size();
    int sizew = warehouse[0].size();
    int sum = 0;
    for (int h=0; h<sizeh; h++) {
        for (int w=0; w<sizew; w++) {
            if (warehouse[h][w] == '[') {
                sum += h*100 + w;
            }
        }
    }
    
    cout << sum << endl;

    return 0;
}