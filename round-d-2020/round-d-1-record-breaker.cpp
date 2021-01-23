#include <bits/stdc++.h>
using namespace std;

void solve(){

  // 1. Get Input
  int N;
  cin >> N;
  vector<int> V(N);
  for (int i = 0 ; i < N; ++i) {
    int in;
    cin >> in;
    V[i] = in;
  }

  int ans = 0;
  int history_high = -1;

  // 2. Iterate through array and check condition
  for (int i = 0; i < N; ++i) {
    if(V[i] > history_high  && (i == N-1 || V[i] > V[i+1])) {
      ans ++;
    }
    history_high  = max(history_high , V[i]);
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    cout << "Case #" << i+1 << ": " ;
    solve();
  }
}

