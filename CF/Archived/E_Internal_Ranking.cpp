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

struct BIT {
    int n;
    vector<ll> bit;

    BIT(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // add value at index i (1-based)
    void update(int i, ll val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    // sum from 1 to i
    ll query(int i) {
        ll sum = 0;
        for (; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    // sum from l to r
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// -------------------- Solver --------------------
void solve() {
    ll n, q; cin >> n >> q;

    vector<pair<ll,ll>> vp(n);
    for(ll i = 0; i < n; i++) {
        cin >> vp[i].first >> vp[i].second;
    }

    sort(vp.begin(), vp.end());

    vector<ll> v(n+1);
    for(int i = 1; i <= n; i++) {
        v[i] = vp[i-1].second;
    }

    vector<ll> comp(v.begin()+1, v.end());
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    for(int i = 1; i <= n; i++) {
        v[i] = lower_bound(comp.begin(), comp.end(), v[i]) - comp.begin() + 1;
    }

    vector<pair<ll,ll>> order;
    for(int i = 1; i <= n; i++) {
        order.push_back({v[i], i});
    }

    sort(order.rbegin(), order.rend());
    vector<ll> left(n+1);
    BIT bit(n);

    for(int i = 0; i < n; ) {
        int j = i;

        while(j < n && order[j].first == order[i].first) j++;

        for(int k = i; k < j; k++) {
            int idx = order[k].second;
            left[idx] = bit.query(idx);
        }

        for(int k = i; k < j; k++) {
            int idx = order[k].second;
            bit.update(idx, 1);
        }

        i = j;
    }

    

    vector<ll> right(n+1);
    BIT bit2(n);

    for(int i = 0; i < n; ) {
        int j = i;

        while(j < n && order[j].first == order[i].first) j++;

        for(int k = i; k < j; k++) {
            int idx = order[k].second;
            right[idx] = bit2.query(idx, n);
        }

        for(int k = i; k < j; k++) {
            int idx = order[k].second;
            bit2.update(idx, 1);
        }

        i = j;
    }

    vector<ll> prefL(n+1), prefR(n+1);
    for(int i = 1; i <= n; i++) {
        prefL[i] = prefL[i-1] + left[i];
        prefR[i] = prefR[i-1] + right[i];
    }

    while(q--) {
        ll l, r; cin >> l >> r;

        ll k = r - l + 1;

        ll total = (prefL[r] - prefL[l-1]) + (prefR[r] - prefR[l-1]);

        ll pairs = total / 2;

        cout << pairs + k << '\n';
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