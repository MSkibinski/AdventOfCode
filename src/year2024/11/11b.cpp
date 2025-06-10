
#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<long long, long long> stones;
    
    int n;   
    while (cin >> n) {
        stones[n] = 1;
    }
    
    long long max_stone = 0;
    for (int i=0; i<75; i++) {
        cout << i << " " << stones.size() << endl;
        map<long long, long long> newStones;
        
        for (auto [stoneValue, count] : stones) {
            if (stoneValue == 0) newStones[1] += count;
            else {
                string stoneString = to_string(stoneValue);
                if (stoneString.size() % 2 == 0) {
                    newStones[stoll(stoneString.substr(0, stoneString.size()/2))] += count;
                    newStones[stoll(stoneString.substr(stoneString.size()/2))] += count;
                }
                else {
                    newStones[stoneValue*2024] += count;
                    max_stone = max(max_stone, stoneValue*2024);
                }
            }
        }
        stones = newStones;
    }
    
    long long sum=0;
    for (auto [stoneValue, count] : stones) {
        sum += count;
    }
    
    cout << max_stone << endl;
    std::cout << sum;

    return 0;
}