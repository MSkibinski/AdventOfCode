#include <iostream>

using namespace std;

int main()
{
    int x1, y1, x2, y2;
    char c;

    int pairs = 0;
    while (cin >> x1 >> c >> y1 >> c >> x2 >> c >> y2) {
        if ((x1 >= x2 && x1<=y2) || (y1 >= x2 && y1<=y2) || (x2 >= x1 && x2<=y1) || (y2 >= x1 && y2<=y1))
             pairs++;
    }

    cout << pairs << endl;
    return 0;
}
