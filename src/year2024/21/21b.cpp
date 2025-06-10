
#include <iostream>
#include <vector>
#include <numeric>
#include <climits>
//#include <algorithm>

using namespace std;

int charToId[256];
charToId['^'] = 1;
charToId['A'] = 2;
charToId['<'] = 3;
charToId['v'] = 4;
charToId['>'] = 5;


vector<vector<int>> shortestPath(11, vector(11, 0));
string numeric_keypad = "789456123 0A";
string directional_keypad = " ^A<v>";

vector<vector<vector<string>>> shortestDirPath(6, vector<vector<string>>(6, vector(25));

void calculateShortestDirPath(int pFrom, int pTo, int level) {
    int dh = pTo/3 - pFrom/3; 
    int dw = pTo%3 - pFrom%3;
    char cVertical = dh > 0 ? 'v' : '^';
    char cHorizontal = dw > 0 ? '>' : '<';
    dh = abs(dh);
    dw = abs(dw);
    
    string path;
    if (dw && cHorizontal=='<' && (pTo % 3 !=0 || pFrom/3 != 3)) {
        path += string(dw, '<');
        dw = 0;
    }
    if (dh && cVertical == '^') {
        path += string(dh, '^');
        dh = 0;
    }
    if (dw && cHorizontal=='<') {
        path += string(dw, '<');
        dw = 0;
    }
    
    if (dh && cVertical == 'v' && (pTo / 3 !=3 || pFrom%3 != 0)) {
        path += string(dh, 'v');
        dh = 0;
    }
    if (dw && cHorizontal=='>') {
        path += string(dw, '>');
        dw = 0;
    }
    if (dh && cVertical == 'v') {
        path += string(dh, 'v');
        dh = 0;
    }
    
    if (level == 0) {
        shortestDirPath[pFrom][pTo][0] = path;
    }
    else {
        string result;
        for (char c : path) {
            result += takeShortestDirPath(from, c, level-1);
        }
        shortestDirPath[pFrom][pTo][level] = result;
    }
    
    return shortestDirPath[pFrom][pTo][level];
}

string takeShortestDirPath(char cFrom, char cTo, int level) {
    int from = charToId[cFrom];
    int to = charToId[cTo];;
    if (shortestDirPath[from][to][level].empty())
        calculateShortestDirPath(cFrom, cTo, int level);
        
    return shortestDirPath[from][to][level];
}
    
    int dh = pTo/3 - pFrom/3; 
    int dw = pTo%3 - pFrom%3;
    char cVertical = dh > 0 ? 'v' : '^';
    char cHorizontal = dw > 0 ? '>' : '<';
    dh = abs(dh);
    dw = abs(dw);
    
    string path;
    if (dw && cHorizontal=='<' && (pTo % 3 !=0 || pFrom/3 != 3)) {
        path += string(dw, '<');
        dw = 0;
    }
    if (dh && cVertical == '^') {
        path += string(dh, '^');
        dh = 0;
    }
    if (dw && cHorizontal=='<') {
        path += string(dw, '<');
        dw = 0;
    }
    
    if (dh && cVertical == 'v' && (pTo / 3 !=3 || pFrom%3 != 0)) {
        path += string(dh, 'v');
        dh = 0;
    }
    if (dw && cHorizontal=='>') {
        path += string(dw, '>');
        dw = 0;
    }
    if (dh && cVertical == 'v') {
        path += string(dh, 'v');
        dh = 0;
    }
    
    if (level == 0) {
        
    }
}

