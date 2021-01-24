#include <bits/stdc++.h>
using namespace std;

enum player
{
  Alma = 0,
  Bertha = 1
};

// Translate row, col into index in string represented museum
// Ex. museum   (2, 2), which is row 3 position 3, will return 6, which is 7th in string
int translateToStringIndex(int row, int col) {
  return row * row + col;
}

// 3.1  Get current player row and position
void getCurrentPlayerRowsAndPosition(string currentState, int round, int &returned_row, int &returned_position) {
  // 3.1.1 Get current player
  int target_player_symbol = (round == Alma ? 'A' : 'B');
  int index = 0;
  // 3.1.2 Find current player in museum string
  for (int i = 0; i < currentState.length(); ++i) {
    if (currentState[i] == target_player_symbol) {
      index = i;
      break;
    }
  }
  // 3.1.3 Translate museum index to row and col
  int row = 0;
  while ((row + 1) * ( row + 1) -1 < index) row++;
  int col = index - row * row;

  // 3.1.4 Return
  returned_row = row;
  returned_position = col;
}

// 3.2.1 Check whether a move is an legal move
bool isMoveLegal(string room, int row, int position, int length) {
  bool row_out_of_boundary = row < 0 || row >= length;
  if (row_out_of_boundary) return false;

  bool position_out_of_boundary = position < 0 || position >= row * 2 + 1;
  if (position_out_of_boundary) return false;

  bool room_not_free = room[translateToStringIndex(row, position)] != 'f';
  if (room_not_free) return false;

  return true;
}

// 3.2 Get current player possible moves
void getPossibleMoves (string room, int row, int position, vector<pair<int, int> > &possibleMoves, int length) {
  if(position % 2 == 0){
    // left right down
    if (isMoveLegal(room, row, position-1, length)) possibleMoves.push_back(make_pair(row, position-1));
    if (isMoveLegal(room, row, position+1, length)) possibleMoves.push_back(make_pair(row, position+1));
    if (isMoveLegal(room, row+1, position+1, length)) possibleMoves.push_back(make_pair(row+1, position+1));
  }else{
    // up left right
    if (isMoveLegal(room, row, position-1, length)) possibleMoves.push_back(make_pair(row, position-1));
    if (isMoveLegal(room, row, position+1, length)) possibleMoves.push_back(make_pair(row, position+1));
    if (isMoveLegal(room, row-1, position-1, length)) possibleMoves.push_back(make_pair(row-1, position-1));
  }
}

int calculateMuseumScore(string s) {
  int score = 0;
  for (int i = 0 ; i < s.length(); ++i) {
    if (s[i] == 'a' || s[i] == 'A') score++;
    if (s[i] == 'b' || s[i] == 'B') score--;
  }
  return score;
}


// 3. Simulate game
int simulate(string current_museum, int current_player, int length, bool is_last_player_stuck = false){

  // 3.1  Get current player row and position
  int current_player_row;
  int current_player_position;
  getCurrentPlayerRowsAndPosition(current_museum, current_player, current_player_row, current_player_position);

  // 3.2 Get current player possible moves
  vector<pair<int, int> > possible_moves;
  getPossibleMoves(current_museum, current_player_row, current_player_position, possible_moves, length);

  if (possible_moves.size() > 0) {
  // 3.3.1 If player can move, simulate all move and select the best score
    int best_score = (current_player == Alma ? -999 : 999);
    for (int i = 0; i < possible_moves.size(); ++i) {
      string new_museum = current_museum;
      new_museum[translateToStringIndex(possible_moves[i].first, possible_moves[i].second)] = current_player == Alma ? 'A' : 'B';
      new_museum[translateToStringIndex(current_player_row, current_player_position)] = current_player == Alma ? 'a' : 'b';
      int next_player = current_player == Alma ? Bertha : Alma;
      int simulated_score = simulate(new_museum, next_player, length);
      best_score = (current_player == 0 ? max(best_score, simulated_score) : min(best_score, simulated_score));
    }
    return best_score;
  } else {
  // 3.3.2 If player cannot move, check whether last player also stuck, else simulate next player
    if (is_last_player_stuck) {
      return calculateMuseumScore(current_museum);
    } else {
      int next_player = current_player == Alma ? Bertha : Alma;
      return simulate(current_museum, next_player, length, true);
    }
  }
}



void solve() {

  // 1. Get input
  int museum_size, a_row, a_position, b_row, b_position, num_construction;
  cin >> museum_size >> a_row >> a_position >> b_row >> b_position >> num_construction;
  a_row--; a_position--; b_row--; b_position--;
  vector<int> construction_row(num_construction);
  vector<int> construction_position(num_construction);
  for(int i = 0; i < num_construction; ++i){
    int row, col;
    cin >> row >> col;
    construction_row[i] = row - 1;
    construction_position[i] = col - 1;
  }

  // 2. Initialize museum
  //    'A' represents current position of Alma
  //    'a' represents room painted by Alma
  //    'B' represents current position of Berthe
  //    'b' represents room painted by Berthe
  //    'c' represents construction room
  //    'f' represents free room
  string museum_status = "";
  for(int i = 0 ; i < museum_size * museum_size; ++i){
    museum_status = museum_status + 'f';
  }
  museum_status[translateToStringIndex(a_row, a_position)] = 'A';
  museum_status[translateToStringIndex(b_row, b_position)] = 'B';
  for (int i = 0; i < num_construction; ++i) {
    museum_status[translateToStringIndex(construction_row[i], construction_position[i])] = 'c';
  }

  // 3. Run game simulation
  int player_round = Alma;
  int result = simulate(museum_status, player_round, museum_size);
  cout  << result << "\n";

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
