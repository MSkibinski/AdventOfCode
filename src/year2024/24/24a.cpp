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

using namespace std;

struct Gate {
    int value1, value2;
    bool v1set, v2set;
    int op;
};

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