int calculateShortestPathForDirectional(string &s, int level) {
    int pFrom = 2; // position of A
    
    int cFrom = 'A';
    
    result = 0;
    for (char cTo: s) {
        result += takeShortestDirPath(cFrom, cTo, level-1) {
        cFrom = cTo;
    }
    
    return result;
    
    vector<string> paths1(1), paths2;
    
    for (char c: s) {
        auto pTo = directional_keypad.find(c);
        if (pTo == pFrom) {
            for (auto &path : paths1) {
                path += "A";
            }   
        }
        else {
            int dh = pTo/3 - pFrom/3; 
            int dw = pTo%3 - pFrom%3;
            char cVertical = dh > 0 ? 'v' : '^';
            char cHorizontal = dw > 0 ? '>' : '<';
            dh = abs(dh);
            dw = abs(dw);
            
            vector<string> paths;
            if (dh && dw) {
                if (pTo/3 == 0 && pFrom%3 == 0) {
                    string path = string(dw, cHorizontal) + string(dh, cVertical) + "A";
                    paths.push_back(path);
                }
                else if (pTo % 3 ==0 && pFrom/3 == 0) {
                    string path = string(dh, cVertical) + string(dw, cHorizontal) + "A";
                    paths.push_back(path);
                }
                else {
                    string path1 = string(dw, cHorizontal) + string(dh, cVertical) + "A";
                    string path2 = string(dh, cVertical) + string(dw, cHorizontal) + "A";
                    paths.push_back(path1);
                    paths.push_back(path2);
                }
            }
            else {
                string path = string(dw, cHorizontal) + string(dh, cVertical) + "A";
                paths.push_back(path);
            }
            
            if (paths.size() == 2) {
                paths2 = paths1;
                for (auto &path : paths2) {
                    path += paths[1];
                }
            }
            
            for (auto &path : paths1) {
                path += paths[0];
            }
            
            if (paths.size() == 2) {
                paths1.insert(paths1.end(), paths2.begin(), paths2.end());
            }
        }
        pFrom = pTo;
    }
    
    int result = INT_MAX;
    if (level == 1) {
        for (auto path : paths1) {
            cout << path << endl;
            result = min(result, (int)path.size());
        }
    }
    else {
        for (auto path : paths1) {
            cout << path << endl;
            result = min(result, calculateShortestPathForDirectional(path, level-1));
        }
    }
    return result;
}

int calculateShortestPath(int from, int to) {
    if (shortestPath[from][to]==0) {
        char cFrom = from==10 ? 'A' : '0' + from;
        char cTo = to==10 ? 'A' : '0' + to;
        
        auto pFrom = numeric_keypad.find(cFrom);
        auto pTo = numeric_keypad.find(cTo);
        
        int dh = pTo/3 - pFrom/3; 
        int dw = pTo%3 - pFrom%3;
        char cVertical = dh > 0 ? 'v' : '^';
        char cHorizontal = dw > 0 ? '>' : '<';
        dh = abs(dh);
        dw = abs(dw);
        
        string path;
        if (dw && cHorizontal=='<' && (pTo % 3 !=0 || pFrom/3 != 3)) {
            path += string(dw, '<');
            dw = 0;
        }
        if (dh && cVertical == '^') {
            path += string(dh, '^');
            dh = 0;
        }
        if (dw && cHorizontal=='<') {
            path += string(dw, '<');
            dw = 0;
        }
        
        if (dh && cVertical == 'v' && (pTo / 3 !=3 || pFrom%3 != 0)) {
            path += string(dh, 'v');
            dh = 0;
        }
        if (dw && cHorizontal=='>') {
            path += string(dw, '>');
            dw = 0;
        }
        if (dh && cVertical == 'v') {
            path += string(dh, 'v');
            dh = 0;
        }
        
        shortestPath[from][to] = calculateShortestPathForDirectional(path, 2);
    }
    return shortestPath[from][to];
}

int main()
{
    for (int i = 0; i<11; i++) {
        for (int j = 0; j<11; j++) {
            if (i==j) {
                shortestPath[i][j] == 1;
                continue;
            }
            
            shortestPath[i][j] = calculateShortestPath(i, j);
        }
    }
    
    string code;
    int result = 0;
    while (cin >> code) {
        cout << code << endl;
        int from = 10;
        int r = 0;
        for (char c : code) {
            int to = c == 'A' ? 10 : c-'0';
            r += shortestPath[from][to];
            from = to;
        }
        
        result += r * stoi(code.substr(0,3));
    }
    cout << result << endl;
    
    return 0;
}