

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> v;
vector<int> len;

bool calculate(long long current, int id, long long result) {
    // cout << current << endl;
    if (id == v.size()) {
        return current == result;
    }
    
    if (current > result)
        return false;
    
    bool possible = calculate(current + v[id], id+1, result);
    if (possible) return true;
    possible = calculate(current * v[id], id+1, result);
    if (possible) return true;
    return calculate(current * pow(10, len[id]) + v[id], id+1, result);
}

int main()
{
    string line;
    
    long long sum = 0;
    while (getline(cin, line)) {
        istringstream is( line );
        
        long long result;
        char c;
        v.clear();
        len.clear();
        int a;
        
        is >> result >> c;
        while (is >> a) {
            v.push_back(a);
            len.push_back(to_string(a).length());
        }
        
        if(calculate(v[0], 1, result)) {
            sum += result;
        }
        //cout << endl;
    }
    
    cout << sum;

    return 0;
}