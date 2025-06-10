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

struct Range {
    vector<pair<int, int>> r;

    Range() : r(4, {1, 4000}) {}

    pair<int, int>& get(char c) {
        switch (c) {
            case 'x': return r[0];
            case 'm': return r[1];
            case 'a': return r[2];
            default: return r[3];
        }
    }

    long long getSum() const {
        long long result = 1;
        for (auto [i, j] : r) {
            result *= (j-i+1);
            if (i>j) result = 0;
        }
        return result;
    }

    void print() {
        for (auto v : r) {
            cout << v.first << "-" << v.second << ",";
        }
        cout << endl;
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
            auto pos = s.find(':');
            if (pos == string::npos) {
                op = 0;
                name = s;
                return;
            }
            category = s[0];
            op = s[1];
            val = stoi(s.substr(2));
            name = s.substr(s.find(':')+1);
        }

        void applyRule(Range &r, Range &r2) {
            auto &v = r.get(category);
            auto &v2 = r2.get(category);
            if (op == '<') {
                v2.second = val-1;
                v.first = val;
            }
            else {
                v2.first = val+1;
                v.second = val;
            }
        }
    };

    vector<Rule> rules;

public:
    Workflow() {}
    Workflow (const string &s) {
        for (auto &rule : split(s))
            rules.push_back(Rule(rule));
    }

    long long possibilities(Range r) {
        long long result = 0;
        for (int i=0; i<rules.size()-1; i++) {
            Range r2 = r;
            rules[i].applyRule(r, r2);

            if (rules[i].name == "A")
                result += r2.getSum();
            else if (rules[i].name == "R")
                result += 0;
            else
                result += workflows[rules[i].name].possibilities(r2);
        }

        if (rules.back().name == "A")
            result += r.getSum();
        else if (rules.back().name == "R")
            result += 0;
        else
            result += workflows[rules.back().name].possibilities(r);

        return result;
    }
};

int main()
{
    string line;
    for (getline(cin, line); !line.empty(); getline(cin, line)) {
        auto pos = line.find('{');
        auto name = line.substr(0, pos);
        auto val = line.substr(pos+1); val.pop_back();
        workflows[name] = Workflow(val);
    }

    cout << workflows["in"].possibilities(Range()) << endl;
}
