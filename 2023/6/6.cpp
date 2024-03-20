#include <iostream>
#include <vector>
#include <cmath>

const int n=4;

using namespace std;

int main() {
    string s;
    cin >> s;

    vector<double> times(n);
    vector<double> dist(n);
    for (auto &t : times)
        cin >> t;

    cin >> s;
    for (auto &d : dist)
        cin >> d;
    
    int result = 1;
    for (int i=0; i<n; i++) {
        // cout << times[i] << " " << dist[i] << endl;
        double delta = times[i]*times[i] - 4*dist[i];
        double x1 = (times[i]-sqrt(delta)) / 2;
        double x2 = (times[i]+sqrt(delta)) / 2;

        double x11 = ceil(x1);
        double x22 = floor(x2);

        if (x11==x1) x11++;
        if (x22==x2) x22--;


        // cout << x11 << " " << x22 << endl;
        result *= x22-x11+1;
    }
    cout << result << endl;
}