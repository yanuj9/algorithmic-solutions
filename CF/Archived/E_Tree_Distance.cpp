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

// -------------------- DSU --------------------
struct DSU {
    vll p, sz;
    DSU(ll n) {
        p.resize(n);
        sz.assign(n,1);
        iota(all(p), 0);
    }
    ll find(ll x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(ll a, ll b) {
        a = find(a); b = find(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n; cin>>n;
    vector<vll> v(n,vll(n,0));
    for(ll i=0; i<n; ++i) {
        for(ll j=i+1; j<n; ++j) {
            cin>>v[i][j];
            v[j][i] = v[i][j];
        }
    }
    for(ll i=0; i<n; ++i) {
        if(v[i][i] != 0) {
            cout<<"No";
            return;
        }
        for(ll j=0; j<n; ++j) {
            if(i != j && v[i][j] == 0) {
                cout<<"No";
                return;
            }
        }
    }

    vector<tuple<ll,ll,ll>> edges;
    for(ll i = 0; i < n; ++i) {
        for(ll j = i+1; j < n; ++j) {
            edges.eb(v[i][j], i, j);
        }
    }

    sort(all(edges));

    DSU dsu(n);
    vector<vector<pair<ll,ll>>> adj(n);

    for(auto &[w,u,vv] : edges) {
        if(dsu.unite(u, vv)) {
            adj[u].pb({vv, w});
            adj[vv].pb({u, w});
        }
    }

    for(ll src = 0; src < n; ++src) {
        vll dist(n, -1);
        queue<ll> q;

        dist[src] = 0;
        q.push(src);

        while(!q.empty()) {
            ll u = q.front(); q.pop();
            for(auto &[to, w] : adj[u]) {
                if(dist[to] == -1) {
                    dist[to] = dist[u] + w;
                    q.push(to);
                }
            }
        }

        for(ll i = 0; i < n; ++i) {
            if(dist[i] != v[src][i]) {
                cout << "No";
                return;
            }
        }
    }
    cout<<"Yes";
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