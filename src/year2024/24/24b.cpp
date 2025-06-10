/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Cable {
    vector<bool> in;
    string op;
    bool value;
    vector<string> out;
    
    bool addInput(bool v) {
        in.push_back(v);
        if (in.size() == 2) {
            if (op == "AND") {
                value = in[0] && in[1];
            }
            else if (op == "OR") {
                value = in[0] || in[1];
            }
            else { // XOR
                value = (!in[0] == in[1]);
            }
            return true;
        }
        return false;
    }
};



int main()
{
    map<string, Cable> cables;
    queue<string> calculated;
    string line;
    for (getline(cin, line); !line.empty(); getline(cin, line)) {
        istringstream ss(line);
        string name;
        int value;
        ss >> name >> value;
        name.pop_back();
        cables[name].value = value;
        calculated.push(name);
    }
    
    string in1, in2, out, op;
    while (cin >> in1 >> op >> in2 >> out >> out) {
        cables[out].op = op;
        cables[in1].out.push_back(out);
        cables[in2].out.push_back(out);
    }
    
    for (auto &[name, cable] : cables) {
        cout << name << ": ";
        for (auto out : cable.out) {
            cout << out << " ";
        }
        cout << endl;
    }
    
    auto cableXIt = cables.find("x00");
    auto cableYIt = cables.find("y00");
    for (int id=0; cableXIt->first[0] == 'x'; id++, cableXIt++, cableYIt++) {
        auto &outX = cableXIt->second.out;
        auto &outY = cableYIt->second.out;
        sort (outX.begin(), outX.end());
        sort (outY.begin(), outY.end());
        if (outX[0] != outY[0]) {
            cout << outX[0] << ", " << outY[0] << endl;
        }
        if (outX[1] != outY[1]) {
            cout << outX[1] << ", " << outY[1] << endl;
        }
        cout << cableXIt->first << " " << cableYIt->first << " " << outX[0] << " " << outY[1] << endl;
    }
    
    
    while (!calculated.empty()) {
        string name = calculated.front(); calculated.pop();
        auto &cable = cables[name];
        for (auto name : cable.out) {
            if(cables[name].addInput(cable.value)) {
                calculated.push(name);
            }
        }
    }
    
    /*for (auto [name, cable] : cables) {
        cout << name  << " " << cable.value << endl;
    }*/
    auto cableIt = cables.find("z00");
    long long result = 0;
    for (int i=0; cableIt != cables.end(); cableIt++, i++) {
        cout << cableIt->first << endl;
        long long v = cableIt->second.value;
        result |= v << i;
    }

    cout << result << endl;

    return 0;
}