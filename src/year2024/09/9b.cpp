
#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<set<int>> freeSpace(10);

pair<int, int> getFirstFree(int size) {
    int position = 100000000;
    int spaceSize = 10;
    for (int i=size; i<10; i++) {
        int freeSpacePosition = *freeSpace[i].begin();
        if (freeSpacePosition < position) {
            position = freeSpacePosition;
            spaceSize = i;
        }
    }
    
    return {position, spaceSize};
}


int main()
{
    string diskMap;
    cin >> diskMap;
    
    vector<pair<int, int>> fileSizes;
    
    int diskPosition = 0;
    for (int i=0; i<diskMap.size(); i++) {
        int value = diskMap[i] - '0';
        if (i%2 == 0) {
            fileSizes.push_back({value, diskPosition});
        }
        else {
            freeSpace[value].insert(diskPosition);
        }
        diskPosition += value;
    }
    for (auto &frSpace : freeSpace) {
        frSpace.insert(diskPosition);
    }
    
    long long sum = 0;
    for (long long fileId = fileSizes.size()-1; fileId > 0; fileId--) {
        auto [fileSize, filePosition] = fileSizes[fileId];
        auto [freeSpacePosition, freeSpaceSize] = getFirstFree(fileSize);
        if (freeSpacePosition < filePosition) {
            filePosition = freeSpacePosition;
            freeSpace[freeSpaceSize].erase(freeSpace[freeSpaceSize].begin());
            
            int spaceLeft = freeSpaceSize - fileSize;
            if (spaceLeft) {
                freeSpace[spaceLeft].insert(freeSpacePosition + fileSize);
            }
        }
        //cout << fileId << " " << filePosition << endl;
        sum += ((2*filePosition + fileSize - 1) * fileSize / 2) * fileId;
    }
    
    std::cout << sum;

    return 0;
}