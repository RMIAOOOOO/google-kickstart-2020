#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){

  long long N, D;
  cin >> N >> D;
  vector<long long> intervals(N);
  for(int i = 0; i < N; ++i){
    long long in;
    cin >> in;
    intervals[i] = in;
  }

  long long ans = D;
  for(int i = N - 1; i >= 0 ; --i){
    ans -= ans % intervals[i];
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
