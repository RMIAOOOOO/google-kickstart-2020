#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get Input
  int number_checkpoint;
  cin >> number_checkpoint;
  vector<int> heights(number_checkpoint);
  for (int i = 0; i < N; ++i) {
    int in;
    cin >> in;
    heights[i] = in;
  }

  // 2.Count valid checkpoints
  int answer = 0;
  for (int i = 1; i < N - 1; ++i) {
    if (heights[i] > heights[i-1] && heights[i] > heights[i+1]) {
      answer ++;
    }
  }

  cout << answer << endl;
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
