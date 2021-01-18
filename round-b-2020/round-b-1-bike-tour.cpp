#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){

  int N;
  cin >> N;
  vector<int> heights(N);
  for(int i = 0; i < N; ++i){
    int in;
    cin >> in;
    heights[i] = in;
  }

  int ans = 0;
  for(int i = 1; i < N - 1; ++i){
    if(heights[i] > heights[i-1] && heights[i] > heights[i+1]){
      ans ++;
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
