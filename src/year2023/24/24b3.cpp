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
    long long A2, B2, C2, D2;





    // for (long long t=0; ; t++) {
    //     Line p1 = lines[0];
    //     Line p2 = lines[1];
    //     p2.x += p2.dx*t; p2.y += p2.dy*t; p2.z += p2.dz*t;
    //     Line p3 = p1;
    //     p3.x += p3.dx; p3.y += p3.dy; p3.z += p3.dz;

    //     // http://wyznacznik.pl/plaszczyzna-w-przestrzeni-zadania
    //     Vector v12{p2.x-p1.x, p2.y-p1.y, p2.z-p1.z};
    //     Vector v13{p3.x-p1.x, p3.y-p1.y, p3.z-p1.z};
    //     // https://www.naukowiec.org/wzory/fizyka/iloczyn-wektorowy-dwoch-wektorow_869.html
    //     Vector n{v12.b*v13.c - v12.c*v13.b, v12.c*v13.a - v12.a*v13.c, v12.a*v13.b - v12.b*v13.a};
    //     A = n.a;
    //     B = n.b;
    //     C = n.c;
    //     D = -(A*p1.x + B*p1.y + C*p1.z);

    //     Point p;
    //     auto &k = lines[2];
    //     auto t3 = A*k.dx + B*k.dy + C*k.dz;
    //     auto t2 = A*k.x + B*k.y + C*k.z + D;
    //     if (t2 % t3) {
    //         if (t%100000000==0)
    //             cout << t << endl;
    //         continue;
    //     }
    //     cout << t << endl;
    //     // t3 = -t2/t3;
    //     // bool possible = true;
    //     // for (int i=3; i<lines.size() && possible; i++) {

    //     // }
        
    //     // p = {k.x + k.dx*t, k.y + k.dy*t, k.z + k.dz*t, t};
    //     break;
    // }
    for (int i=0, found = 0; i<lines.size() && !found; i++) {
        int result = 0;
        int result2 = 0;
        for (int j=i+1; j<lines.size() && !found; j++) {
            if (i==j) continue;
            Line p1 = lines[i];
            Line p2 = lines[j];

            Line p3 = p1;
            p3.x += p3.dx; p3.y += p3.dy; p3.z += p3.dz;

            Line p4 = p2;
            p4.x += p4.dx; p4.y += p4.dy; p4.z += p4.dz;
            
            // http://wyznacznik.pl/plaszczyzna-w-przestrzeni-zadania
            Vector v12{p2.x-p1.x, p2.y-p1.y, p2.z-p1.z};
            Vector v13{p3.x-p1.x, p3.y-p1.y, p3.z-p1.z};
            // https://www.naukowiec.org/wzory/fizyka/iloczyn-wektorowy-dwoch-wektorow_869.html
            Vector n{v12.b*v13.c - v12.c*v13.b, v12.c*v13.a - v12.a*v13.c, v12.a*v13.b - v12.b*v13.a};
            A = n.a;
            B = n.b;
            C = n.c;
            D = -(A*p1.x + B*p1.y + C*p1.z);

            Vector v14{p4.x-p1.x, p4.y-p1.y, p4.z-p1.z};
            Vector n2{v12.b*v14.c - v12.c*v14.b, v12.c*v14.a - v12.a*v14.c, v12.a*v14.b - v12.b*v14.a};

            A2 = n2.a;
            B2 = n2.b;
            C2 = n2.c;
            D2 = -(A2*p1.x + B2*p1.y + C2*p1.z);

            double epsilon = 0.0001;
            double dA = double(A) / A2;
            double dB = double(B) / B2;
            double dC = double(C) / C2;
            double dD = double(D) / D2;

            double dd = 1;
            if (A==0 || A2==0) {
                dd = 2;
                if (A==0 && A2==0)
                    dA = 0;
                else
                    dA = 1234123513;
            }

            if (B==0 || B2==0) {
                if (dd==2)
                    dd = 3;
                if (B==0 && B2==0)
                    dB = 0;
                else
                    dB = 2136245643;
            }

            if (C==0 || C2==0) {
                if (dd==3)
                    dd = 4;
                if (C==0 && C2==0)
                    dC = 0;
                else
                    dC = 6587243254;
            }

            if (D==0 || D2==0) {
                if (D==0 && D2==0)
                    dD = 0;
                else
                    dD = 5673543456;
            }
            if (dd==1) dd = dA;
            else if (dd==2) dd = dB;
            else if (dd==3) dd = dC;
            else if (dd==4) dd = dD;

            if ((dB==0 || abs(dB-dd) < epsilon) && (dC==0 || abs(dC-dd) < epsilon) && (dD==0 || abs(dD-dd) < epsilon)) {
                cout << i << ", " << j << " tworza plaszczyzne" << endl;
                cout << dA << ", " << dB << ", " << dC << ", " << dD << endl;
                cout << A << ", " << B << ", " << C << ", " << D << endl;
                cout << A2 << ", " << B2 << ", " << C2 << ", " << D2 << endl;
            }
        }
    }

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
