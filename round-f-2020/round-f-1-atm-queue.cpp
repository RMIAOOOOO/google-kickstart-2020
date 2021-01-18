#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){
  int numberOfPeople, maximumWithdraw = 0;
  vector<pair<int, int> > que;
  cin >> numberOfPeople >> maximumWithdraw;
  que.resize(numberOfPeople);
  for(int i = 0; i < numberOfPeople; ++i){
    int input;
    cin >> input;
    int round = (input-1) / maximumWithdraw;
    que[i] = make_pair(round, i);
  }
  sort(que.begin(), que.end());
  for(int i  = 0; i < numberOfPeople; ++i){
    cout << que[i].second + 1;
    if(i != numberOfPeople - 1) cout << " " ;
  }
  cout << "\n";

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
