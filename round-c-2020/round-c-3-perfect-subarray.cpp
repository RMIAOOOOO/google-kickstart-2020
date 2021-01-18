#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<unordered_map>
using namespace std;

void solve(){

  // 1. get input, keep track of max
  int N;
  cin >> N;
  vector<int> initialNumbers(N);
  vector<int> prefixSum(N);
  int positiveSumLimit = 0;
  int negativeOffset = 0;
  for(int i = 0; i < N; ++i){
    int in;
    cin >> in;
    initialNumbers[i] = in;
    if(i == 0) prefixSum[i] = in;
    else prefixSum[i] = prefixSum[i-1] + in;

    if(in > 0) positiveSumLimit += in;
    else negativeOffset -= in;
  }

  // 2. construct lookup table for square numbers
  vector<int> perfectSquares(1);
  perfectSquares[0] = 0;
  int maxSeed = 1;
  while( maxSeed * maxSeed <= positiveSumLimit){
    perfectSquares.push_back(maxSeed * maxSeed);
    maxSeed ++;
  }
      // maxSeed === length of array

  // 3. Iterate through every number
  vector<int> previousSumMap(negativeOffset + positiveSumLimit + 1, 0);
  previousSumMap[negativeOffset] = 1;
  int ans = 0;

  //    3.1 For every number, calculate the cumulative sum for every perfect square
  for(int i = 0; i < N; ++i){
    for(int j = 0; j <  maxSeed; ++j){
      int  supplementaryNumber = prefixSum[i] - perfectSquares[j] ;
      int accessIndex = negativeOffset + supplementaryNumber;
      if(accessIndex > negativeOffset + positiveSumLimit || accessIndex < 0) continue;
  //    3.2 For every perfect square, lookup the map of previous sums
      ans += previousSumMap[negativeOffset + supplementaryNumber];
    }

  //    3.3 add the number to the map
    int insertIndex = negativeOffset + prefixSum[i];
    previousSumMap[insertIndex] ++;
  }

  // 4. Output the number
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
