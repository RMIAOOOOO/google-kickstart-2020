#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

vector<long long> currentConfig;
vector<long long> configSum;

long long getSumFromTo(long long frontIndex, long long backIndex){
  if(frontIndex == 0 ){
    return configSum[backIndex];
  }else{
    return configSum[backIndex] - configSum[frontIndex-1];
  }
}

long long getIndexAtMost(long long targetValue, long long beginIndex, long long endIndex){
  while(1){
    if(beginIndex == endIndex) return beginIndex;
    if(beginIndex + 1 == endIndex){
      if(currentConfig[endIndex] > targetValue && currentConfig[beginIndex] > targetValue) return beginIndex - 1; // exceptional case
      else if(currentConfig[endIndex] > targetValue) return beginIndex;
      else return endIndex;
    }

    int middleIndex = ( beginIndex + endIndex ) / 2;

    if(currentConfig[middleIndex] <= targetValue){
      beginIndex = middleIndex;
    }else{
      endIndex = middleIndex;
    }
  }

}

void solve(){
  // get input
  long long wheel, N;
  cin >> wheel >> N;
  vector<int> preConfig;
  preConfig.resize(wheel);
  long long ln = N;
  long long lw = wheel;
  long long bestCost = ln * lw;
  for(int i = 0 ; i < wheel; ++i){
    int input;
    cin >> input;
    preConfig[i] = input;
  }

  // prepare data: sort currentConfig, prepare configSum
  sort(preConfig.begin(), preConfig.end());

  currentConfig.resize(wheel);
  for(int i = 0; i < wheel; ++i){
    currentConfig[i] = preConfig[i];
  }
  configSum.resize(wheel, 0);
  configSum[0] = currentConfig[0];
  for(int i = 1; i < wheel; ++i){
    configSum[i] = currentConfig[i] + configSum[i-1];
  }

  long long separatingIndexA = 0;
  long long separatingIndexB = 0;


  for(int i = 0 ; i < wheel; ++i){

    if(currentConfig[i] < (N + 1) / 2){

      long long frontCost = currentConfig[i] * (i+1) - getSumFromTo(0, i);

      long long targetValue = currentConfig[i] + N / 2;
      long long separatingIndex = getIndexAtMost(targetValue, separatingIndexA, wheel-1);

      long long backCostOriginal = getSumFromTo(i, separatingIndex) - currentConfig[i] * (separatingIndex - i + 1);
      long long backCostReverse = (separatingIndex == wheel - 1 ? 0 : (N + currentConfig[i]) * (wheel - 1 - separatingIndex) - getSumFromTo(separatingIndex+1, wheel-1));

      long long newCost = frontCost + backCostOriginal + backCostReverse;
      bestCost = min(bestCost, newCost);
      separatingIndexA = separatingIndex;
    }else{

      long long backCost = getSumFromTo(i, wheel-1) - currentConfig[i] * (wheel - i);

      long long targetValue = (currentConfig[i] + N / 2) % N;

      bool hasReversedValue = currentConfig[0] <= targetValue;
      if(hasReversedValue){
        long long separatingIndex = getIndexAtMost(targetValue, separatingIndexB, wheel-1);
        long long frontCostOriginal  = getSumFromTo(0, separatingIndex);
        frontCostOriginal += N * (separatingIndex + 1);
        frontCostOriginal -= currentConfig[i] * (separatingIndex + 1);
        long long frontCostReverse = currentConfig[i] * (i - separatingIndex ) - getSumFromTo(separatingIndex+1, i);

        long long newCost = backCost + frontCostOriginal + frontCostReverse;
        bestCost = min(bestCost, newCost);
        separatingIndexB = separatingIndex;
      }else{
        long long frontCostOriginal = 0;
        long long frontCostReverse = currentConfig[i] * (i+1) - getSumFromTo(0, i);

        long long newCost = backCost + frontCostOriginal + frontCostReverse;
        bestCost = min(bestCost, newCost);
      }

    }
  }

  cout << bestCost << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
