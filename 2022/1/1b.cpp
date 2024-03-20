#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> result;
    while (cin.peek() != EOF) {
        int curr = 0;
        int x;
        while (cin.peek() != '\n') {
            cin >> x; cin.ignore();
            curr += x;
        }
        cin.ignore();

        result.push_back(curr);
    }
    nth_element(result.begin(),result.begin()+2, result.end(), greater{});

    cout << result[0]+result[1]+result[2] << endl;
}