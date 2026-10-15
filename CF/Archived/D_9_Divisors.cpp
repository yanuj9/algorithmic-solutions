#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll LIM = sqrtl(N);

    // Sieve up to sqrt(N)
    int MAXP = 2000000;
    vector<bool> isprime(MAXP + 1, true);
    vector<int> primes;

    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= MAXP; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= MAXP)
                for (ll j = (ll)i * i; j <= MAXP; j += i)
                    isprime[j] = false;
        }
    }

    ll ans = 0;

    // Case 1: p^8
    for (ll p : primes) {
        ll x = 1;
        for (int i = 0; i < 8; i++) {
            if (x > N / p) {
                x = N + 1;
                break;
            }
            x *= p;
        }
        if (x <= N) ans++;
        else break;
    }

    // Case 2: p^2 q^2  <=>  p*q <= sqrt(N)
    int m = primes.size();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if ((ll)primes[i] * primes[j] > LIM) break;
            ans++;
        }
    }

    cout << ans << "\n";
}
