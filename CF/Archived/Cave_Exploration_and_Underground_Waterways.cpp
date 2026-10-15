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

// -------------------- Solver --------------------
void solve() {
    ll h,w; cin>>h>>w;
    vector<string> ip(h); cin>>ip;
    ll sr,sc,gr,gc;
    for(ll i=0; i<h; ++i) {
        for(ll j=0; j<w; ++j) {
            if(ip[i][j] == 'S') {
                sr = i;
                sc = j;
            }
            if(ip[i][j] == 'G') {
                gr = i;
                gc = j;
            }
        }
    }
    vector<vll> component_id(h,vll(w,-1));
    vector<vector<pll>> componentCells;
    ll totalComponents = 0;

    for(ll i=0; i<h; ++i) {
        for(ll j=0; j<w; ++j) {
            if(ip[i][j] == 'V' && component_id[i][j] == -1) {
                queue<pll> q;
                q.push({i,j});
                component_id[i][j] = totalComponents;

                vector<pll> currcells;

                while(!q.empty()) {
                    auto [r,c] = q.front(); q.pop();
                    currcells.push_back({r,c});

                    for(ll d=0; d<4; ++d) {
                        ll nr = r + dx[d], nc = c + dy[d];
                        if(nr >= 0 && nr < h && nc >= 0 && nc < w) {
                            if(component_id[nr][nc] == -1 && ip[nr][nc] == 'V') {
                                q.push({nr,nc});
                                component_id[nr][nc] = totalComponents;
                            }
                        }
                    }
                }

                componentCells.push_back(currcells);
                totalComponents++;
            }
        }
    }

    vector<vll> dis(h,vll(w,INF));
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
    vector<bool> componentVisited(totalComponents, false);

    dis[sr][sc] = 0;
    pq.push({0,sr,sc});

    while(!pq.empty()) {
        auto [d,r,c] = pq.top(); pq.pop();

        if(d > dis[r][c]) continue;

        if(r == gr && c == gc) {
            cout<<d;
            return;
        }

        if(ip[r][c] == 'V') {
            ll id = component_id[r][c];
            if(!componentVisited[id]) {
                componentVisited[id] = true;
                for(auto& cell:componentCells[id]) {
                    ll nr = cell.ff, nc = cell.ss;
                    if(dis[nr][nc] > d) {
                        dis[nr][nc] = d;
                        pq.push({d,nr,nc});
                    }
                }
            }
        }

        for(ll dir=0; dir<4; ++dir) {
            ll nr = r + dx[dir];
            ll nc = c + dy[dir];
            if(nr >= 0 && nr < h && nc >= 0 && nc < w && ip[nr][nc] != 'X') {
                ll wt = ip[nr][nc] == 'V' ? 2 : 1;
                if(d + wt < dis[nr][nc]) {
                    dis[nr][nc] = d + wt;
                    pq.push({dis[nr][nc], nr, nc});
                }
            }
        }
    }

    cout<<"NO\n";
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