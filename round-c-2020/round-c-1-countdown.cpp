#include <bits/stdc++.h>
using namespace std;

long long LIMIT = 1e9;

void solve() {

  // 1. Get Input
  int num_number, k_countdown;
  cin >> num_number >> k_countdown;
  vector<int> numbers(num_number);
  for (int i = 0; i < num_number; ++i) {
    int in;
    cin >> in;
    numbers[i] = in;
  }

  // 2. Iterate through the numbers, start counting down when meet K.
  bool is_currently_counting_down = false;
  int currently_count_down_to = k_countdown;
  int answer = 0 ;

  for (int i = 0; i < num_number; ++i) {
    if (is_currently_counting_down) {
      if (numbers[i] == currently_count_down_to) {
        currently_count_down_to--;
        if (currently_count_down_to == 0) {
          answer ++;
          is_currently_counting_down = false;
          currently_count_down_to = k_countdown;
        }
      } else {
        currently_count_down_to = k_countdown;
        i--;
        is_currently_counting_down = false;
      }
    } else {
      if( numbers[i] == k_countdown) {
        currently_count_down_to = k_countdown - 1;
        is_currently_counting_down = true;
      }
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
