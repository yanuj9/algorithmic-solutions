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

struct LazySegmentTree {
    int n;
    vector<long long> tree, lazy;

    // Initialization: Pass a 0-indexed vector. Tree size is 4*n.
    LazySegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    // Build: node=1, range=[0, n-1]
    void build(int node, int L, int R, const vector<long long>& arr) {
        if (L == R) {
            tree[node] = arr[L];
            return;
        }
        int mid = (L + R) / 2;
        build(2 * node, L, mid, arr);
        build(2 * node + 1, mid + 1, R, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Push: Propagates pending updates to children
    void push(int node, int L, int R) {
        if (lazy[node] != 0) {
            tree[node] += (long long)(R - L + 1) * lazy[node];
            if (L != R) { // If not leaf, pass lazy value to children
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Clear the pending work
        }
    }

    // Update: Adds 'val' to range [qL, qR] (0-based inclusive)
    void update(int node, int L, int R, int qL, int qR, long long val) {
        push(node, L, R);
        if (qL > R || qR < L) return; // Out of range
        if (qL <= L && R <= qR) {     // Fully inside
            lazy[node] += val;
            push(node, L, R);
            return;
        }
        int mid = (L + R) / 2;
        update(2 * node, L, mid, qL, qR, val);
        update(2 * node + 1, mid + 1, R, qL, qR, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Query: Gets range sum of [qL, qR] (0-based inclusive)
    long long query(int node, int L, int R, int qL, int qR) {
        push(node, L, R);
        if (qL > R || qR < L) return 0;
        if (qL <= L && R <= qR) return tree[node];
        int mid = (L + R) / 2;
        return query(2 * node, L, mid, qL, qR) + query(2 * node + 1, mid + 1, R, qL, qR);
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n,m; cin>>n>>m;
    vll g(m), t(n+1); cin>>g;
    LazySegmentTree lst(t);
    ll ans = 0;
    for(ll i=m-1; i>=0; --i) {
        ll countAllLess = lst.query(1,0,n,0,g[i] - 1);
        ans += countAllLess;
        lst.update(1, 0, n, g[i], g[i], 1);
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