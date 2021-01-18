#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){
  long long N, K, S;
  cin >> N >> K >> S;
  long long ans = K - 1 + 1 + N;
  ans = min(ans, K - 1 + K - S + N - S + 1);
  cout << ans << "\n";
//  cout << ans << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
