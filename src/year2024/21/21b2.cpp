
#include <iostream>
#include <vector>
#include <numeric>
#include <climits>
//#include <algorithm>

using namespace std;

int charToId[256];

vector<vector<string>> shortestPath(11, vector<string>(11));
string numeric_keypad = "789456123 0A";
string directional_keypad = " ^A<v>";

vector<vector<vector<string>>> shortestDirPath(6, vector<vector<string>>(6, vector<string>(25)));


string takeShortestPathForDirecional(int from, int to, int level) {
    if (shortestDirPath[from][to][level].empty()) {
        int pFrom = from;
        int pTo = to;
        int dh = pTo/3 - pFrom/3; 
        int dw = pTo%3 - pFrom%3;
        char cVertical = dh > 0 ? 'v' : '^';
        char cHorizontal = dw > 0 ? '>' : '<';
        dh = abs(dh);
        dw = abs(dw);
        
        string path;
        if (dw && cHorizontal=='<' && (pTo % 3 !=0 || pFrom/3 != 0)) {
            path += string(dw, '<');
            dw = 0;
        }
        if (dh && cVertical == 'v') {
            path += string(dh, 'v');
            dh = 0;
        }
        if (dw && cHorizontal=='<') {
            path += string(dw, '<');
            dw = 0;
        }
        
        if (dh && cVertical == '^' && (pTo / 3 !=0 || pFrom%3 != 0)) {
            path += string(dh, '^');
            dh = 0;
        }
        if (dw && cHorizontal=='>') {
            path += string(dw, '>');
            dw = 0;
        }
        if (dh && cVertical == '^') {
            path += string(dh, '^');
            dh = 0;
        }
        path += 'A';
        
        if (level == 0) {
            shortestDirPath[from][to][level] = path;
        }
        else {
            cout << path << endl;
            for (char c : path) {
                pTo = charToId[c];
                shortestDirPath[from][to][level] += takeShortestPathForDirecional(pFrom, pTo, level-1);
                pFrom = pTo;
            }
        }
    }
    cout << from << " " << to << " " << level << ": " << shortestDirPath[from][to][level] << endl;
    return shortestDirPath[from][to][level];
}


string takeShortestPath(int from, int to) {
    if (shortestPath[from][to].empty()) {
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
        path += 'A';
        
        pFrom = charToId['A'];
        cout << path << endl;
        for (char c : path) {
            pTo = charToId[c];
            shortestPath[from][to] += takeShortestPathForDirecional(pFrom, pTo, 1);
            pFrom = pTo;
        }
    }
    return shortestPath[from][to];
}

int main()
{
    charToId['^'] = 1;
    charToId['A'] = 2;
    charToId['<'] = 3;
    charToId['v'] = 4;
    charToId['>'] = 5;
    
    string code;
    int result = 0;
    while (cin >> code) {
        cout << code << endl;
        int from = 10;
        int r = 0;
        string rPath;
        for (char c : code) {
            int to = c == 'A' ? 10 : c-'0';
            rPath += takeShortestPath(from, to);
            from = to;
        }
        cout << rPath << endl;
        result += rPath.size() * stoi(code.substr(0,3));
    }
    cout << result << endl;
    
    return 0;
}