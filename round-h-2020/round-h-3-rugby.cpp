#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get Input
  int N;
  cin >> N;
  vector<long long> x_coord(N);
  vector<long long> y_coord(N);
  for (int i = 0; i < N; ++i) {
    cin >> x_coord[i] >> y_coord[i];
  }

  int mid_index = N / 2;

  // 2. Get vertical movement cost
  //    Align player along the player in horizontal middle
  sort(y_coord.begin(), y_coord.end());
  long long final_y = y_coord[mid_index];
  long long cost_vertical = 0;
  for (int i = 0; i < N; ++i) {
    cost_vertical += abs(y_coord[i] - final_y);
  }

  // 3. Get horizontal movement cost, then sort player by X, then adjust best step based on index, sort again
  //    Align player along the player in the adjusted horizontal middle
  sort (x_coord.begin(), x_coord.end());
  for (int i = 0; i < N; ++i) {
    x_coord[i] -= i;
  }
  sort(x_coord.begin(), x_coord.end());

  long long final_x = x_coord[mid_index];
  long long cost_horizontal = 0;
  for (int i = 0; i < N; ++i) {
    cost_horizontal += abs(x_coord[i] - (final_x));
  }

  // 4. Calculate total cost
  long long ans = cost_horizontal + cost_vertical;
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
