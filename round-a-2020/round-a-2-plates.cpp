#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  int num_stack, num_plate_per_stack, plate_quota;
  cin >> num_stack >> num_plate_per_stack >> plate_quota;

  // 2. Compute the sum of beauty when selecting a stack with depth of n plates.
  vector<vector<long long> > stack_depth_beauty_sum(num_stack, vector<long long>(num_plate_per_stack, 0));

  for (int i = 0; i < num_stack; ++i) {
    long long current_sum = 0;
    for (int j = 0; j < num_plate_per_stack; ++j) {
      int input = 0;
      cin >> input;
      current_sum  += input;
      stack_depth_beauty_sum[i][j] = current_sum;
    }
  }

  // 3. Initialize an array for storing the maximum beauty by only selecting n plates
  vector<long long> n_plates_maximum_beauty(plate_quota + 1, 0);

  // 4.1 Update the n_plates_maximum_beauty array by stepping through every stack
  //     Create a new_n_plates_max array that involves choosing the plates from current stack
  for (int current_stack = 0; current_stack < num_stack; ++current_stack) {
    vector<long long> new_n_plates_max(plate_quota + 1, 0);
    // 4.2 For every stack, try choosing different number of plates in current stack
    for (int current_stack_depth = 1; current_stack_depth <= num_plate_per_stack; ++current_stack_depth) {
      // 4.3 For every number of plates selected in this stack, fit with valid numbers of selected plates from previous stages
      //     Update the new_n_plates_max by trying out the combination
      for (int previous_consumed_quota = 0; previous_consumed_quota + current_stack_depth <= plate_quota; ++previous_consumed_quota) {
        int total_num_plates = current_stack_depth + previous_consumed_quota;
        long long current_stack_depth_beauty = stack_depth_beauty_sum[current_stack][current_stack_depth-1];
        long long current_total_beauty = current_stack_depth_beauty + n_plates_maximum_beauty[previous_consumed_quota];
        new_n_plates_max[total_num_plates] = max(new_n_plates_max[total_num_plates], current_total_beauty);
      }
    }

    // 4.4 Update the old n_plates_maximum_beauty with new ones
    for (int i = 0; i < plate_quota +1; ++i) {
      n_plates_maximum_beauty[i] = max(n_plates_maximum_beauty[i], new_n_plates_max[i]);
    }

  }

  // 5. Answer will be the updated array when n plates are selected
  long long answer = n_plates_maximum_beauty[plate_quota];

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

