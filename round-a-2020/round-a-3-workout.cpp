#include <bits/stdc++.h>
using namespace std;

int reduction_required (const vector<int> &differences, int min_diff) {
  int result = 0;
  for(int i = 0; i < differences.size(); ++i){
    int num_reduction = (differences[i] - 1) / min_diff;
    result += num_reduction;
  }
  return result;
}

void solve() {

  // 1. Get input
  int num_exercise, num_extra_session;
  cin >> num_exercise >> num_extra_session;
  vector<int> difficuites(num_exercise, 0);
  for (int i = 0; i < num_exercise; ++i) {
    int in;
    cin >> in;
    difficuites[i] = in;
  }

  // 2. Get differences
  vector<int> differences(num_exercise - 1, 0);
  for (int i = 0; i < num_exercise - 1; ++i)
    differences[i] = difficuites[i+1] - difficuites[i];

  // 3. binary search through all possible minimum interval, left_bound is the min viable solution
  int left_bound = 1;
  int right_bound = difficuites[num_exercise - 1] - difficuites[0];

  while (right_bound > left_bound) {
    int mid = (right_bound + left_bound) / 2;

    int mid_reduction_required = reduction_required(differences, mid);
    if (mid_reduction_required <= num_extra_session) {
      right_bound = mid;
    } else {
      left_bound = mid+1;
    }
  }

  cout << left_bound << "\n";
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
