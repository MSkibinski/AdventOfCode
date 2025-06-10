#include <iostream>
#include <vector>

using namespace std;

struct Line {
    long long x, y;
    double dx;
    double A, B, C;
};

int main() {
    long long minV, maxV;
    cin >> minV >> maxV;

    long long x, y, z;
    double dx, dy, dz;
    char c;

    vector<Line> lines; 
    while (cin >> x >> c >> y >> c >> z >> c >> dx >> c >> dy >> c >> dz) {
        double A = dy / dx;
        double B = -1;
        double C = y - x*A;
        lines.push_back({x, y, dx, A, B, C});
    }

    int result = 0;

    for (int i=0; i<lines.size(); i++) {
        for (int j=i+1; j<lines.size(); j++) {
            Line p1 = lines[i];
            Line p2 = lines[j];
            double W = p2.A - p1.A;
            if (W == 0) {
                // cout << "rownolegle" << endl;
                continue;           
            } 
            double Wx = p1.C - p2.C;
            double Wy = -p1.A*p2.C + p2.A*p1.C;
            double x = Wx/W;
            double y = Wy/W;
            // cout << x << "  " << y << endl;
            if ((x > p1.x && p1.dx < 0) || (x<p1.x && p1.dx > 0) || (x > p2.x && p2.dx < 0) || (x < p2.x && p2.dx > 0))
                continue;

            if (x >= minV && y >= minV && x <= maxV && y <= maxV) {
                result++;
                // cout << "dodany" << endl;
            }
        }
    }
    cout << result << endl;
}
