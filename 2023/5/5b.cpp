#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string line, tmp;



struct Range {
    unsigned int start;
    unsigned int end;

    bool operator<(const Range &r2) const {
        return start<r2.start;
    }
};

struct Mapping {
    unsigned int sourceStart;
    unsigned int sourceEnd;
    unsigned int destination;

    bool operator<(const Mapping &r2) const {
        return sourceStart<r2.sourceStart;
    }
};

vector<Range> seeds;

void mapping(){
    vector<Range> result;
    getline(cin, line);

    getline(cin, line);
    vector<Mapping> map_values;
    while (line.size()) {
        istringstream iss(line);
        unsigned int destination, source, range;
        iss >> destination >> source >> range;

        map_values.push_back({source, source+range-1, destination});

        getline(cin, line);
    }
    sort (map_values.begin(), map_values.end());

    for (int i=0, j=0; i<seeds.size();) {
        if (j >= map_values.size()) {
            while (i<seeds.size()) {
                result.push_back(seeds[i]);
                i++;
            }
        }
        else if (seeds[i].start <= map_values[j].sourceStart) {
            if (seeds[i].end < map_values[j].sourceStart) {
                result.push_back(seeds[i]);
                i++;
            }
            else {
                if (seeds[i].start < map_values[j].sourceStart) {
                    result.push_back({seeds[i].start, map_values[j].sourceStart-1});
                }
                if (seeds[i].end <= map_values[j].sourceEnd) {
                    unsigned int length = seeds[i].end - map_values[j].sourceStart;
                    result.push_back({map_values[j].destination, map_values[j].destination+length});
                    i++;
                }
                else {
                    result.push_back({map_values[j].destination, map_values[j].sourceEnd-map_values[j].sourceStart+map_values[j].destination});
                    seeds[i].start = map_values[j].sourceEnd+1;
                    j++;
                }
            }
        }
        else if (seeds[i].start > map_values[j].sourceEnd) {
            j++;
        }
        else {
            unsigned int diff = seeds[i].start-map_values[j].sourceStart;
            map_values[j].sourceStart += diff;
            map_values[j].destination += diff;
        }
    }

    sort(result.begin(), result.end());

    seeds = result;
    for (auto s : seeds) {
        cout << s.start << "-" << s.end << endl;
    }
    cout << endl;
}

int main() {
    
    getline(cin, line);

    istringstream iss(line);
    iss >> tmp;
    
    unsigned int s, len;
    while (iss >> s >> len)
        seeds.push_back({s, s+len-1});
    getline(cin, line);

    sort(seeds.begin(), seeds.end());

    for (auto s : seeds) {
        cout << s.start << "-" << s.end << endl;
    }
    cout << endl;
    
    for (int i=0; i<7; i++)
        mapping();

    cout << seeds[0].start << endl;
}