#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define all(x) x.begin(), x.end()

class Solution {
public:
    string solve(string s) {
        int n = s.size() - 1;
        set<char> st({'a', 'e', 'i', 'o', 'u'});
        while(n >= 0 && st.count(s[n])) --n;
        return n == 0 ? "" : s.substr(0,n+1);
    }
};

#ifndef ONLINE_JUDGE
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    Solution sol;
    while (T--) {
        string s; cin>>s;
        cout << sol.solve(s) << "\n";
    }

    return 0;
}
#endif