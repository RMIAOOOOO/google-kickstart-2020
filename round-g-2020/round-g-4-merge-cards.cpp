#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<unordered_map>
#include<iomanip>
using namespace std;

void solve(){
  // 1. Get input
  int N;
  cin >> N;
  vector<int> cards(N);
  for(int i = 0; i < N; ++i){
    int in;
    cin >> in;
    cards[i] = in;
  }
  // 2. Create lookup table for probability
  vector<vector<double> > probabilityLookup(N);
  for(int i = 0; i < N; ++i){
    probabilityLookup[i].resize(N, 0);
  }
  probabilityLookup[0][0] = 0;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j+i < N; ++j){
      double leftSenario = i == 0 ? 0 : 1;
      double rightSenario = j == 0 ? 0 : 1;
      double remainingLeft = i - leftSenario;
      double remainingRight = j - rightSenario;
      if(i == 0 && j == 0){
        continue;
      }else if( i == 0){
        double rightExpect = rightSenario * (1+probabilityLookup[i][j-1]);
        double remainingRightProb = remainingRight * probabilityLookup[i][j-1];
        probabilityLookup[i][j] = (rightExpect + remainingRightProb) / (i+j);
      }else if( j == 0){
        double leftExpect = leftSenario * (1+probabilityLookup[i-1][j]);
        double remainingLeftProb = remainingLeft * probabilityLookup[i-1][j];
        probabilityLookup[i][j] = (leftExpect + remainingLeftProb) / (i+j);
      }else{
        double rightExpect = rightSenario * (1+probabilityLookup[i][j-1]);
        double leftExpect = leftSenario * (1+probabilityLookup[i-1][j]);
        double remainingRightExpect = remainingRight * probabilityLookup[i][j-1];
        double remainingLeftExpect = remainingLeft * probabilityLookup[i-1][j];
        probabilityLookup[i][j] = (rightExpect + leftExpect + remainingRightExpect + remainingLeftExpect) / (i+j);
      }
    }
  }
  // 3. Iterate through the lookup table to get the probability
  double ans = 0;
  for(int i = 0; i < N; ++i){
    ans += cards[i] * probabilityLookup[i][N-1-i];
  }
  // 4. Ans
  cout << setprecision(10) << ans << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
