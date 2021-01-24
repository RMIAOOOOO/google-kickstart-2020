#include <bits/stdc++.h>
using namespace std;

void solve(){

  // 1. Get input
  int num_building, a_visible, b_visible, both_visible;
  cin >> num_building >> a_visible >> b_visible >> both_visible;

  // 2. Go through every possible scenario
  int only_a_visible = a_visible - both_visible;
  int only_b_visible = b_visible - both_visible;
  vector<int> ans(0);
  long long max_height = num_building;
  long long second_height = max_height - 1;

  if (only_a_visible + only_b_visible + both_visible > num_building) {
    // 2.1 Case 1: More building than possibly could have, illegal, leave ans array empty
  } else if (num_building > 1 && a_visible == 1 && a_visible == b_visible && b_visible == both_visible){
    // 2.2 Case 2: Unreasonable case: only 1 building seen by both A and B, but has more than 1 building,
    //               leave ans empty.
  } else if (both_visible >= 2) {
    // 2.3 Case 3: has at least 2 both visible building, put all unseen low building between the visible ones,
    //               and the remaining building only seen by A and B in from of A and B respectively
    for(int i = 0; i < only_a_visible; ++i) ans.push_back(second_height);
    ans.push_back(max_height);
    for (int i = 0; i < num_building - (only_a_visible + only_b_visible + both_visible); ++i) ans.push_back(1);
    for (int i = 0; i < both_visible - 1 ; ++i) ans.push_back(max_height);
    for (int i = 0; i < only_b_visible; ++i) ans.push_back(second_height);
  } else { // only 1 building both visible
    // 2.4 Case 4: Only 1 visible building by both A and B.
    //             Need to hide the unseen low building between A and both or both and B
    if (a_visible == 1) {
      // 2.4.1  Case 4.1: Only A can see 1 building, cannot hide between A and both
      //                    Put highest in front of A, then hide unseen low building, then B's building
      ans.push_back(max_height);
      for (int i = 0; i < num_building - (only_a_visible + only_b_visible + both_visible); ++i) ans.push_back(1);
      for (int i = 0; i < b_visible - both_visible; ++i) ans.push_back(second_height);
    } else {
      // 2.4.1  Case 4.2: A sees more than one building, hide unseen low buildings between A and both seen.
      for (int i = 0; i < only_a_visible; ++i) ans.push_back(second_height);
      for (int i = 0; i < num_building - (only_a_visible + only_b_visible + both_visible); ++i) ans.push_back(1);
      for (int i = 0; i < both_visible; ++i) ans.push_back(max_height);
      for (int i = 0; i < only_b_visible; ++i) ans.push_back(second_height);
    }
  }

  // 3. Output
  if (ans.size() == 0) {
    cout << "IMPOSSIBLE" ;
  } else {
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i];
      if(i != ans.size()-1) cout << " ";
    }
  }
  cout << "\n";
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
