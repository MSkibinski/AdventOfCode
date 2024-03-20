#include <iostream>
#include <vector>

using namespace std;

struct Point {
    long long x, y, z;
    long long t;
};

struct Line {
    long long x, y, z;
    long long dx, dy, dz;
};

struct Vector {
    long long a, b, c;
};

int main() {
    long long minV, maxV;
    cin >> minV >> maxV;

    long long x, y, z;
    long long dx, dy, dz;
    char c;

    vector<Line> lines; 
    while (cin >> x >> c >> y >> c >> z >> c >> dx >> c >> dy >> c >> dz)
        lines.push_back({x, y, z, dx, dy, dz});

    long long A, B, C, D;
    for (long long t=0; ; t++) {
        Line p1 = lines[0];
        Line p2 = lines[1];
        p2.x += p2.dx*t; p2.y += p2.dy*t; p2.z += p2.dz*t;
        Line p3 = p1;
        p3.x += p3.dx; p3.y += p3.dy; p3.z += p3.dz;

        // http://wyznacznik.pl/plaszczyzna-w-przestrzeni-zadania
        Vector v12{p2.x-p1.x, p2.y-p1.y, p2.z-p1.z};
        Vector v13{p3.x-p1.x, p3.y-p1.y, p3.z-p1.z};
        // https://www.naukowiec.org/wzory/fizyka/iloczyn-wektorowy-dwoch-wektorow_869.html
        Vector n{v12.b*v13.c - v12.c*v13.b, v12.c*v13.a - v12.a*v13.c, v12.a*v13.b - v12.b*v13.a};
        A = n.a;
        B = n.b;
        C = n.c;
        D = -(A*p1.x + B*p1.y + C*p1.z);

        Point p;
        auto &k = lines[2];
        auto t3 = A*k.dx + B*k.dy + C*k.dz;
        auto t2 = A*k.x + B*k.y + C*k.z + D;
        if (t2 % t3) {
            if (t%100000000==0)
                cout << t << endl;
            continue;
        }
        cout << t << endl;
        // t3 = -t2/t3;
        // bool possible = true;
        // for (int i=3; i<lines.size() && possible; i++) {

        // }
        
        // p = {k.x + k.dx*t, k.y + k.dy*t, k.z + k.dz*t, t};
        break;
    }
    // for (int i=0, found = 0; i<lines.size() && !found; i++) {
    //     for (int j=i+1; j<lines.size() && !found; j++) {
    //         Line p1 = lines[i];
    //         Line p2 = lines[j];
    //         auto d = (double)p1.dx / p2.dx;
    //         auto d2 = (double)p2.dx / p1.dx;
    //         if (((double)p1.dy / p2.dy == d && (double)p1.dz / p2.dz == d) ||
    //             ((double)p2.dy / p1.dy == d2 && (double)p2.dz / p1.dz == d2)) {
    //             found = 1;

    //             Line p3 = p1;
    //             p3.x += p3.dx; p3.y += p3.dy; p3.z += p3.dz;
                
    //             // http://wyznacznik.pl/plaszczyzna-w-przestrzeni-zadania
    //             Vector v12{p2.x-p1.x, p2.y-p1.y, p2.z-p1.z};
    //             Vector v13{p3.x-p1.x, p3.y-p1.y, p3.z-p1.z};
    //             // https://www.naukowiec.org/wzory/fizyka/iloczyn-wektorowy-dwoch-wektorow_869.html
    //             Vector n{v12.b*v13.c - v12.c*v13.b, v12.c*v13.a - v12.a*v13.c, v12.a*v13.b - v12.b*v13.a};
    //             A = n.a;
    //             B = n.b;
    //             C = n.c;
    //             D = -(A*p1.x + B*p1.y + C*p1.z);

    //             cout << i << ", " << j << " tworza plaszczyzne" << endl;
    //             cout << A << ", " << B << ", " << C << ", " << D << endl;
    //         }
    //     }
    // }

    // // https://courseware.cemc.uwaterloo.ca/web/Gr12CaAn000/Public_Html/slides/V4/TheIntersectionOfALineAndAPlane.pdf
    // vector<Point> points;
    // for (int i=3; i<5; i++) {
    //     Point p;
    //     auto &k = lines[i];
    //     auto t = A*k.dx + B*k.dy + C*k.dz;
    //     auto t2 = A*k.x + B*k.y + C*k.z + D;
    //     // cout << t << " " << t2 << endl;
    //     t = -t2/t;
    //     p = {k.x + k.dx*t, k.y + k.dy*t, k.z + k.dz*t, t};
    //     points.push_back(p);
    //     // cout << t << endl; 
    // }
    // if (points[0].t > points[1].t)
    //     swap(points[0], points[1]);
    // auto &p1 = points[0];
    // auto &p2 = points[1];
    // auto dt = p2.t - p1.t;
    // dx = (p2.x - p1.x) / dt;
    // dy = (p2.y - p1.y) / dt;
    // dz = (p2.z - p1.z) / dt;

    // Point result{p1.x - dx*p1.t, p1.y - dy*p1.t, p1.z - dz*p1.t};

    // cout << result.x << ", " << result.y << ", " << result.z << endl;
    // cout << result.x + result.y + result.z << endl;
}
