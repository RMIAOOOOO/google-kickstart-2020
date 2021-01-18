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

void solve(){

  int K;
  cin >> K;
  vector<int> A(K);
  for(int i = 0 ; i < K; ++i){
    int in;
    cin >> in;
    A[i] = in;
  }

  int up = 0;
  int down = 0;
  int lastNote = A[0];
  int ans = 0;
  for(int i = 1; i < K; ++i){
    int currentNote = A[i];
    if(currentNote == lastNote) continue;
    if(currentNote > lastNote){
      up ++;
      down = 0;
      if(up >= 4){
        up = 0;
        ans ++;
      }
    }else{
      down ++;
      up = 0;
      if(down >= 4){
        down = 0;
        ans ++;
      }
    }
    lastNote = currentNote;
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
