#include <bits/stdc++.h>


using namespace std;

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
        
        sumLen = ans = aLen + bLen;

        for (int i = 0; i < aLen; ++i) {
            flag = true;
            for (int j = 0; j < i; ++j) {
                if (a[i - j] + b[j] > 3) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ans = min(ans, sumLen - i);
            }
        }
        
        cout << ans << endl;
    }

    return 0;
}