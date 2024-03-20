#include <iostream>
#include <sstream>
#include <vector>
// #include <algorithm>

using namespace std;

string s;
vector<int> v;

vector<vector<long long>> calculated;

long long possibilities(int startId, int vId, int min_length) {
    if (calculated[startId][vId] != -1)
        return calculated[startId][vId];

    if (vId == v.size()) {
        calculated[startId][vId] = (s.find('#', startId) != string::npos ? 0 : 1);
        return calculated[startId][vId];
    }
    int length = s.size() - startId - min_length;
    if (length > 0) {
        int pos = s.find('#', startId);
        if (pos!=string::npos)
            length = min(length, pos-startId);
    }
    
    long long result = 0;
    bool last = (vId == v.size()-1);
    for (int x=0; x<=length; x++) {
        int pos = s.find('.', startId+x);
        if (pos==string::npos || pos >= startId+x+v[vId]) {
            if (last || s[startId+x+v[vId]] != '#') {
                result += possibilities(startId+x+v[vId]+(last?0:1), vId+1, min_length-v[vId]-1);
            }
        }
    }
    calculated[startId][vId] = result;
    return result;
}

int main()
{
    string a;
    long long result = 0;
    while (cin >> s >> a) {
        s = s+'?'+s+'?'+s+'?'+s+'?'+s;
        a = a+','+a+','+a+','+a+','+a+',';
        // cout << s << " " << a << endl;
        istringstream iss (a+',');
        v.clear();
        calculated.clear();
        int sum = -1;
        int x;
        char c;
        while (iss >> x >> c) {
            v.push_back(x);
            sum += x + 1;
        }

        calculated = vector<vector<long long>>(s.size()+1, vector<long long>(v.size()+1, -1));
        long long p = possibilities(0, 0, sum);
        // cout << p << endl;
        result += p;
    }

    cout << result << endl;
}
