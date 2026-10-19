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
using ull = unsigned long long;
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
vll primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
// or use: {{0,1},{1,0},{0,-1},{-1,0}} for 2D

// -------------------- Comparators --------------------
auto desc = [](auto a, auto b) { return a > b; };

// -------------------- Helper --------------------

struct SegmentTree {
    int n;
    vector<pii> tree;

    SegmentTree(int n) : n(n), tree(4*n + 5) {
        build(1, 1, n);
    }

    pii combine(pair<int, int> left, pair<int, int> right) {
        if (left.ff <= right.ff) return left;
        return right;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = {0, tl};
        } else {
            int tm = tl + (tr - tl) / 2;
            build(2 * v, tl, tm);
            build(2 * v + 1, tm + 1, tr);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            tree[v].ff++;
        } else {
            int tm = tl + (tr - tl) / 2;
            if (pos <= tm) update(2 * v, tl, tm, pos);
            else update(2 * v + 1, tm + 1, tr, pos);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }

    pii query(int v, int tl, int tr, int l, int r) {
        if (l > r) return {1e9, 1e9};
        if (l == tl && r == tr) return tree[v];
        int tm = tl + (tr - tl) / 2;
        return combine(
            query(2 * v, tl, tm, l, min(r, tm)),
            query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r)
        );
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n,m,t; cin>>n>>m>>t;
    vll brightness(n+1, 0);

    SegmentTree st(n);

    for(ll i=0; i<m; ++i) {
        ll s,l,r; cin>>s>>l>>r;

        auto best_seat = st.query(1, 1, n, l, r);
        int idx = best_seat.ss;

        st.update(1, 1, n, idx);

        ll light = max(0LL, 100LL - (t - s));
        brightness[idx] += light;
    }
    for(ll i=1; i<=n; ++i) cout<<brightness[i]<<" ";
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