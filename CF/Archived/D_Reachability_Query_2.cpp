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

void dfs1(int u, vll& vis, vll& order, vector<vll>& g){
    vis[u]=1;
    for(int v:g[u])
        if(!vis[v]) dfs1(v,vis, order,g);
    order.push_back(u);
}

void dfs2(int u, vll& comp,ll cid, vector<vll>& rg){
    comp[u]=cid;
    for(int v:rg[u])
        if(comp[v]==-1) dfs2(v,comp,cid,rg);
}

// -------------------- Solver --------------------
void solve() {
    ll n,m; cin>>n>>m;
    vector<vll> g(n+1), rev(n + 1);
    for (ll i=0; i<m; ++i) {
        ll x,y; cin>>x>>y;
        g[x].push_back(y);
        rev[y].push_back(x);
    }

    ll nq; cin>>nq;
    vector<pair<int,int>> queries(nq);
    for (ll i=0; i<nq; ++i) {
        cin>>queries[i].ff>>queries[i].ss;
    }

    vll order, vis(n+1,0);

    for(ll i=1; i<=n; ++i) {
        if(!vis[i]) dfs1(i,vis,order,g);
    }

    vll comp(n+1,-1);
    ll cid=0;
    reverse(all(order));
    for(auto u:order){
        if(comp[u] == -1){
            dfs2(u, comp, cid, rev);
            cid++;
        }
    }

    int C = cid;

    vector<vll> dag_rev(C);
    for(ll u=1; u<=n; ++u){
        for(auto v:g[u]){
            if(comp[u] != comp[v]){
                dag_rev[comp[v]].push_back(comp[u]);
            }
        }
    }

    vector<bool> good(C,false);
    queue<int> bfs;
    vector<string> ans;

    for(auto &qr:queries) {
        int type = qr.ff;
        int v = qr.ss;
        int c = comp[v];

        if(type == 1) {
            if(!good[c]) {
                good[c] = true;
                bfs.push(c);

                while(!bfs.empty()) {
                    int u = bfs.front(); bfs.pop();
                    for(auto p:dag_rev[u]) {
                        if(!good[p]) {
                            good[p] = true;
                            bfs.push(p);
                        }
                    }
                }
            }
        }
        else{
            ans.push_back(good[c] ? "Yes" : "No");
        }
    }

    for (auto& x : ans) {
        cout<<x<<endl;
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