#include <bits/stdc++.h>
using namespace std;

// 3. Overload comparison by comparing enjoy (first) + remembrance (second) of two toys.
class Compare {
public:
  bool operator() (pair<long long, long long> a, pair<long long, long long> b) {
    return a.first + a.second < b.first + b.second;
  }
};

void solve(){

  // 1. Get input
  int num_toy;
  vector<pair<long long, long long> > toys;
  cin >> num_toy;
  for (int i = 0; i < num_toy; ++i) {
    long long enjoy, remember;
    cin >> enjoy >> remember;
    toys.push_back(make_pair(enjoy, remember));
  }

  // 2. Calculate the first round time without removing any toy
  long long best_game_length = 0;
  long long round_time = 0;
  for (int i = 0; i < num_toy; ++i) {
    long long enjoy = toys[i].first;
    best_game_length += enjoy;
    round_time += enjoy;
  }

  // 3. Prepare priority queue structure for ordering toys that allows the game to run indefinitely.
  //    Toys with greatest (enjoy + remembrance) are placed on top of the priority queue.
  priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, Compare>
    second_round_indefinitely_toy_priority_queue;

  // 4. Iterate through every tops from first to last,
  //      begin by having every toy present in the first round.
  //    At every step, try adding the toy to second round.
  //      If a toy can be added, add it to priority queue as well and update score.
  //    If toy cannot be added, throw the toy away, and throw any of the previously
  //      added toys in the priority queue violating the new status.
  int current_num_toys_removed = 0;
  int best_num_toys_removed = 0;
  long long current_game_length = best_game_length;
  for (int i = 0; i < num_toy; ++i) {
    // 4.1  Check if adding a new toy to second round is illegal
    long long enjoy = toys[i].first;
    long long remembrance = toys[i].second;
    bool is_keeping_current_toy_indefinitely = round_time - enjoy >= remembrance;
    if (is_keeping_current_toy_indefinitely) {
      // 4.2.1  If toy can be added, update the best score
      //          and add to priority queue for later checking
      current_game_length += toys[i].first;
      if (current_game_length > best_game_length) {
        best_num_toys_removed = current_num_toys_removed;
        best_game_length = current_game_length;
      }
      second_round_indefinitely_toy_priority_queue.push(make_pair(enjoy, remembrance));
    }else{
      // 4.2.2.1 If toy cannot be added, throw away the toy,
      //         and pop and throw away all previously added toys that violates indefinitely.
      current_num_toys_removed ++;
      round_time -= enjoy;
      current_game_length -= enjoy;
      while(!second_round_indefinitely_toy_priority_queue.empty()) {
        long long top_toy_enjoy = second_round_indefinitely_toy_priority_queue.top().first;
        long long top_toy_remembrance = second_round_indefinitely_toy_priority_queue.top().second;
        bool is_top_toy_legal = round_time - top_toy_enjoy >= top_toy_remembrance;
        if (is_top_toy_legal) break;
      // 4.2.2.2 Remove the toy from round one as well
        else {
          current_game_length -= 2 * top_toy_enjoy;
          round_time -= top_toy_enjoy;
          second_round_indefinitely_toy_priority_queue.pop();
          current_num_toys_removed ++;
        }
      }
    }
  }

  // 5. Check for possible infinite solution. If any toy is in the priority_queue,
  //      they can make up indefinitely loop, else print best score
  bool has_indefinitely_solution = !second_round_indefinitely_toy_priority_queue.empty();
  if (has_indefinitely_solution) {
    cout << current_num_toys_removed << " " << "INDEFINITELY"<< "\n";
  } else {
    cout << best_num_toys_removed << " " << best_game_length << "\n";
  }
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
