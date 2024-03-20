#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int result = 0;
    while (cin.peek() != EOF) {
        int curr = 0;
        int x;
        while (cin.peek() != '\n') {
            cin >> x; cin.ignore();
            curr += x;
        }
        cin.ignore();

        result = max(result, curr);
    }
    cout << result << endl;
}