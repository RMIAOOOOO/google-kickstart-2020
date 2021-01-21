#include <bits/stdc++.h>
using namespace std;

long long LIMIT = 1e9;

void solve() {

  // 1. Get input
  //    has_char records whether the character is used in the wall
  int row, column;
  cin >> row >> column;
  vector<bool> has_char(26, false);
  vector<vector<char> > walls(row, vector<char>(column, ' '));
  for (int i = 0; i < row; ++i) {
    string in;
    cin >> in;
    for (int j = 0; j < column; ++j) {
      walls[i][j] = in[j];
      int current_char_index = in[j] - 'A';
      has_char[current_char_index] = true;
    }
  }

  // 2. Construct a dependency lookup table
  //    Ex. depends_on[3][4] means there is a block 'd' that is before a block 'e',
  //          so block 'd' depends on 'e'.
  vector<vector<bool> > depends_on(26, vector<bool>(26, false));
  for (int i = 0; i < row - 1; ++i) {
    for (int j = 0; j < column; ++j) {
      int current_char_index = walls[i][j] - 'A';
      int below_char_index = walls[i+1][j] - 'A';
      if(current_char_index != below_char_index){
        depends_on[current_char_index][below_char_index] = true;
      }
    }
  }

  // 3. Pick the shape that are stabilized in the beginning and
  //    record whether the characters that are waiting for base.
  //    stabilized_shape are the orders the wall can be built in.
  vector<int> stabilized_shape(0);
  vector<int> waiting_for_base(26, false);
  for(int i = 0 ; i < 26; ++i){
    if(has_char[i]){
      for(int j = 0; j < 26; ++j){
        if(depends_on[i][j]){
          waiting_for_base[i] = true;
        }
      }
      if(!waiting_for_base[i]){
        stabilized_shape.push_back(i);
      }
    }
  }

  // 4. For every iteration, try to see if a character is now stabled
  //    Add the stabled ones into the stabilized_shapes
  for (int iteration = 0; iteration < 26; ++iteration) {
    for (int character = 0; character < 26; ++character) {
      if (waiting_for_base[character]) {
        bool base_all_found = true;
        for (int j = 0; j < 26; ++j) {
          if (depends_on[character][j] && !waiting_for_base[j]) {
            base_all_found = false;
          }
        }
        if (base_all_found) {
          waiting_for_base[character] = false;
          stabilized_shape.push_back(character);
        }
      }
    }
  }

  // 5. Construct answer string
  string answer = "";
  for (int i = 0; i < stabilized_shape.size(); ++i) {
    char new_char = stabilized_shape[i] + 'A';
    answer += new_char;
  }

  // 6. Check all the shapes are stabilized
  bool has_solution = true;
  for (int i = 0 ; i < 26; ++i) {
    if(waiting_for_base[i]) has_solution = false;
  }

  // 7. Output
  if(has_solution)
    cout << answer << endl;
  else
    cout << "-1" << endl;
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
