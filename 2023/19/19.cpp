#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> split(const string &input) {
    vector<string> result;

    stringstream ss(input);
    string s;
    while (getline(ss, s, ','))
        result.push_back(s);

    return result;
}

struct Part {
    int x, m, a, s;

    Part(const string &str) {
        auto v = split(str.substr(1, str.size()-2));
        x = stoi(v[0].substr(2));
        m = stoi(v[1].substr(2));
        a = stoi(v[2].substr(2));
        s = stoi(v[3].substr(2));
    }

    int get(char c) const {
        switch (c) {
            case 'x': return x;
            case 'm': return m;
            case 'a': return a;
            case 's': return s;
        }
        return 0;
    }

    int getSum() const {
        return x+m+a+s;
    }
};

class Workflow;

unordered_map<string, Workflow> workflows;

class Workflow {
    struct Rule {
        char category;
        char op;
        int val;
        string name;

        Rule(const string &s) {
            category = s[0];
            op = s[1];
            val = stoi(s.substr(2));
            name = s.substr(s.find(':')+1);
        }

        bool isAccepted(const Part &p) {
            int v = p.get(category);
            return op == '>' ? v > val : v < val;
        }
    };

    vector<Rule> rules;
    string last;

public:
    Workflow() {}
    Workflow (const string &s) {
        auto v = split(s);
        for(int i=0; i<v.size()-1; i++)
            rules.push_back(Rule(v[i]));
        last = v.back();
        last.pop_back();
    }

    bool isAccepted(const Part &p) {
        for (auto &r : rules)
            if (r.isAccepted(p)) {
                if (r.name == "A")
                    return true;
                else if (r.name == "R")
                    return false;
                return workflows[r.name].isAccepted(p);
            }

        if (last == "A")
            return true;
        else if (last == "R")
            return false;
        return workflows[last].isAccepted(p);
    }
};

int main()
{
    string line;
    for (getline(cin, line); !line.empty(); getline(cin, line)) {
        auto pos = line.find('{');
        workflows[line.substr(0, pos)] = Workflow(line.substr(pos+1));
    }

    int result=0;
    while (cin >> line) {
        Part p(line);
        if (workflows["in"].isAccepted(p))
            result += p.getSum();
    }

    cout << result << endl;
}
