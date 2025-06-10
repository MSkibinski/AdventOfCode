
#include <iostream>

using namespace std;

int main()
{
    string diskMap;
    cin >> diskMap;
    
    long long sum = 0;
    for (long long frontPosition=0, endPosition=diskMap.size()-1, diskPosition=0; frontPosition <= endPosition; ) {
        if (frontPosition%2 == 0) {
            int fileId = frontPosition/2;
            int length = diskMap[frontPosition] - '0';
            sum += ((2*diskPosition + length - 1) * length / 2) * fileId;
            
            diskPosition += length;
            frontPosition++;
        }
        else {
            int fileId = endPosition/2;
            int freeSpace = diskMap[frontPosition] - '0';
            int fileSize = diskMap[endPosition] - '0';
            int length = min(freeSpace, fileSize);
            
            sum += ((2*diskPosition + length - 1) * length / 2) * fileId;
            diskPosition += length;
            
            if (freeSpace == length) {
                frontPosition++;
            }
            else {
                diskMap[frontPosition] -= length;
            }
            
            if (fileSize == length) {
                endPosition -= 2;
            }
            else {
                diskMap[endPosition] -= length;
            }
        }
    }
    
    std::cout << sum;

    return 0;
}