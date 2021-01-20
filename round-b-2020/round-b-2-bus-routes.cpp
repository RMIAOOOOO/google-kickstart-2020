#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get Input
  int number_checkpoint, num_day;
  cin >> number_checkpoint >> num_day;
  vector<long long> intervals(number_checkpoint);
  for (int i = 0; i < number_checkpoint; ++i) {
    long long in;
    cin >> in;
    intervals[i] = in;
  }

  // 2. Iterate from the last bus, try catch up the previous bus as
  //      late as possible, reduce the days from the latest_day_depart
  long long latest_day_depart = num_day;
  for (int i = number_checkpoint - 1; i >= 0 ; --i) {
    long long days_to_nearest_previous_bus = latest_day_depart % intervals[i];
    latest_day_depart -= days_to_nearest_previous_bus;
  }

  cout << latest_day_depart << endl;
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

