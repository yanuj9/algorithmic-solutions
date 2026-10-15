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
constexpr ll INF = 1e9;
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

struct Point {
    int r, c;
};

// -------------------- Solver --------------------
void solve() {
    ll h,w,k; cin>>h>>w>>k;
    vector<string> grid(h);
    Point start_pt, shelter_pt;
    vector<Point> kittens;

    for(int i = 0; i < h; ++i) {
        cin>>grid[i];
        for(int j = 0; j < w; ++j) {
            if(grid[i][j] == '@') start_pt = {i, j};
            else if(grid[i][j] == 'G') shelter_pt = {i, j};
            else if(grid[i][j] == 'F') kittens.push_back({i, j});
        }
    }

    vector<Point> key_points;
    key_points.push_back(start_pt);
    for(auto& kt : kittens) key_points.push_back(kt);
    key_points.push_back(shelter_pt);

    int num_keys = key_points.size();
    vector<vector<int>> dist(num_keys, vector<int>(num_keys, -1));

    for(int i = 0; i < num_keys; ++i) {
        vector<vector<int>> min_steps(h, vector<int>(w, -1));
        queue<Point> q;

        Point src = key_points[i];
        min_steps[src.r][src.c] = 0;
        q.push(src);

        while(!q.empty()) {
            Point curr = q.front();
            q.pop();

            for(int d = 0; d < 4; ++d) {
                int nr = curr.r + dx[d];
                int nc = curr.c + dy[d];

                if(nr >= 0 && nr < h && nc >= 0 && nc < w) {
                    if(grid[nr][nc] != '#' && min_steps[nr][nc] == -1) {
                        min_steps[nr][nc] = min_steps[curr.r][curr.c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }

        for(int j = 0; j < num_keys; ++j) {
            Point dest = key_points[j];
            dist[i][j] = min_steps[dest.r][dest.c];
        }
    }

    for(int j = 1; j < num_keys; ++j) {
        if(dist[0][j] == -1) {
            cout<<"-1\n";
            return;
        }
    }

    int num_masks = (1 << k);
    vector<vector<int>> dp(num_masks, vector<int>(k + 1, INF));

    dp[0][0] = 0;

    for(int mask = 0; mask < num_masks; ++mask) {
        for(int curr_node = 0; curr_node <= k; ++curr_node) {
            if(dp[mask][curr_node] == INF) continue;

            for(int next_kitten = 0; next_kitten < k; ++next_kitten) {
                if(!(mask & (1 << next_kitten))) {
                    int next_mask = mask | (1 << next_kitten);
                    int next_node = next_kitten + 1;

                    if(dist[curr_node][next_node] != -1) {
                        dp[next_mask][next_node] = min(
                            dp[next_mask][next_node], 
                            dp[mask][curr_node] + dist[curr_node][next_node]
                        );
                    }
                }
            }
        }
    }

    int all_kittens_masked = num_masks - 1;
    int min_total_steps = INF;
    int shelter_idx = k + 1;

    for(int last_node = 0; last_node <= k; ++last_node) {
        if(dp[all_kittens_masked][last_node] != INF && dist[last_node][shelter_idx] != -1) {
            min_total_steps = min(
                min_total_steps, 
                dp[all_kittens_masked][last_node] + dist[last_node][shelter_idx]
            );
        }
    }


    if(min_total_steps == INF) cout<<"-1";
    else cout<<min_total_steps;

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