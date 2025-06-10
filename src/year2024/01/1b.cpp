#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int a, b;
    vector<int> v1, v2;
    while (cin >> a >> b) {
        v1.push_back(a);
        v2.push_back(b);
    }
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    v2.push_back(v1.back() + 1);
    
    int sum = 0;
    for (int i=0, j=0; i<v1.size(); i++) {
        int n = 1;
        while (i<v1.size()-1 && v1[i] == v1[i+1]) {
            n++;
            i++;
        }
        while (v2[j]<v1[i]) j++;
        int m = 0;
        while (v2[j] == v1[i]) {
            m++;
            j++;
        }
        sum += v1[i] * n * m;
    }
    
    std::cout << sum << endl;

    return 0;
}