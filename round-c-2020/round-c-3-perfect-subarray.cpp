#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. get input, keep track of maximum and minimum of possible sub array sum for later indexing
  int N;
  cin >> N;
  vector<int> numbers(N);
  vector<int> prefix_sum(N);
  int positive_sum_limit = 0;
  int negative_offset = 0;
  for (int i = 0; i < N; ++i) {
    int in;
    cin >> in;
    numbers[i] = in;
    if (i == 0) {
      prefix_sum[i] = in;
    } else {
      prefix_sum[i] = prefix_sum[i-1] + in;
    }

    if(in > 0) {
      positive_sum_limit += in;
    } else {
      negative_offset += -in;
    }
  }

  // 2. construct lookup table for square numbers, up to the max possible sub array sum
  vector<int> perfect_squares(1);
  perfect_squares[0] = 0;
  int max_base = 1;
  while( max_base * max_base <= positive_sum_limit){
    perfect_squares.push_back(max_base * max_base);
    max_base ++;
  }

  // 3. Iterate through prefix, for every prefix, try all squared numbers by
  //      checking the previous prefix that can be subtracted off to get the
  //      specific squared number.
  vector<int> previous_sum_map(negative_offset + positive_sum_limit + 1, 0);
  previous_sum_map[negative_offset] = 1;
  long long answer = 0;

  //    3.1 Iterate through every prefix
  for (int index = 0; index < N; ++index) {
  //    3.1.1 Iterate through every possible squared numbers, check if there is previous
  //            prefix that can be subtracted off from the current prefix to get the square
    for (int square_base = 0; square_base <  max_base; ++square_base) {
      int supplementary_number = prefix_sum[index] - perfect_squares[square_base];
      int supplementary_number_offseted_index = negative_offset + supplementary_number;
      if(supplementary_number_offseted_index < previous_sum_map.size() && supplementary_number_offseted_index >= 0) {

        answer += previous_sum_map[supplementary_number_offseted_index];
      }
    }

  //    3.2 Add the prefix to the array, waiting for the following prefixes to check from
    int current_prefix_offseted_index = negative_offset + prefix_sum[index];
    previous_sum_map[current_prefix_offseted_index] ++;
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
