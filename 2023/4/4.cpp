#include <iostream>
#include <vector>

using namespace std;

// const int cards = 6;
// const int n_winning = 5;
// const int n_my = 8;

const int cards = 190;
const int n_winning = 10;
const int n_my = 25;

int main() {
    int result = 0;
    for (int i=0; i<cards; i++) {
        string s;
        cin >> s >> s;
        vector<int> winningNumbers(n_winning);
        for (auto &n : winningNumbers)
            cin >> n;
        cin >> s;
        int n1, points=0;
        for (int j=0; j<n_my; j++) {
            cin >> n1;
            for (auto n2 : winningNumbers) {
                if (n1==n2) {
                    points = points==0 ? 1 : points*2;
                    break;
                }
            }
        }
        result += points;
    }
    cout << result << endl;
}