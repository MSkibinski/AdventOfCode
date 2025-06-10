#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string line, tmp;
vector<unsigned int> seeds;

void mapping(){
    vector<unsigned int> result = seeds;
    getline(cin, line);

    getline(cin, line);
    while (line.size()) {
        istringstream iss(line);
        unsigned int destination, source, range;
        iss >> destination >> source >> range;

        for (int i=0; i<seeds.size(); i++) {
            if (seeds[i] >= source && seeds[i] < source + range)
                result[i] = destination + (seeds[i]-source);
        }

        getline(cin, line);
    }
    seeds = result;
    // for (auto &value : seeds) {
    //     cout << value << endl;
    // }
    // cout << endl;
}

int main() {
    
    getline(cin, line);

    istringstream iss(line);
    iss >> tmp;
    
    unsigned int x;
    while (iss >> x)
        seeds.push_back(x);
    getline(cin, line);

    for (int i=0; i<7; i++)
        mapping();

    cout << *min_element(seeds.begin(), seeds.end()) << endl;
}