

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> v;

bool calculate(long long current, int id, long long result) {
    if (id == v.size()) {
        return current == result;
    }
    
    if (current > result)
        return false;
    
    bool possible = calculate(current + v[id], id+1, result);
    if (possible) return true;
    return calculate(current * v[id], id+1, result);
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
        int a;
        
        is >> result >> c;
        while (is >> a) {
            v.push_back(a);
        }
        
        if(calculate(v[0], 1, result)) {
            sum += result;
        }
    }
    
    cout << sum;

    return 0;
}