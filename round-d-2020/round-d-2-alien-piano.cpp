#include <bits/stdc++.h>
using namespace std;

void solve(){

  // 1. Get input
  int K;
  cin >> K;
  vector<int> A(K);
  for(int i = 0 ; i < K; ++i){
    int in;
    cin >> in;
    A[i] = in;
  }

  // 2. Iterate through the array, count for consecutive up or down.
  //    When there is 4 consecutive movement, break rule in the last note
  //      and increase answer.
  int consecutive_up = 0;
  int consecutive_down = 0;
  int last_note = A[0];
  int ans = 0;
  for(int i = 1; i < K; ++i){
    int current_note = A[i];
    if(current_note == last_note) {
      continue;
    } else if (current_note > last_note){
      consecutive_up ++;
      consecutive_down = 0;
      if (consecutive_up >= 4) {
        consecutive_up = 0;
        ans ++;
      }
    } else {
      consecutive_down ++;
      consecutive_up = 0;
      if (consecutive_down >= 4) {
        consecutive_down = 0;
        ans ++;
      }
    }
    last_note = current_note;
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
