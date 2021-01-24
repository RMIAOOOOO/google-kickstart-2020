#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  int N;
  cin >> N;
  vector<int> numbers(N);
  for (int i = 0; i < N ; ++i) {
    int in;
    cin >> in;
    numbers[i] = in;
  }

  // 2. Iterate through numbers to count the occurrence of same delta and update answer
  int longest_length = 1;
  int last_difference = numbers[1] - numbers[0];
  int continuous_count = 1;
  for (int i = 2 ; i < N ; ++i) {
    int new_difference = numbers[i] - numbers[i-1];
    if (new_difference == last_difference) {
      continuous_count ++;
      longest_length = max(continuous_count, longest_length);
    } else {
      last_difference = new_difference;
      continuous_count = 1;
    }
  }

  cout << longest_length + 1 << "\n";
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
