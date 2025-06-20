#include <bits/stdc++.h>


using namespace std;

/*
 SampleInput
2112112112
2212112
12121212
21212121
2211221122
21212
 SampleOutput
 10
 8
 15
*/

int main() {
    vector<int> a(100, 0), b(100, 0);
    string sa, sb;
    int aLen, bLen, sumLen;
    int ans;
    bool flag;

    while (1) {
        cin >> sa >> sb;
        aLen = sa.size();
        bLen = sb.size();
        for (int i = 0; i < aLen; ++i) {
            a[i] = sa[i];
        }
        for (int i = 0; i < bLen; ++i) {
            b[i] = sb[i];
        }
        
        sumLen = aLen + bLen;
        ans = aLen + bLen;

        for (int i = 0; i < aLen; ++i) {
            flag = true;
            for (int j = 0; j < i; ++j) {
                if (a[aLen - j] + b[j] > 3) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ans = min(ans, sumLen - i-1);
            }
        }
        
        cout << ans << endl;
    }

    return 0;
}