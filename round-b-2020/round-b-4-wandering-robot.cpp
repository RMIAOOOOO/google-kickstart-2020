#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get Input
  int map_width, map_height, hole_left, hole_up, hole_right, hole_down;
  cin >> map_width >> map_height >> hole_left >> hole_up >> hole_right >> hole_down;

  // 2. List the hole's first upper right block's x and y
  //    List the hole's first lower left block's x and y
  int upper_right_path_valid_x = hole_right + 1;
  int upper_right_path_valid_y = hole_up - 1;
  int lower_left_path_valid_x = hole_left - 1;
  int lower_left_path_valid_y = hole_down + 1;

  // 3. List the two paths's checkpoint blocks at the diagonal of hole.
  //      Take into account the implicit path outside the map's boundary.
  //    The check points blocks are in the form: pair(x,y)
  vector<pair<int, int> > upper_right_path_blocks(0);
  int upper_right_path_width = map_width - hole_right;
  int upper_right_path_height = hole_up - 1;
  if (upper_right_path_width > 0 && upper_right_path_height > 0) {
    upper_right_path_blocks.resize(upper_right_path_height);
    for (int i = 0 ; i < upper_right_path_height; ++i) {
      upper_right_path_blocks[i] = make_pair(upper_right_path_valid_x + i , upper_right_path_valid_y - i);
    }
  }

  vector<pair<int, int> > lower_left_path_blocks(0);
  int lower_left_path_width = hole_left - 1;
  int lower_left_path_height = map_height - hole_down;
  if (lower_left_path_width > 0 && lower_left_path_height > 0) {
    lower_left_path_blocks.resize(lower_left_path_width);
    for (int i = 0 ; i < lower_left_path_width; ++i) {
      lower_left_path_blocks[i] = make_pair(lower_left_path_valid_x - i, lower_left_path_valid_y + i);
    }
  }

  // 4. Prepare the look up table of log_2(n!) to be used in the following step
  //    Ex. lookup[3] = log_2(6)
  vector<double> log_base_2_factorial_n_lookup(map_width + map_height);
  log_base_2_factorial_n_lookup[0] = log2(1.0);
  if (max(map_width,map_height) > 1) log_base_2_factorial_n_lookup[1] = log2(1.0);
  for (int i = 2; i < log_base_2_factorial_n_lookup.size(); ++i) {
    log_base_2_factorial_n_lookup[i] = log_base_2_factorial_n_lookup[i-1] + log2(i);
  }


  // 5. For each possible destination, calculate the probability in log form
  //      first then add up as exponential to avoid overflow
  //    C(n,k) / 2^n = 2^(log2(C(n,k) / 2^n))
  //    log2(C(n,k)/2^n) = log2(n!) - log2(k!) - log2((n-k!)) - n
  double upper_right_answer = 0;
  for (int k = 0; k < upper_right_path_blocks.size(); ++k) {
    int n = upper_right_path_blocks[0].first + upper_right_path_blocks[0].second - 2;
    double log_base_2_factorial_n = log_base_2_factorial_n_lookup[n];
    double log_base_2_factorial_k = log_base_2_factorial_n_lookup[k];
    double log_base_2_factorial_n_minus_k = log_base_2_factorial_n_lookup[n - k];
    double answer_as_exponent_of_2 = log_base_2_factorial_n - log_base_2_factorial_k - log_base_2_factorial_n_minus_k - n;
    upper_right_answer += pow(2.0, answer_as_exponent_of_2);
  }

  double lower_left_answer = 0;
  for (int k = 0; k < lower_left_path_blocks.size(); ++k) {
    int n = lower_left_path_blocks[0].first + lower_left_path_blocks[0].second - 2;
    double log_base_2_factorial_n = log_base_2_factorial_n_lookup[n];
    double log_base_2_factorial_k = log_base_2_factorial_n_lookup[k];
    double log_base_2_factorial_n_minus_k = log_base_2_factorial_n_lookup[n-k];
    double answer_as_exponent_of_2 = log_base_2_factorial_n - log_base_2_factorial_k - log_base_2_factorial_n_minus_k - n;
    lower_left_answer += pow(2.0, answer_as_exponent_of_2);
  }

  // 4. Add up possibility from upper right and lower left paths to get total answer
  double total_answer = upper_right_answer + lower_left_answer;
  cout << total_answer << "\n";
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
