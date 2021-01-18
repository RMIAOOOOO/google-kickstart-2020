#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

int translateToStringIndex(int row, int col){
  return row * row + col;
}

int getCurrentPlayerRowsAndPosition(string currentState, int round){
  int targetChar = (round == 0 ? 'A' : 'B');
  int index = 0;
  for(int i = 0; i < currentState.length(); ++i){
    if(currentState[i] == targetChar) {
      index = i;
      break;
    }
  }
//  cout << "index: " << index << "\n";
  int row = 0;
  while((row+1)*(row+1)-1 < index) row++;
  int col = index - row*row;
  return row*100+col;
}


bool isRoomLegal(string room, int row, int position, int length){
    if(row < 0 || row >= length) return false;
    if(position < 0 || position >= row * 2 + 1) return false;
    if(room[translateToStringIndex(row, position)] != 'f') return false;
    return true;
  }

void getPossibleMoves(string room, int row, int position, vector<pair<int, int> > &possibleMoves, int length){
    if(position % 2 == 0){
      // left right down
      if(isRoomLegal(room, row, position-1, length)) possibleMoves.push_back(make_pair(row, position-1));
      if(isRoomLegal(room, row, position+1, length)) possibleMoves.push_back(make_pair(row, position+1));
      if(isRoomLegal(room, row+1, position+1, length)) possibleMoves.push_back(make_pair(row+1, position+1));
    }else{
      // up left right
      if(isRoomLegal(room, row, position-1, length)) possibleMoves.push_back(make_pair(row, position-1));
      if(isRoomLegal(room, row, position+1, length)) possibleMoves.push_back(make_pair(row, position+1));
      if(isRoomLegal(room, row-1, position-1, length)) possibleMoves.push_back(make_pair(row-1, position-1));
    }
  }

int calculateScore(string s){
  int score = 0;
  for(int i = 0 ; i < s.length(); ++i){
    if(s[i] == 'a' || s[i] == 'A') score++;
    else if(s[i] == 'b' || s[i] == 'B') score--;
  }
  return score;
}

int simulate(string currentMuseum, int playerRound, int length){
//  cout << "current state: " << currentMuseum << "\n";
  int pp = getCurrentPlayerRowsAndPosition(currentMuseum, playerRound);
  int playerRow = pp/100;
  int playerPosition = pp%100;
//  cout << "playerRow      " << playerRow << "\n";
//  cout << "playerPosition " << playerPosition<< "\n";

  vector<pair<int, int> > possibleMoves;
  getPossibleMoves(currentMuseum, playerRow, playerPosition, possibleMoves, length);

//  cout << "possible moves:\n";
//  for(int i = 0; i < possibleMoves.size(); ++i){
//      cout << possibleMoves[i].first << " " << possibleMoves[i].second << "\n";
//    }

  if(possibleMoves.size() == 0){
    playerRound = playerRound == 0 ? 1 : 0;
    int pp = getCurrentPlayerRowsAndPosition(currentMuseum, playerRound);
    int nextPlayerRow = pp/100;
    int nextPlayerPosition = pp%100;
    vector<pair<int, int> > nextPlayerPossibleMoves;
    getPossibleMoves(currentMuseum, nextPlayerRow, nextPlayerPosition, nextPlayerPossibleMoves, length);

//      cout << "next player possible moves:\n";
//      for(int i = 0; i < nextPlayerPossibleMoves.size(); ++i){
//        cout << nextPlayerPossibleMoves[i].first << " " << nextPlayerPossibleMoves[i].second << "\n";
//      }
    if(nextPlayerPossibleMoves.size() == 0){
//         cout << "no way here, calculating possible score: " << calculateScore() << "\n";
       return calculateScore(currentMuseum);
    }
    int bestScore = (playerRound == 0 ? -999 : 999);
    for(int i = 0; i < nextPlayerPossibleMoves.size(); ++i){
      string newMuseum = currentMuseum;
//        cin >> b; //debug
      newMuseum[translateToStringIndex(nextPlayerPossibleMoves[i].first, nextPlayerPossibleMoves[i].second)] = playerRound == 0 ? 'A' : 'B';
      newMuseum[translateToStringIndex(nextPlayerRow, nextPlayerPosition)] = playerRound == 0 ? 'a' : 'b';
      int nextRound = (playerRound == 0 ? 1 : 0);
      int simulatedScore = simulate(newMuseum, nextRound, length);
      bestScore = (playerRound == 0 ? max(bestScore, simulatedScore) : min(bestScore, simulatedScore));
    }
    return bestScore;
  }else{
    int bestScore = (playerRound == 0 ? -999 : 999);
    for(int i = 0; i < possibleMoves.size(); ++i){
      string newMuseum = currentMuseum;
//        int b; //debug
//        cin >> b; //debug
      newMuseum[translateToStringIndex(possibleMoves[i].first, possibleMoves[i].second)] = playerRound == 0 ? 'A' : 'B';
      newMuseum[translateToStringIndex(playerRow, playerPosition)] = playerRound == 0 ? 'a' : 'b';
      int nextRound = (playerRound == 0 ? 1 : 0);
      int simulatedScore = simulate(newMuseum, nextRound, length);
      bestScore = (playerRound == 0 ? max(bestScore, simulatedScore) : min(bestScore, simulatedScore));
    }
    return bestScore;
  }
}





void solve(){

  // input
  int S, ARow, APosition, BRow, BPosition, numOfConstruction;
  cin >> S >> ARow >> APosition >> BRow >> BPosition >> numOfConstruction;
  ARow--; APosition--; BRow--; BPosition--;
  vector<pair<int, int> > construction;
  construction.resize(0);
  for(int i = 0; i < numOfConstruction; ++i){
    int row, col;
    cin >> row >> col;
    construction.push_back(make_pair(row-1, col-1));
  }


  // 1. initialize museum
  //  Museum museum(S, ARow, APosition, BRow, BPosition, construction);

  string museum = "";
  for(int i = 0 ; i < S * S; ++i){
    museum = museum + 'f';
  }
  museum[translateToStringIndex(ARow, APosition)] = 'A';
  museum[translateToStringIndex(BRow, BPosition)] = 'B';
  for(int i = 0; i < numOfConstruction; ++i){
    museum[translateToStringIndex(construction[i].first, construction[i].second)] = 'c';
  }
  //  cout << museum;
  int playerRound = 0;

  // 2. initialize broad status
  int result = simulate(museum, playerRound, S);

//  int bestScore = 0;
  // 3. explore all possible solutions in museum
  //    a. while there is still room to move, simulate next steps, record status
  //    b. check if no steps can be made, if no steps can be made, record the bestScore
  //    c. recursively call explore all possible solutions in museum
//  int result = museum.simulate();
//  cout << "answer: ";
  cout  << result;
  // 4. print the best Score

  cout << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
