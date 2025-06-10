#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std;

unordered_map<string, int> history;

class Reflector {
    vector<string> v;

    
    void tiltWest() {
        for (auto &line : v) {
            int r = 0;
            for (int i=v[0].size()-1; i>=0; i--) {
                if (line[i]=='O') {
                    line[i] = '.';
                    r++;
                }
                else if (line[i]=='#' && r) {
                    for (int k=i+1; r; k++, r--)
                        line[k] = 'O';
                }
            }
            for (int k=0; r; k++, r--)
                line[k] = 'O';
        }
    }
    void tiltSouth() {
        int len = v[0].size();
        vector<int> r(len);
        for (int i=0; i<v.size(); i++) {
            for (int j=0; j<len; j++) {
                if (v[i][j]=='O') {
                    v[i][j] = '.';
                    r[j]++;
                }
                else if (v[i][j]=='#' && r[j]) {
                    for (int k=i-1; r[j]; k--, r[j]--)
                        v[k][j] = 'O';
                }
            }
        }
        for (int j=0; j<len; j++)
            for (int k=v.size()-1; r[j]; k--, r[j]--)
                v[k][j] = 'O';

    }
    void tiltEast() {
        for (auto &line : v) {
            int r = 0;
            for (int i=0; i<v[0].size(); i++) {
                if (line[i]=='O') {
                    line[i] = '.';
                    r++;
                }
                else if (line[i]=='#' && r) {
                    for (int k=i-1; r; k--, r--)
                        line[k] = 'O';
                }
            }
            for (int k=line.size()-1; r; k--, r--)
                line[k] = 'O';
        }
    }

public:
    void read() {
        string line;
        while (cin >> line)
            v.push_back(line);
    }

    void tiltNorth() {
        int len = v[0].size();
        vector<int> r(len);
        for (int i=v.size()-1; i>=0; i--) {
            for (int j=0; j<len; j++) {
                if (v[i][j]=='O') {
                    v[i][j] = '.';
                    r[j]++;
                }
                else if (v[i][j]=='#' && r[j]) {
                    for (int k=i+1; r[j]; k++, r[j]--)
                        v[k][j] = 'O';
                }
            }
        }
        for (int j=0; j<len; j++)
            for (int k=0; r[j]; k++, r[j]--)
                v[k][j] = 'O';
    }

    void spin() {
        tiltNorth();
        tiltWest();
        tiltSouth();
        tiltEast();
    }

    int countLoad() {
        int result = 0;
        int len = v[0].size();
        
        for (int row=v.size(), i=0; i<v.size(); row--, i++)
            for (int j=0; j<len; j++)
                result += v[i][j]=='O' ? row : 0;

        return result;
    }

    void print() {
        for (const auto &line : v)
            cout << line << endl;
        cout << endl;
    }

    string getString() {
        string result;
        result.reserve(v.size() * v[0].size());
        for (const auto &line : v)
            result += line;
        return result;
    }
};

int main()
{
    Reflector reflector;
    reflector.read();
    reflector.tiltNorth();

    cout << reflector.countLoad() << endl;
}
