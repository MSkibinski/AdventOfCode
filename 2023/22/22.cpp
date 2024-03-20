#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <memory>

#include <complex>

using namespace std;

struct Coord {
    unsigned int x;
    unsigned int y;
    unsigned int z;
};

std::istream& operator>>(std::istream& is, Coord& coord) {
    char c;
    is >> coord.x >> c >> coord.y >> c >> coord.z;
    return is;
}

struct Brick {
    Coord a, b;
    set<Brick*> below;
    set<Brick*> up;
    
    bool operator<(const Brick &b) const {
        if (a.z != b.a.z) {
            return a.z < b.a.z;
        }
        else {
            return a.x < b.a.x;
        }
    }

    bool canBeDisintegrated() {
        // cout << "upSize: " << up.size() << endl;
        for (auto &brickUp : up) {
            if (brickUp->below.size()==1)
                return false;
        }
        return true;
    }
};

std::istream& operator>>(std::istream& is, Brick& b) {
    char c;
    is >> b.a >> c >> b.b;

    if (b.a.z > b.b.z) {
        cout << "Z odwrotnie" << endl;
        swap(b.a, b.b);
    }

    return is;
}

int main() {
    vector<Brick> bricks;
    Brick b;
    unsigned int maxX = 0;
    unsigned int maxY = 0;
    while (cin >> b) {
        bricks.push_back(b);
        maxX = max(maxX, max(b.a.x, b.b.x));
        maxY = max(maxY, max(b.a.y, b.b.y));
    }

    sort(bricks.begin(), bricks.end());

    vector<vector<Brick*>> v{maxX+1, vector<Brick*>{maxY+1, nullptr}};
    for (auto &brick : bricks) {
        unsigned int maxZ = 0;
        for (int i=brick.a.x; i<=brick.b.x; i++) {
            for (int j=brick.a.y; j<=brick.b.y; j++) {
                if (v[i][j] != nullptr) {
                    maxZ = max(maxZ, v[i][j]->b.z);
                }
            }
        }
        int dropBy = brick.a.z - maxZ - 1;
        // cout << "dropBy: " << dropBy << endl;
        brick.a.z -= dropBy;
        brick.b.z -= dropBy;
        for (int i=brick.a.x; i<=brick.b.x; i++) {
            for (int j=brick.a.y; j<=brick.b.y; j++) {
                if (v[i][j] != nullptr) {
                    if (v[i][j]->b.z == brick.a.z-1) {
                        brick.below.insert(v[i][j]);
                        v[i][j]->up.insert(&brick);
                    }
                }
                v[i][j] = &brick;
            }
        }
    }

    int result = 0;
    for (auto &brick : bricks) {
        if(brick.canBeDisintegrated()) {
            result++;
        }
    }
    cout << result << endl;
}
