#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
#include<iostream>
#include<unordered_set>
using namespace std;

long long LIMIT = 1e9;

void solve(){

  int N;
  cin >> N;
  vector<int> V(N);
  for(int i = 0 ; i < N; ++i){
    int in;
    cin >> in;
    V[i] = in;
  }

  int ans = 0;
  int historyHigh = -1;

  for(int i = 0; i < N; ++i){
    if(V[i] > historyHigh && (i == N-1 || V[i] > V[i+1]) ){
      ans ++;
    }
    historyHigh = max(historyHigh, V[i]);
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
