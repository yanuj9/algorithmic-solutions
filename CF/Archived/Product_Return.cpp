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

struct Product {
    ll a,b,id;
};

struct Query {
    ll k,id;
};

struct DSU {
    vector<long long> p, max_weight;
    ll total_cost = 0;
    DSU(long long n) {
        p.resize(n + 2);
        max_weight.resize(n + 2);
        total_cost = 0;
        iota(p.begin(), p.end(), 0);
    }
    long long find(long long x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void activate(ll i, ll w) {
        max_weight[i] = w;
        total_cost += w;
    }
    bool unite(long long a, long long b) {
        a = find(a); b = find(b);
        if(a == b) return false;
        total_cost -= max_weight[a];
        total_cost -= max_weight[b];

        p[a] = b;
        max_weight[b] = max(max_weight[a], max_weight[b]);

        total_cost += max_weight[b];
        return true;
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n,q; cin>>n>>q;
    vector<Product> products(n);
    for(ll i=0; i<n; ++i) {
        cin>>products[i].a>>products[i].b;
        products[i].id = i + 1;
    }
    vector<Query> queries(q);
    for(ll i=0; i<q; ++i) {
        cin>>queries[i].k;
        queries[i].id = i;
    }

    sort(all(products), [](Product& a, Product& b) {
        return a.a < b.a;
    });

    sort(all(queries), [](Query& a, Query& b){
        return a.k < b.k;
    });

    DSU dsu(n);
    vector<bool> active(n+2, false);
    vll ans(q);

    ll ptr = 0;

    for(ll i=0; i<q; ++i) {
        ll currk = queries[i].k;

        while(ptr < n && products[ptr].a < currk) {
            ll currid = products[ptr].id;
            ll currwt = products[ptr].b;

            dsu.activate(currid, currwt);
            active[currid] = true;

            if(active[currid - 1]) {
                dsu.unite(currid, currid - 1);
            }
            if(active[currid + 1]) {
                dsu.unite(currid, currid + 1);
            }
            ptr++;
        }

        ans[queries[i].id] = dsu.total_cost;
    }

    for(ll i=0; i<q; ++i) cout<<ans[i]<<endl;
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