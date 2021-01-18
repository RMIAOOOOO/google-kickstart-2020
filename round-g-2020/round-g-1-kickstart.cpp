#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){
  string S;
  cin >> S;
  vector<char> notedown;
  notedown.resize(S.length(), ' ');
  if(S.length() <= 6){
    cout << "0\n";
  }else {
    for(int i = 0 ; i < S.length() - 3; ++i){
      if(S[i] == 'K' && S[i+1] == 'I' && S[i+2] == 'C' && S[i+3] == 'K') notedown[i] = 'K';
    }
    for(int i = 0 ; i < S.length() - 4; ++i){
      if(S[i] == 'S' && S[i+1] == 'T' && S[i+2] == 'A' && S[i+3] == 'R'&& S[i+4] == 'T') notedown[i] = 'S';
    }
    int ans = 0;
    int Kcount = 0;
    for(int i = 0; i < S.length()-3; ++i){
      if(notedown[i] == 'K'){
        Kcount ++;
      }else if(notedown[i] == 'S'){
        ans += Kcount;
      }
    }
    cout << ans << "\n";
  }
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
