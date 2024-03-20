#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

vector<string> broadcaster; 

class Module;

enum Pulse {
    low,
    high
};

unordered_map<string, Module> modules;

struct Info {
    string to;
    string from;
    Pulse pulse;
};
queue<Info> q;

class Module {
    char t;
    string name;
    vector<string> output;
    vector<string> input;
    vector<Pulse> lastInputPulse;
    bool isOn;
    
public:
    int lowPulses;
    int highPulses;
    Module () {}
    void init (char type, const string &n, const string &s) {
        t = type;
        name = n;
        isOn = false;
        lowPulses=0;
        highPulses=0;
        string s2;
        stringstream ss(s);
        while (ss >> s2) {
            cout << s2 << " ";
            output.push_back(s2);
            modules[s2].input.push_back(name);
            modules[s2].lastInputPulse.push_back(Pulse::low);
        }
        cout << endl;
    }

    void inputPulse(const string &from, Pulse pulse) {
        if (pulse == Pulse::low)
            lowPulses++;
        else
            highPulses++;
        if (t=='%') { // flip flop
            if (pulse == Pulse::low) {
                if (!isOn) {
                    isOn = !isOn;
                    sendPulse(Pulse::high);
                }
                else  {
                    isOn = !isOn;
                    sendPulse(Pulse::low);
                }
            }
        }
        else { // remember 
            int id = 0;
            while (input[id] != from) id++;
            lastInputPulse[id] = pulse;
            bool allHigh = true;
            for (auto p : lastInputPulse) {
                if (p == Pulse::low) {
                    allHigh = false;
                    break;
                }
            }
            if (allHigh) {
                sendPulse(Pulse::low);
            }
            else {
                sendPulse(Pulse::high);
            }
        }
    }

    void sendPulse (Pulse pulse) {
        for (auto &o : output) {
            q.push({o, name, pulse});
            //cout << name << " " << o << " " << (pulse == Pulse::low ? "low" : "high") << endl; 
        }
    }
};

void createModule(string &input) {
    stringstream ss(input);
    string s, s2, name;
    ss >> s >> s2;
    name = s.substr(1);
    cout << name << " ";
    getline(ss, s2);
    modules[name].init(s[0], name, s2);
}

void pushButton() {
    for (auto &name: broadcaster) {
        q.push({name, "broadcaster", Pulse::low});
    }
}

int main() {
    string line, s;
    getline(cin, line);
    stringstream ss(line);
    ss >> s >> s;
    while (ss >> s) {
        broadcaster.push_back(s);
        cout << s << " ";
    }
    cout << endl;

    while (getline(cin, line))
        createModule(line);

    long long result = 0;
    // for (int i=0; i<1000; i++) {
    while (modules["rx"].lowPulses == 0) {
        pushButton();
        result++;
        while (!q.empty()) {
            auto &[to, from, pulse] = q.front(); q.pop();
            modules[to].inputPulse(from, pulse);
        }
        // cout << modules["rx"].lowPulses << " " << modules["rx"].highPulses << endl;
    }

    cout << result << endl;
}
