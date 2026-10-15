snippets

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

// Leftmost True → “Find the smallest x such that check(x) is true.”
// ✅ Invariant:
// check(mid) is monotonic (false → true).
// At any point:
// [minimal_possible_value, hi] = all known-false
// [lo, maximal_possible_value] = possible or true
// ans = smallest known-true so far.

// long long lo = minimal_possible_value;
// long long hi = maximal_possible_value;
long long leftmostTrue(long long lo, long long hi) {
    // lo : “Whatever the correct answer is, it won’t be smaller than this.”
    // hi : “Even if the answer is extremely large, it must be ≤ this value.”

    long long ans = LLONG_MAX; // sentinel for "no true found"

    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid)) { 
            ans = mid;      // found a true
            hi = mid - 1;   // look for smaller true
        } else lo = mid + 1;
    }

    return ans == LLONG_MAX ? -1 : ans; // -1 = not found
}




// Rightmost True → “Find the largest x such that check(x) is true.”
// ✅ Invariant:
// check(mid) monotonic (true → false).
// At any point:
// [minimal_possible_value, lo] = all known-true
// [hi, maximal_possible_value] = all known-false
// ans = largest known-true so far.


// long long lo = minimal_possible_value;
// long long hi = maximal_possible_value;
long long rightmostTrue(long long lo, long long hi) {
    // lo : “Whatever the correct answer is, it won’t be smaller than this.”
    // hi : “Even if the answer is extremely large, it must be ≤ this value.”

    long long ans = LLONG_MIN; // sentinel for "no true found"

    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid)) { 
            ans = mid;      // found a true
            lo = mid + 1;   // try larger true
        } else hi = mid - 1;
    }

    return ans == LLONG_MIN ? -1 : ans; // -1 = not found
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

vector<ll> fact(MAX,1);
vector<ll> invf(MAX,1);
vector<ll> invNaturalNo(MAX,1);

void inv() {
	for(ll i=2; i<= MAX - 2; ++i) {
		invNaturalNo[i] = invNaturalNo[mod % i] * (mod - mod / i) % mod;
	}
}
// (fact[n] * invf[k]) % mod * invf[n-k]) % mod 
void f() {
	for(ll i=2; i<= MAX - 2; ++i) {
		fact[i] = (fact[i-1] * i) % mod;
	}
	for(ll i=2; i<= MAX - 2; ++i) {
		invf[i] = (invf[i-1] * invNaturalNo[i]) % mod;
	}
}

//  O(n) precomputation and O(1) for every query
ll nCrModP(ll n, ll k) {
	return ((fact[n] * invf[k]) % mod * invf[n-k]) % mod;
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

// Segment Tree

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


////// Binary Search Pattern 2 - Invariant always to maintain : One end always true and one end always false
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