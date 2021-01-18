#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){
  int N, A, B, C;
  cin >> N >> A >> B >> C;
  if( A - C + B - C + C > N) cout << "IMPOSSIBLE" ;
  else if( A == B && B == C && A == 1 && N > 1){
    cout << "IMPOSSIBLE";
  }else if( C != 1){
    vector<int> ans;
    ans.resize(0);
    for(int i = 0; i < A - C; ++i) ans.push_back(N-1);
    ans.push_back(N);
    for(int i = 0; i < N - (A-C+B-C+C); ++i) ans.push_back(1);
    for(int i = 0; i < C-1 ; ++i) ans.push_back(N);
    for(int i = 0; i < B - C; ++i) ans.push_back(N-1);
    for(int i = 0; i < ans.size(); ++i) {
        cout << ans[i];
        if(i != ans.size()-1) cout << " ";
    }
  }else {
    if( A == 1){
      vector<int> ans;
      ans.resize(0);
      ans.push_back(N);
      for(int i = 0; i < N - (A-C+B-C+C); ++i) ans.push_back(1);
      for(int i = 0; i < B - C; ++i) ans.push_back(N-1);
      for(int i = 0; i < ans.size(); ++i) {
          cout << ans[i];
          if(i != ans.size()-1) cout << " ";
      }
    }else{
      vector<int> ans;
      ans.resize(0);
      for(int i = 0; i < A - C; ++i) ans.push_back(N-1);
      for(int i = 0; i < N - (A-C+B-C+C); ++i) ans.push_back(1);
      for(int i = 0; i < C; ++i) ans.push_back(N);
      for(int i = 0; i < B - C; ++i) ans.push_back(N-1);
      for(int i = 0; i < ans.size(); ++i) {
          cout << ans[i];
          if(i != ans.size()-1) cout << " ";
      }
    }
  }
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
