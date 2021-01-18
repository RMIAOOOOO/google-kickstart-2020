#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){
  int squareLength;
  cin >> squareLength;
  vector< vector<int> > square;
  square.resize(squareLength);
  for(int i = 0 ; i < squareLength; ++i){
    square[i].resize(squareLength);
    for(int j = 0 ; j < squareLength; ++j){
      int input;
      cin >> input;
      square[i][j] = input;
    }
  }
  long int ans = 0;
  for(int i = 0 ; i < squareLength - 1 ; ++i ){
    int numberOfElement = i+1;
    long int sum = 0;
    for(int j = 0 ; j < numberOfElement; ++j){
      int row = squareLength - i + j -1;
      int col = j;
      sum += square[row][col];
    }
    ans = max(sum, ans);
  }


  long int sum2 = 0;
  for(int j = 0 ; j < squareLength; ++j){
    int row = j;
    int col = j;
    sum2 += square[row][col];
  }
  ans = max(sum2, ans);

  for(int i = 0 ; i < squareLength - 1 ; ++i ){
    int numberOfElement = i+1;
    long int sum = 0;
    for(int j = 0 ; j < numberOfElement; ++j){
      int row = j;
      int col = squareLength + j - i -1;
      sum += square[row][col];
    }
    ans = max(sum, ans);
  }


  cout << ans << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
