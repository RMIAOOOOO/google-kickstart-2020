#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  int num_people, max_withdraw = 0;
  vector<pair<int, int> > amount_ith_person_pair;
  cin >> num_people >> max_withdraw;

  // 2. Create a pair vector for sorting by number of round take then by person number
  amount_ith_person_pair.resize(num_people);
  for (int i = 0; i < num_people; ++i) {
    int input;
    cin >> input;
    int round = (input - 1) / max_withdraw;
    amount_ith_person_pair[i] = make_pair(round, i);
  }

  // 3. Sort the vector using pair's sort: sort first by round taken then by person number
  sort(amount_ith_person_pair.begin(), amount_ith_person_pair.end());

  // 4. Output the person number after sorting
  for (int i  = 0; i < num_people; ++i) {
    cout << amount_ith_person_pair[i].second + 1;
    if (i != num_people - 1) cout << " " ;
  }
  cout << "\n";

//  cout << ans << "\n";
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
