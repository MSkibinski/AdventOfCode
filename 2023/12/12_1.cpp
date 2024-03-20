#include <iostream>
#include <sstream>
#include <vector>
// #include <algorithm>

using namespace std;

string s;
vector<int> v;

vector<vector<bool>> possible;

int possibilities(int startId, int vId, int min_length) {
    if (vId == v.size()) {
        return s.find('#', startId) != string::npos ? 0 : 1;
    }
    int length = s.size() - startId - min_length; // +1 czy +v[vId]
    if (length > 0) {
        int pos = s.find('#', startId);
        if (pos!=string::npos)
            length = min(length, pos-startId);
    }
    
    int result = 0;
    bool last = (vId == v.size()-1);
    for (int x=0; x<=length; x++) {
        int pos = s.find('.', startId+x);
        if (pos==string::npos || pos >= startId+x+v[vId]) {
            if (last || s[startId+x+v[vId]] != '#') {
                result += possibilities(startId+x+v[vId]+(last?0:1), vId+1, min_length-v[vId]-1);
            }
        }
    }
    return result;
}

int main()
{
    string a;
    int result = 0;
    while (cin >> s >> a) {
        istringstream iss (a+',');
        v.clear();
        int sum = -1;
        int x;
        char c;
        while (iss >> x >> c) {
            v.push_back(x);
            sum += x + 1;
        }

        int p = possibilities(0, 0, sum);
        // cout << p << endl;
        result += p;
    }

    cout << result << endl;
}
