#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  int num_interval, max_harvest;
  cin >> num_interval >> max_harvest;
  vector<int> start_time(num_interval);
  vector<int> end_time(num_interval);
  for (int i = 0; i < num_interval; ++i) {
    int start_in, end_in;
    cin >> start_in >> end_in;
    start_time[i] = start_in;
    end_time[i] = end_in;
  }

  // 2. Create session queue vector, pair stores (start_time, session_length)
  //    Then sort by start time
  vector<pair<int, int> > harvest_time_queue(num_interval);
  for (int i = 0; i < num_interval; ++i) {
    int start = start_time[i];
    int length = end_time[i] - start_time[i];
    harvest_time_queue[i] = make_pair(start, length);
  }
  sort(harvest_time_queue.begin(), harvest_time_queue.end());

  // 3. Iterate through session from first to last, start a new harvest if a session cannot be covered.
  int answer = 0;
  int last_harvest_end = 0;
  for (int i = 0; i < num_interval; ++i) {
    int current_session_start_time = harvest_time_queue[i].first;
    int current_session_finish_time = harvest_time_queue[i].first + harvest_time_queue[i].second;
    // 3.1 If the new session can be covered by last harvest, do nothing
    if (last_harvest_end >= current_session_finish_time) {
      continue;
    } else {
    // 3.2 If the session cannot be covered, cover it up with new harvests
      int new_harvest_start_time = max(last_harvest_end, current_session_start_time);
      int new_session_remaining_time = current_session_finish_time - new_harvest_start_time;

      int num_deploy_this_session = ((new_session_remaining_time - 1) / max_harvest) + 1;
      answer += num_deploy_this_session;
      last_harvest_end = new_harvest_start_time + (num_deploy_this_session * max_harvest);
    }
  }

  cout << answer << "\n";
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
