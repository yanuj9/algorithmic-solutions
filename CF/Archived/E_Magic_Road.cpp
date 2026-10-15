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

// -------------------- Matrix Exponentiation Helper --------------------
struct Matrix {
    static ll MOD; // Shared MOD; override in solve() if needed
    int size;
    vector<vll> mat;

    // Constructor: Initialize an N x N matrix with 0s
    Matrix(int n) : size(n), mat(n, vll(n, 0)) {}

    // Accessor: res(i, j) to get/set matrix[i][j]
    ll& operator()(int i, int j) { return mat[i][j]; }
    const ll& operator()(int i, int j) const { return mat[i][j]; }

    // Factory: Creates an Identity matrix (1s on diagonal)
    static Matrix identity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++) res(i, i) = 1;
        return res;
    }

    // Multiplier: A * B in O(N^3)
    Matrix operator*(const Matrix& other) const {
        Matrix res(size);
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                if (mat[i][k] == 0) continue; // Optimization: skip 0
                for (int j = 0; j < size; j++) {
                    ll prod = (mat[i][k] * other(k, j)) % MOD;
                    res(i, j) = (res(i, j) + prod) % MOD;
                }
            }
        }
        return res;
    }
};

ll Matrix::MOD = 998244353; // Default contest MOD

// Power: Computes A^K in O(N^3 * log K)
Matrix power(Matrix A, ll k) {
    Matrix res = Matrix::identity(A.size);
    while (k > 0) {
        if (k & 1) res = res * A; // Multiply if bit is set
        A = A * A;                // Square the base
        k >>= 1;                  // Next bit
    }
    return res;
}

// -------------------- Solver --------------------
void solve() {
    ll n,m,k; cin>>n>>m>>k;
    Matrix adj(n);
    for(ll i=0; i<m; ++i) {
        ll u,v,w; cin>>u>>v>>w;
        adj(u-1,v-1) = w;
    }

    Matrix ans = power(adj, k);
    cout<<ans(0,n-1);
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