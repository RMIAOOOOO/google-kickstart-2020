#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){

  // 1. Get Input
  int N;
  cin >> N;
  vector<long> XCoord(N);
  vector<long> YCoord(N);
  for(int i = 0; i < N; ++i){
    int inX, inY;
    cin >> inX >> inY;
    long long longX = inX;
    long long longY = inY;
    XCoord[i] = longX;
    YCoord[i] = longY;
  }

  // 2. get row
  long long sumY = 0;

  int midIndex = N / 2;
  sort(YCoord.begin(), YCoord.end());
  long long finalY = YCoord[midIndex];
  for(int i = 0; i < N; ++i){
    long long individualCost = abs(YCoord[i] - finalY);
    sumY += individualCost;
  }

  // 3. get col
  long long sumX = 0;

  sort(XCoord.begin(), XCoord.end());
  for(int i = 0; i < N; ++i){
    XCoord[i] -= i;
  }
  sort(XCoord.begin(), XCoord.end());
  long long finalX = XCoord[midIndex];
  for(int i = 0; i < N; ++i){
    long long individualCost = abs(XCoord[i] - (finalX));
    sumX += individualCost;
  }

  // 4. calculate cost
  long long ans = sumX + sumY;
  cout << ans << "\n";


}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
