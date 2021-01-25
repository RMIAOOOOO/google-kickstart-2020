#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  int square_width;
  cin >> square_width;
  vector<vector<int> > matrix(square_width, vector<int>(square_width, 0));
  for(int i = 0 ; i < square_width; ++i){
    for(int j = 0 ; j < square_width; ++j){
      int input;
      cin >> input;
      matrix[i][j] = input;
    }
  }

  long int ans = 0;
  // 2. Iterate through bottom left diagonals
  for (int i = 0 ; i < square_width - 1 ; ++i) {
    int num_element_in_diagonal = i + 1;
    long int sum_bottom_left_diagonal = 0;
    for(int j = 0 ; j < num_element_in_diagonal; ++j){
      int row = square_width - i + j -1;
      int col = j;
      sum_bottom_left_diagonal += matrix[row][col];
    }
    ans = max(sum_bottom_left_diagonal, ans);
  }

  // 3. Try middle diagonals
  long int sum_logest_diagonal = 0;
  for (int j = 0 ; j < square_width; ++j) {
    int row = j;
    int col = j;
    sum_logest_diagonal += matrix[row][col];
  }
  ans = max(sum_logest_diagonal, ans);

  // 4. Iterate through upper right diagonals
  for (int i = 0 ; i < square_width - 1 ; ++i) {
    int num_element_in_diagonal = i+1;
    long int sum_upper_right_diagonal = 0;
    for(int j = 0 ; j < num_element_in_diagonal; ++j){
      int row = j;
      int col = square_width + j - i -1;
      sum_upper_right_diagonal += matrix[row][col];
    }
    ans = max(sum_upper_right_diagonal, ans);
  }

  cout << ans << "\n";
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
