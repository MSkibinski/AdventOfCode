#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<string> t;
    string line;
    while (cin >> line)
        t.push_back(line);

    int bestScenicScore = 0;
    for (int i=1; i<t.size()-1; i++)
    for (int j=1; j<t[0].size()-1; j++) {
        int h = t[i][j];
        int up=1, down=1, left=1, right=1;
        for (int jj=j-1; jj>0; jj--, left++)
            if (t[i][jj] >= h)
                break;
        for (int jj=j+1; jj<t[0].size()-1; jj++, right++)
            if (t[i][jj] >= h)
                break;
        for (int ii=i-1; ii>0; ii--, up++)
            if (t[ii][j] >= h)
                break;
        for (int ii=i+1; ii<t.size()-1; ii++, down++)
            if (t[ii][j] >= h)
                break;

        bestScenicScore = max(bestScenicScore, up*down*left*right);
    }

    cout << bestScenicScore << endl;
}
