// snippets

using ll = long long;

// 0.0 or smallest x	1e6 or largest x
double ternary_search(double lo, double hi) {
    while (hi - lo > EPS) { // EPS is very small, like 1e-6 or 1e-9
        double mid1 = lo + (hi - lo) / 3.0;
        double mid2 = hi - (hi - lo) / 3.0;
        if (f(mid1) < f(mid2)) {
            hi = mid2;
        } else {
            lo = mid1;
        }
    }
    return (lo + hi) / 2.0; // safer option or else can use lo (95% times works)
}

// 0 or smallest x	1e5 or largest x
ll ternary_search(ll lo, ll hi) {
    while (lo < hi) {
        ll mid1 = lo + (hi - lo) / 3;
        ll mid2 = hi - (hi - lo) / 3;
        if (f(mid1) < f(mid2))
            hi = mid2 - 1;
        else
            lo = mid1 + 1;
    }
    return lo;
}

int binarySearchExact(vector<int>& a, int x) {
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        else if (a[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1; // Not found
}

// Key point: r doesn’t need to be the smallest possible — it just has to be a safe upper bound that definitely works.
// sum(nums) is the safest possible because it’s the largest any contiguous segment could sum to.


// use hi = a.size() - 1 if answer is guaranteed to exist
int leftmostOccurence(vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo; // First index >= x
}

int rightmostOccurence(vector<int>& a, int x) {
    int lo = 0, hi = a.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;  // bias to right
        if (a[mid] <= x) lo = mid;        // valid, might go further
        else hi = mid - 1;                // invalid, go left
    }
    return lo;  // rightmost index where a[i] <= x
}

// lo and hi initialization doesn't matter but prefer
// lo = 0, hi = 1e14 ... modify as per the need
double binarySearchFloat(double lo, double hi) {
    const double EPS = 1e-9;
    while (hi - lo > EPS) {
        double mid = (lo + hi) / 2;
        if (condition(mid)) hi = mid;
        else lo = mid;
    }
    return lo;  // or hi
}

long long low = MIN_POSSIBLE, high = MAX_POSSIBLE;
long long answer = -1;
// answer is what is we expect can be answer and lies in [low, high]
while (low <= high) {
    long long mid = low + (high - low) / 2;

    if (check(mid)) {
        answer = mid;      // mid is a possible answer
        high = mid - 1;    // try to find a smaller one
    } else {
        low = mid + 1;     // mid too small, try bigger
    }
    // answer now holds the optimal result
}


// disjoint union
vector<int> parent, rank;
int find(int x) {
    if(parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}
void Union(int x, int y) {
    int x_parent = find(x);
    int y_parent = find(y);
    
    if(rank[x_parent] > rank[y_parent]) {
        parent[y_parent] = x_parent;
    }
    else if(rank[x_parent] < rank[y_parent]) {
        parent[x_parent] = y_parent;
    }
    else {
        parent[x_parent] = y_parent;
        rank[y_parent]++;
    }
}

// parent call 
parent.resize(n); rank.resize(n,0);
iota(parent.begin(), parent.end(), 0);

ll gcd(ll x,ll y)
{
    if(x==0) return y;
    return gcd(y%x,x);
}
// O(log min(a,b))
// O(sqrt(n)) 
bool isPrime(ll n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (ll i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
// O(sqrt(n))
vector<int> factors(int n) {
	vector<int> f;
	for (int x = 2; x*x <= n; x++) {
		while (n%x == 0) {
			f.push_back(x);
			n /= x;
			}
	}
	if (n > 1) f.push_back(n);
	return f;
}
// for multiple queries of primes, implement this O(log n) time O(n) space
void SieveOfEratosthenes(ll n) {
    vector<bool> prime(n + 1, true);
 
    for (ll p = 2; p * p <= n; p++) {
        if (prime[p] == true) {
            for (ll i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
 
    for (ll p = 2; p <= n; p++)
        if (prime[p])
            cout << p << " ";
}
// O(log n) 
ll modpow(ll x, ll n, ll m) {
	if (n == 0) return 1%m;
	ll u = modpow(x,n/2,m);
	u = (u*u)%m;
	if (n%2 == 1) u = (u*x)%m;
	return u;
}

// Binary Exponentiation O(log n)
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

// O (log n) expo Mod
ll expoMod(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll modinv(ll A, ll M) {
    ll m0 = M;
    ll y = 0, x = 1;
 
    if (M == 1)
        return 0;
 
    while (A > 1) {
        ll q = A / M;
        ll t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

// Totient Function - O(√n log n)
ll phi(ll n) {
    ll result = n;
  
    for(ll p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
                 
            result -= result / p;
        }
    }
    
    if (n > 1)
        result -= result / n;
         
    return result;
}
// NchooseR
ll nCr(ll n, ll r) {
    if(r > n - r) r = n - r;
    ll ans = 1;

    for(ll i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}

// needs MOD to be prime
vector<ll> fact(MAXN,1);
vector<ll> invf(MAXN,1);
vector<ll> invNaturalNo(MAXN,1);

void inv() {
	for(ll i=2; i<= MAXN - 2; ++i) {
		invNaturalNo[i] = invNaturalNo[MOD % i] * (MOD - MOD / i) % MOD;
	}
}
// (fact[n] * invf[k]) % MOD * invf[n-k]) % MOD 
void f() {
	for(ll i=2; i<= MAXN - 2; ++i) {
		fact[i] = (fact[i-1] * i) % MOD;
	}
	for(ll i=2; i<= MAXN - 2; ++i) {
		invf[i] = (invf[i-1] * invNaturalNo[i]) % MOD;
	}
}

//  O(n) precomputation and O(1) for every query
ll nCrModP(ll n, ll k) {
	return ((fact[n] * invf[k]) % MOD * invf[n-k]) % MOD;
}

inv();
f();


// another inv function (when n is too large with % mod ) -> inv(1/n) % mod
// and mod is prime - Fermet's little theorem
ll inv(ll n, ll mod) {
	return binpow(n,mod - 2)
}

// xor l to r logic
ll xor0ToN(ll n) {
	ll m = n;
	m %= 4;
	switch(n) {
		case 0 : return n;
			     break;
		case 1 : return 1;
		         break;
		case 2 : return n + 1;
			     break ;
	    default : return 0;
	}
}

ll xorLToR(ll l,ll r) {
	ll xorUptoL = xor0ToN(l);
	ll xorUptoR = xor0ToN(r);
	return xorUptoL ^ xorUptoR;
}

struct point {
	ll x,y;
	point() : x(0), y(0) {}
	point(ll a, ll b) {
		x = a;
		y = b;
	}
};

// DSU

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

// ================== 🔹 MERGE SORT TREE ==================
struct MergeSortTree {
    int n;
    vector<vector<ll>> tree;

    MergeSortTree(int n) {
        this->n = n;
        tree.resize(4 * n);
    }

    void build(int node, int l, int r, vector<vll> &arr) {
        if (l == r) {
            tree[node] = arr[l];
            sort(all(tree[node]));
            return;
        }

        int mid = (l + r) / 2;
        build(2*node, l, mid, arr);
        build(2*node+1, mid+1, r, arr);

        auto &L = tree[2*node];
        auto &R = tree[2*node+1];

        tree[node].resize(L.size() + R.size());
        merge(all(L), all(R), tree[node].begin());
    }

    // count elements >= val in range [ql, qr]
    ll query(int node, int l, int r, int ql, int qr, ll val) {
        if (r < ql || l > qr) return 0;

        if (ql <= l && r <= qr) {
            auto &vec = tree[node];
            auto it = lower_bound(all(vec), val);
            return vec.end() - it;
        }

        int mid = (l + r) / 2;
        return query(2*node, l, mid, ql, qr, val) +
               query(2*node+1, mid+1, r, ql, qr, val);
    }
};

// ================== 🔹 BIT (Fenwick Tree) ==================
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

// ================== 🔹 Sparse Table for Range Minimum Query (RMQ) ==================
struct SparseTable {
    int n, K;
    vector<vi> st;
    vi lg;
    SparseTable(const vi& a) {
        n = a.size();
        K = log2(n) + 1;
        st.assign(K, vi(n));
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < n; i++) st[0][i] = a[i];
        for (int j = 1; j < K; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    int query(int L, int R) {
        int j = lg[R - L + 1];
        return min(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

// ================== 🔹 Segment Tree ==================

class SegmentTree {
    vector<ll> tree;
    int n;

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    void build(const vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * v, tl, tm);
            build(a, 2 * v + 1, tm + 1, tr);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    void update(int v, int tl, int tr, int pos, ll new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(2 * v, tl, tm, pos, new_val);
            else
                update(2 * v + 1, tm + 1, tr, pos, new_val);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return tree[v];
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, min(r, tm)) +
               query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    }
};

// using segment tree
SegmentTree st(N);
st.build(A, 1, 1, N);


















/////////////////////////////////////////////////////////////////////////////////////
////////
//////// sparse table ll implementation

const ll LOG = 20; // because 2^17 > 1e5

ll st[MAXN][LOG]; // sparse table [starting pos, just smaller size than n with length - power of 2]
ll log_table[MAXN];

void build_log(ll N) {
    log_table[1] = 0;
    for (ll i = 2; i <= N; ++i)
        log_table[i] = log_table[i / 2] + 1;
}

void build_sparse(const vll &A, ll N) {
    for (ll i = 0; i < N; ++i)
        st[i][0] = A[i];

    for (ll j = 1; (1 << j) <= N; ++j) {
        for (ll i = 0; i + (1 << j) <= N; ++i) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

ll query_min(ll L, ll R) {
    ll j = log_table[R - L + 1];
    return min(st[L][j], st[R - (1 << j) + 1][j]);
}

build_log(n);
build_sparse(vectorV,n);


// sparse table

const int MAXN = 1e5 + 5;
const int LOG = 17; // because 2^17 > 1e5

int st[MAXN][LOG]; // sparse table
int log_table[MAXN];

void build_log(int N) {
    log_table[1] = 0;
    for (int i = 2; i <= N; ++i)
        log_table[i] = log_table[i / 2] + 1;
}

void build_sparse(const vector<int> &A, int N) {
    for (int i = 0; i < N; ++i)
        st[i][0] = A[i];

    for (int j = 1; (1 << j) <= N; ++j) {
        for (int i = 0; i + (1 << j) <= N; ++i) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query_min(int L, int R) {
    int j = log_table[R - L + 1];
    return min(st[L][j], st[R - (1 << j) + 1][j]);
}

