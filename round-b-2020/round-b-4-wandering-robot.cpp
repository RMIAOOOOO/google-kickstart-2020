#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<math.h>
using namespace std;

void solve(){

  // 1. Input
  int width, height, left, up, right, down;
  cin >> width >> height >> left >> up >> right >> down;

  // 2. List the possible destination
  int urLeft= right + 1;
  int urDown = up - 1;
  int dlRight = left - 1;
  int dlUp = down + 1;

  vector<pair<int, int> > urBlocks(0);
  vector<pair<int, int> > dlBlocks(0);

  int urWidth = width - right;
  int urHeight = up - 1;
  if(urWidth != 0 && urHeight != 0){
    urBlocks.resize(urHeight);
    for(int i = 0 ; i < urHeight; ++i){
      urBlocks[i] = make_pair( urLeft + i , urDown - i );
    }
  }

  reverse(urBlocks.begin(), urBlocks.end());

  int dlWidth = left - 1;
  int dlHeight = height - down;
  if(dlWidth != 0 && dlHeight != 0){
    dlBlocks.resize(dlWidth);
    for(int i = 0 ; i < dlWidth; ++i){
      dlBlocks[i] = make_pair( dlRight - i, dlUp + i);
    }
  }

  reverse(dlBlocks.begin(), dlBlocks.end());

//  cout << "up right  \n";
//  for(int i = 0 ; i < urBlocks.size(); ++i){
//    cout << urBlocks[i].first << " " << urBlocks[i].second << "\n";
//  }
//  cout << "down left  \n";
//  for(int i = 0 ; i < dlBlocks.size(); ++i){
//    cout << dlBlocks[i].first << " " << dlBlocks[i].second << "\n";
//  }

  // 3. For each possible destination, calculate the probability, including the oversafe ones.

  // 3.1 Prepare log2 n!
  vector<double> log2Lookup(width + height);
  log2Lookup[0] = log2(1.0);
  if(max(width,height) > 1) log2Lookup[1] = log2(1.0);
  for(int i = 2; i < log2Lookup.size(); ++i){
    log2Lookup[i] = log2Lookup[i-1] + log2(i);
  }


//  cout << "log2Lookup table\n";
//  for(int i = 0; i < log2Lookup.size(); ++i){
//    cout << log2Lookup[i] << " ";
//  }
//  cout << "\n";

  double urAns = 0;
  for(int i = 0; i < urBlocks.size(); ++i){
    int base = urBlocks[0].first + urBlocks[0].second - 2;
    double log2N = log2Lookup[base];
    int k = i;
    double log2K = log2Lookup[k];
    double log2NmK = log2Lookup[base-k];
    double exp = log2N - log2K - log2NmK - base;
    urAns += pow(2.0, exp);
//    cout << "!" << urAns << " ";
  }

  double dlAns = 0;
  for(int i = 0; i < dlBlocks.size(); ++i){
    int base = dlBlocks[0].first + dlBlocks[0].second - 2;
    double log2N = log2Lookup[base];
    int k = i;
    double log2K = log2Lookup[k];
    double log2NmK = log2Lookup[base-k];
    double exp = log2N - log2K - log2NmK - base;
    dlAns += pow(2.0, exp);
//    cout << "@" << dlAns << " ";
  }
  // 4. Add up the result
  double ans = urAns + dlAns;
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
