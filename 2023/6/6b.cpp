#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

int main() {
    // double t =  71'530;
    // double d = 940'200;

    long double t =          56'977'793;
    long double d = 499'221'010'971'440;

    long double delta = t*t - 4*d;
    cout << delta << endl;
    auto x1 = (t-sqrt(delta)) / 2;
    auto x2 = (t+sqrt(delta)) / 2;

    // 35 349 467,48

    // 10814163
    // 46163631

    // 35349469 - kalkulator

    // 46163630,2

    // cout << x1 << " " << x2 << endl;
    double x11 = ceil(x1);
    double x22 = floor(x2);

    // if (x11==x1) x11++;
    // if (x22==x2) x22--;


    cout << x11 << " " << x22 << endl;
    int result = x22-x11+1;
    cout << result << endl;
}