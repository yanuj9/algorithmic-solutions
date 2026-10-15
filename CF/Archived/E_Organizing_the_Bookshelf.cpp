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

// 1/b % MOD
ll mod_inv(ll b, ll m = MOD) {
    return mod_pow(b, m - 2, m); // Fermat (MOD must be prime)
}

// -------------------- Grid Directions --------------------
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
// or use: {{0,1},{1,0},{0,-1},{-1,0}} for 2D

// -------------------- Comparators --------------------
auto desc = [](auto a, auto b) { return a > b; };

// -------------------- Helper --------------------

ll merge(ll l, ll m, ll r, vll& v) {
    ll n1 = m - l + 1, n2 = r - m;
    vll v1(n1), v2(n2);
    for(ll i=0; i<n1; ++i) v1[i] = v[i+l];
    for(ll i=0; i<n2; ++i) v2[i] = v[i + 1 + m];

    ll invCount = 0;
    ll i=0, j=0, k=l;
    while(i < n1 && j < n2) {
        if(v1[i] <= v2[j]) {
            v[k++] = v1[i++];
        }
        else {
            v[k++] = v2[j++];
            invCount += n1 - i;
        }
    }
    while(i < n1) v[k++] = v1[i++];
    while(j < n2) v[k++] = v2[j++];
    
    return invCount;
}

ll countInversions(ll l, ll r, vll& v) {
    if(l >= r) return 0;
    ll ans = 0;
    ll mid = l + (r - l) / 2;
    ans += countInversions(l,mid,v);
    ans += countInversions(mid + 1, r, v);
    ans += merge(l,mid,r,v);
    return ans;
}

struct BIT {
    // Initialization with 1 extra node and functions based 1 based indexing
    int n;
    vector<long long> bit;

    BIT(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int i, long long val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n; cin>>n;
    vll v(n); cin>>v;
    BIT bit(n+5);
    ll ans = 0;
    for(ll i=0; i<n; ++i) {
        ans += bit.query(v[i], n);
        bit.update(v[i],1);
    }
    cout<<ans;
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