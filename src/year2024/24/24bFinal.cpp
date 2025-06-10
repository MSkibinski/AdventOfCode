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
    vector<string> inName;
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
        cables[out].inName.push_back(in1);
        cables[out].inName.push_back(in2);
    }
    
    for (auto &[name, cable] : cables) {
        sort(cable.out.begin(), cable.out.end());
        cout << name << ": ";
        for (auto out : cable.out) {
            cout << out << " ";
        }
        cout << endl;
    }
    
    auto cableXIt = cables.find("x01");
    auto cableYIt = cables.find("y01");
    string carryName = cables["x00"].out[0] == "z00" ? cables["x00"].out[1] : cables["x00"].out[0]; // name of gate for carry;
    vector<string> cableNamesToChange;
    for (int id=1; cableXIt->first[0] == 'x'; id++, cableXIt++, cableYIt++) {
        auto &outX = cableXIt->second.out;
        string XYxorGateName; 
        string XYandGateName; 
        if (cables[outX[0]].op == "XOR") {
            XYxorGateName = outX[0];
            XYandGateName = outX[1];
        }
        else {
            XYxorGateName = outX[1];
            XYandGateName = outX[0];
        }
        auto &XYxorGate = cables[XYxorGateName];
        auto &XYandGate = cables[XYandGateName];
        
        auto &carryCable = cables[carryName];
        
        string zOutName = "z";
        if (id < 10) {
            zOutName += "0";
        }
        zOutName += to_string(id);
        if (XYxorGate.out != carryCable.out) {
            auto &zGate = cables[zOutName];
            // ktorys jest zamieniony
            bool XYcorrect = false;
            string correctName = carryName;
            string inCorrectName = XYxorGateName;
            for (auto outXY : XYxorGate.out) {
                if (outXY == zOutName) {
                    XYcorrect = true;
                    swap (correctName, inCorrectName);
                }
            }

            string nameToFind;
            for (auto in : zGate.inName) {
                if (in != correctName)
                    nameToFind = in;
            }
            cableNamesToChange.push_back(inCorrectName);
            cableNamesToChange.push_back(nameToFind);
            swap(cables[inCorrectName], cables[nameToFind]);
            cout << "zamiana " << inCorrectName << " " << nameToFind << endl;
        }
        
        string secondXorGateName = XYxorGate.out[0];
        string secondAndGateName = XYxorGate.out[1];
        if (cables[XYxorGate.out[1]].op == "XOR") {
            swap(secondXorGateName, secondAndGateName);
        }
        
        if (secondXorGateName != zOutName) {
            swap(cables[secondXorGateName], cables[zOutName]);
            cout << "zamiana " << secondXorGateName << " " << zOutName << endl;
            cableNamesToChange.push_back(secondXorGateName);
            cableNamesToChange.push_back(zOutName);
        }
        
        auto &secondAndGate = cables[secondAndGateName];
        if (secondAndGate.out[0] != XYandGate.out[0]) {
            
        }
        carryName = secondAndGate.out[0];
    }
    
    sort(cableNamesToChange.begin(), cableNamesToChange.end());
    for (auto cName : cableNamesToChange) {
        cout << cName << ",";
    }
    cout << endl;
    
    
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