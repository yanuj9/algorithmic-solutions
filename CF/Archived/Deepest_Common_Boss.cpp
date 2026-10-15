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
    constexpr int MAXN = 3e5 + 7;

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

    struct SparseTable {
        long long n, K;
        vector<vector<long long>> st;
        vector<long long> lg;
        vector<ll> v;

        SparseTable(const vector<long long>& a) {
            v = a;
            n = a.size();
            K = log2(n) + 1;
            st.assign(K, vector<long long>(n));
            lg.assign(n + 1, 0);

            for (long long i = 2; i <= n; i++)
                lg[i] = lg[i / 2] + 1;

            for (long long i = 0; i < n; i++)
                st[0][i] = i;

            for (long long j = 1; j < K; j++) {
                for (long long i = 0; i + (1 << j) <= n; i++) {
                    ll leftIdx = st[j - 1][i], rightIdx = st[j - 1][i + (1 << (j - 1))];
                    if(v[leftIdx] < v[rightIdx]) {
                        st[j][i] = leftIdx;
                    }
                    else st[j][i] = rightIdx;
                }
            }
        }

        long long query(long long L, long long R) {
            long long j = lg[R - L + 1];
            ll leftIdx = st[j][L], rightIdx = st[j][R - (1 << j) + 1];
            return (v[leftIdx] < v[rightIdx]) ? leftIdx : rightIdx;
        }
    };

    vll nodes, depths;
    vll firstOccurence(MAXN);

    void dfs(ll src, ll d, vector<vll>& adj) {
        firstOccurence[src] = nodes.size();
        nodes.push_back(src);
        depths.push_back(d);
        for(auto c:adj[src]) {
            dfs(c,d+1,adj);
            nodes.push_back(src);
            depths.push_back(d);
        }
    }

    // -------------------- Solver --------------------
    void solve() {
        ll n,q; cin>>n>>q;
        vector<vll> adj(n+1);
        for(ll i=2; i<=n; ++i) {
            ll p; cin>>p;
            adj[p].push_back(i);
        }
        dfs(1,1,adj);
        SparseTable sptMnmIdx(depths);
        while(q--) {
            ll x,y; cin>>x>>y;
            ll l = firstOccurence[x], r = firstOccurence[y];
            if(l > r) swap(l,r);
            ll idx = sptMnmIdx.query(l,r);
            cout<<nodes[idx]<<endl;
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