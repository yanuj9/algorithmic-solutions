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
constexpr ll MOD = 998244353;
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

struct Node {
    ll sum = 0, ans = 0;
};

struct LazySegmentTree {
    int n;
    vector<Node> tree;
    vll lazy;

    LazySegmentTree(int n) : n(n) {
        tree.assign(4 * n, {0, 0});
        lazy.assign(4 * n, 0);
    }

    Node merge_nodes(const Node& left, const Node& right) {
        Node res;
        res.sum = (left.sum + right.sum) % MOD;
        
        ll cross_product = (left.sum * right.sum) % MOD;
        res.ans = (left.ans + right.ans + cross_product) % MOD;
        
        return res;
    }

    void apply(int node, int L, int R, ll val) {
        ll len = R - L + 1;
        val %= MOD;

        ll pairs = (len * (len - 1) / 2) % MOD;

        ll term1 = tree[node].ans;
        ll term2 = (val * tree[node].sum % MOD) * (len - 1) % MOD;
        ll term3 = (val * val % MOD) * pairs % MOD;
        tree[node].ans = (term1 + term2 + term3) % MOD;

        tree[node].sum = (tree[node].sum + len * val % MOD) % MOD;

        lazy[node] = (lazy[node] + val) % MOD;
    }

    void push(int node, int L, int R) {
        if (lazy[node] != 0) {
            if (L != R) {
                int mid = L + (R - L) / 2;
                apply(2 * node, L, mid, lazy[node]);
                apply(2 * node + 1, mid + 1, R, lazy[node]);
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int L, int R, int qL, int qR, ll val) {
        if (qL <= L && R <= qR) {
            apply(node, L, R, val);
            return;
        }
        push(node, L, R);
        int mid = L + (R - L) / 2;
        if (qL <= mid) update(2 * node, L, mid, qL, qR, val);
        if (qR > mid)  update(2 * node + 1, mid + 1, R, qL, qR, val);
        
        tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int L, int R, int qL, int qR) {
        if (qL <= L && R <= qR) {
            return tree[node];
        }
        push(node, L, R);
        int mid = L + (R - L) / 2;
        
        if (qR <= mid) return query(2 * node, L, mid, qL, qR);
        if (qL > mid)  return query(2 * node + 1, mid + 1, R, qL, qR);
        
        return merge_nodes(
            query(2 * node, L, mid, qL, qR),
            query(2 * node + 1, mid + 1, R, qL, qR)
        );
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n,q; cin>>n>>q;
    LazySegmentTree lst(n);
    while(q--) {
        ll l,r,v; cin>>l>>r>>v;
        --l; --r;
        lst.update(1,0,n-1,l,r,v);
        cout<<lst.query(1,0,n-1,l,r).ans<<endl;
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