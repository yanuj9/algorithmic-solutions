#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;

    vector<long long> A(N), B(N), C(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }

    vector<long long> enter(N, -1);

    queue<int> q; // waiting queue
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    // (leave_time, index)

    long long cur_people = 0;
    long long t = 0;
    int ptr = 0; // next arrival

    while (ptr < N || !q.empty() || !pq.empty()) {

        // 1. Add arrivals
        while (ptr < N && A[ptr] <= t) {
            q.push(ptr);
            ptr++;
        }

        // 2. Remove leavers
        while (!pq.empty() && pq.top().first <= t) {
            cur_people -= C[pq.top().second];
            pq.pop();
        }

        bool progressed = false;

        // 3. Admit front group if possible
        if (!q.empty()) {
            int i = q.front();
            if (cur_people + C[i] <= K) {
                enter[i] = t;
                cur_people += C[i];
                pq.push({t + B[i], i});
                q.pop();
                progressed = true;
            }
        }

        if (progressed) continue;

        // 4. Jump time
        long long next_t = LLONG_MAX;
        if (ptr < N) next_t = min(next_t, A[ptr]);
        if (!pq.empty()) next_t = min(next_t, pq.top().first);

        t = next_t;
    }

    for (int i = 0; i < N; i++) {
        cout << enter[i] << "\n";
    }

    return 0;
}
