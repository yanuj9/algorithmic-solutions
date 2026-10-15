#include <bits/stdc++.h>
using namespace std;

// // Optional: Policy-based DS (comment to disable)
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// template<typename T>
// using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


// // Optional: File I/O
// ifstream input_file("input.txt");
// ofstream output_file("output.txt");
// #define cin input_file
// #define cout output_file

// -------------------- Type Aliases --------------------
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;

// -------------------- Macros --------------------
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define endl '\n'
#define SUM(v) accumulate(all(v), 0LL)
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))

// -------------------- Constants --------------------
constexpr ll INF = 1e18;
constexpr ll MOD = 1e9 + 7;
constexpr int MAXN = 2e5 + 5;

// -------------------- Overloads --------------------
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (const auto& x : v) os << x << ' ';
    return os;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << '(' << p.ff << ", " << p.ss << ')';
}

template<typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
    for (auto& x : s) os << x << ' ';
    return os;
}

template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
    for (auto& [k, v] : m) os << '{' << k << ": " << v << "} ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
    for (const auto& row : v) {
        for (const auto& val : row) os << val << ' ';
        os << '\n';
    }
    return os;
}

template<typename T>
istream& operator>>(istream& is, vector<vector<T>>& v) {
    for (auto& row : v)
        for (auto& val : row)
            is >> val;
    return is;
}


// -------------------- Debug (Optional) --------------------
/*
#define dbg(x) cerr << #x << " = " << x << endl;
*/

// -------------------- Math Utilities --------------------
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll mod_add(ll a, ll b, ll m = MOD) { return (a + b) % m; }
ll mod_sub(ll a, ll b, ll m = MOD) { return (a - b + m) % m; }
ll mod_mul(ll a, ll b, ll m = MOD) { return (a * b) % m; }

ll mod_pow(ll base, ll exp, ll m = MOD) {
    ll res = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1) res = mod_mul(res, base, m);
        base = mod_mul(base, base, m);
        exp >>= 1;
    }
    return res;
}

ll mod_inv(ll a, ll m = MOD) {
    return mod_pow(a, m - 2, m); // Fermat (MOD must be prime)
}

// -------------------- Grid Directions --------------------
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
// or use: {{0,1},{1,0},{0,-1},{-1,0}} for 2D

// -------------------- Comparators --------------------
auto desc = [](auto a, auto b) { return a > b; };

// -------------------- Helper --------------------

// -------------------- Solver --------------------
void solve() {
    ll n; cin>>n;
    vector<vector<vector<ll>>> v(n, vector<vector<ll>>(n,vector<ll>(n,0))), pre(n, vector<vector<ll>>(n,vector<ll>(n,0)));
    for(ll i=0; i<n; ++i) {
        for(ll j=0; j<n; ++j) {
            for(ll k=0; k<n; ++k) {
                cin>>v[i][j][k];
            }
        }
    }
    pre = v;
    // for(ll z=0; z<n; ++z) {
    //     for(ll x=0; x<n; ++x) {
    //         for(ll y=0; y<n; ++y) {
    //             cout<<v[x][y][z]<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }
    for(ll z=0; z<n; ++z) {
        // process 2d array array
        for(ll i=1; i<n; ++i) pre[i][0][z] = pre[i-1][0][z] + v[i][0][z];
        for(ll i=1; i<n; ++i) pre[0][i][z] = pre[0][i-1][z] + v[0][i][z];
        for(ll i=1; i<n; ++i) {
            for(ll j=1; j<n; ++j) {
                pre[i][j][z] = pre[i-1][j][z] + pre[i][j-1][z] + v[i][j][z] - pre[i-1][j-1][z];
            }
        }
    }
    // for(ll z=0; z<n; ++z) {
    //     for(ll x=0; x<n; ++x) {
    //         for(ll y=0; y<n; ++y) {
    //             cout<<pre[x][y][z]<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }
    for(ll z=1; z<n; ++z) {
        // get sum in z - axis
        for(ll x=0; x<n; ++x) {
            for(ll y=0; y<n; ++y) {
                pre[x][y][z] += pre[x][y][z-1];
            }
        }
    }

    // for(ll z=0; z<n; ++z) {
    //     for(ll x=0; x<n; ++x) {
    //         for(ll y=0; y<n; ++y) {
    //             cout<<pre[x][y][z]<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }

    // process q queries
    ll q; cin>>q;
    while(q--) {
        ll lx, rx, ly, ry, lz, rz; cin>>lx>>rx>>ly>>ry>>lz>>rz;
        --lx; --ly; --lz; --rx; --ry; --rz;
        ll ans = pre[rx][ry][rz];
        
        // remove by one one surface each
        ans -= (lx - 1 >= 0 ? pre[lx - 1][ry][rz] : 0);
        ans -= (ly - 1 >= 0 ? pre[rx][ly - 1][rz] : 0);
        ans -= (lz - 1 >= 0 ? pre[rx][ry][lz - 1] : 0);
    
        // add once common volume by two surfaces as removed twice
        ans += ((lz - 1 >= 0 && ly - 1 >= 0) ? pre[rx][ly - 1][lz - 1] : 0);
        ans += ((lz - 1 >= 0 && lx - 1 >= 0) ? pre[lx - 1][ry][lz - 1] : 0);
        ans += ((lx - 1 >= 0 && ly - 1 >= 0) ? pre[lx - 1][ly - 1][rz] : 0);

        // substract thrice added area, as to remove the common area of all
        ans -= ((ly - 1 >= 0 && lx - 1 >= 0 && lz - 1 >= 0) ? (pre[lx - 1][ly - 1][lz - 1]) : 0);

        cout<<ans<<endl;
    }
}

// -------------------- Main --------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}