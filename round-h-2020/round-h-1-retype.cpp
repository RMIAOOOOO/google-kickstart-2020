#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  long long total_level, current_level, weapon_level;
  cin >> total_level >> current_level >> weapon_level;

  // 2. Calculate two potion's cost and compare
  long long restart_cost = (current_level - 1) + 1 + total_level;
  long long go_back_cost = (current_level - 1) + (current_level - weapon_level) + (total_level - weapon_level + 1);
  long long ans = min(restart_cost, go_back_cost);

  cout << ans << "\n";
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
