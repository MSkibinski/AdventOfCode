#include <iostream>
#include <vector>
#include <list>

using namespace std;

int getHash(const string &s) {
    int hash = 0;
    for (auto c : s)
        hash = ((hash + c) * 17) % 256;
    return hash;
}

int main()
{
    vector<list<pair<string, int>>> boxes(256);

    string s;
    for (getline(cin, s, ','); !s.empty(); getline(cin, s, ',')) {
        // cout << s << endl;
        auto pos = s.find_first_of("=-");
        string label = s.substr(0, pos);
        auto &box = boxes[getHash(label)];

        if (s[pos] == '=') {
            int power = s[pos+1] - '0';
            bool found = false;
            for (auto &elem : box) {
                if (elem.first == label) {
                    elem.second = power;
                    found = true;
                    break;
                }
            }
            if (!found)
                box.push_back({label, power});
        }
        else {
            auto it = box.begin();
            while (it != box.end()) {
                if (it->first==label)
                    break;
                it++;
            }
            if (it != box.end())
                box.erase(it);
        }
    }

    int result = 0;
    int boxId = 1;
    for (auto &box : boxes) {
        int slot=1;
        for (auto &[label, power] : box) {
            result += boxId * slot * power;
            slot++;
        }
        boxId++;
    }

    cout << result << endl;
}
