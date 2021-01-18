#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
#include<iostream>
using namespace std;

long long LIMIT = 1e9;

void solve(){

  int N, K;
  cin >> N >> K;

  vector<int> inputs(N);
  for(int i = 0; i < N; ++i){
    int in;
    cin >> in;
    inputs[i] = in;
  }

  bool isCurrentlyCountingDown = false;
  int currentlyCountdownValue = K;
  int ans = 0 ;

  for(int i = 0; i < N; ++i){
    if(isCurrentlyCountingDown){
      if(inputs[i] == currentlyCountdownValue){
        currentlyCountdownValue--;
        if(currentlyCountdownValue == 0){
          ans ++;
          isCurrentlyCountingDown = false;
          currentlyCountdownValue = K;
        }
      }else{
        if(inputs[i] == K){
          currentlyCountdownValue = K - 1;
          isCurrentlyCountingDown = true;
        }else{
          isCurrentlyCountingDown = false;
          currentlyCountdownValue = K;
        }
      }
    }else{
      if(inputs[i] == K){
        currentlyCountdownValue = K - 1;
        isCurrentlyCountingDown = true;
      }
    }
  }

  cout << ans << endl;
}

int main(){

  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
