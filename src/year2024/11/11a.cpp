
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<long long> stones;
    
    int n;   
    while (cin >> n) {
        stones.push_back(n);
    }
    
    long long max_stone = 0;
    for (int i=0; i<25; i++) {
        vector<long long> newStones;
        newStones.reserve(stones.size()*2);
        
        for (auto stone : stones) {
            if (stone == 0) newStones.push_back(1);
            else {
                string stoneString = to_string(stone);
                if (stoneString.size() % 2 == 0) {
                    newStones.push_back(stoll(stoneString.substr(0, stoneString.size()/2)));
                    newStones.push_back(stoll(stoneString.substr(stoneString.size()/2)));
                }
                else {
                    newStones.push_back(stone*2024);
                    max_stone = max(max_stone, stone*2024);
                }
            }
        }
        stones = newStones;
    }
    
    cout << max_stone << endl;
    std::cout << stones.size();

    return 0;
}