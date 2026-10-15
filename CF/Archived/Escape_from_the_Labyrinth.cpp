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
const int dx[5] = {-1, 1, 0, 0, 0};
const int dy[5] = {0, 0, -1, 1, 0};
vll primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
// or use: {{0,1},{1,0},{0,-1},{-1,0}} for 2D

// -------------------- Comparators --------------------
auto desc = [](auto a, auto b) { return a > b; };

// -------------------- Helper --------------------

struct State {
    int tr, tc;
    int gr1, gc1;
    int gr2, gc2;
};

int dist[9][9][9][9][9][9];

pii get_next_guard_pos(int gr, int gc, int tr, int tc, int N, int M, const vector<string>& grid) {
    int min_dist = 1e9;
    int best_r = gr, best_c = gc;

    for(int i = 0; i < 5; ++i) {
        int nr = gr + dx[i];
        int nc = gc + dy[i];

        if(nr >= 1 && nr <= N && nc >= 1 && nc <= M && grid[nr - 1][nc - 1] == '.') {
            int d = abs(nr - tr) + abs(nc - tc);

            if (d < min_dist) {
                min_dist = d;
                best_r = nr;
                best_c = nc;
            }
        }
    }
    return {best_r, best_c};
}

// -------------------- Solver --------------------
void solve() {
    ll n,m,k; cin>>n>>m>>k;
    int Sr,Sc,Gr,Gc; cin>>Sr>>Sc>>Gr>>Gc;

    vector<pii> guards(2, {0, 0});
    for(ll i=0; i<k; ++i) cin>>guards[i].first>>guards[i].second;

    vector<string> grid(n); cin>>grid;
    memset(dist, -1, sizeof(dist));

    queue<State> q;
    State start = {Sr, Sc, guards[0].first, guards[0].second, guards[1].first, guards[1].second};

    q.push(start);
    dist[start.tr][start.tc][start.gr1][start.gc1][start.gr2][start.gc2] = 0;

    while(!q.empty()) {
        State curr = q.front();
        q.pop();

        int d = dist[curr.tr][curr.tc][curr.gr1][curr.gc1][curr.gr2][curr.gc2];

        for(int i = 0; i < 5; ++i) {
            int ntr = curr.tr + dx[i];
            int ntc = curr.tc + dy[i];

            if(ntr < 1 || ntr > n || ntc < 1 || ntc > m || grid[ntr - 1][ntc - 1] == '#') continue;

            if(k >= 1 && ntr == curr.gr1 && ntc == curr.gc1) continue;
            if(k == 2 && ntr == curr.gr2 && ntc == curr.gc2) continue;

            if(ntr == Gr && ntc == Gc) {
                cout << d + 1 << "\n";
                return;
            }

            int ngr1 = 0, ngc1 = 0;
            if(k >= 1) {
                auto next_g1 = get_next_guard_pos(curr.gr1, curr.gc1, ntr, ntc, n, m, grid);
                ngr1 = next_g1.first;
                ngc1 = next_g1.second;
            }

            int ngr2 = 0, ngc2 = 0;
            if(k == 2) {
                auto next_g2 = get_next_guard_pos(curr.gr2, curr.gc2, ntr, ntc, n, m, grid);
                ngr2 = next_g2.first;
                ngc2 = next_g2.second;
            }

            if(k >= 1 && ntr == ngr1 && ntc == ngc1) continue;
            if(k == 2 && ntr == ngr2 && ntc == ngc2) continue;

            if(dist[ntr][ntc][ngr1][ngc1][ngr2][ngc2] == -1) {
                dist[ntr][ntc][ngr1][ngc1][ngr2][ngc2] = d + 1;
                q.push({ntr, ntc, ngr1, ngc1, ngr2, ngc2});
            }
        }
    }

    cout<<-1;

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