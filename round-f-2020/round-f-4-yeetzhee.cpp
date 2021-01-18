#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<map>
#include<iomanip>
using namespace std;

double calculateBestAverage(vector<int> &currentGroup, int groupLength, int numberOfFace, map<vector<int>, double> &expectedValueHash, vector<int> &targetGroup){

  bool isCompleted = true;
  for(int i = 0 ; i < groupLength; ++i){
    if(currentGroup[i] != targetGroup[i]) isCompleted = false;
  }
  if(isCompleted == true) return 0;

  // 1. create vector of descending cases, sort them
  vector<vector<int> > candidateTargetGroup;
  vector<int> progressIndex;
  int currentOccurrence = currentGroup[0];
  for(int i = 0; i < groupLength; ++i){
    if((i == 0 || currentGroup[i] != currentOccurrence) && currentGroup[i] + 1 <= targetGroup[i]){
      vector<int> newCandidate(groupLength);
      for(int j = 0; j < groupLength; ++j){
        newCandidate[j] = currentGroup[j];
      }
      newCandidate[i] ++;
      currentOccurrence = currentGroup[i];
      candidateTargetGroup.push_back(newCandidate);
      progressIndex.push_back(i);
    }
  }

  // 2. iterate through descending cases
  // 2.1 search from has map, if not found dive in
  // 2,2 calculate expected value by x = 1 + sigma(p i * e i) / sigma (p i)

  double sumPiEi = 0;
  double sumPi = 0;
  double probabilityUnit = 1.0 / numberOfFace;


//  cout << "unit = " << probabilityUnit << endl;
  for(int i = 0; i < candidateTargetGroup.size(); ++i){

    double Ei = 0;
    if(expectedValueHash.find(candidateTargetGroup[i]) != expectedValueHash.end()){
      Ei = expectedValueHash[candidateTargetGroup[i]];
    }else{
      Ei = calculateBestAverage(candidateTargetGroup[i], groupLength, numberOfFace, expectedValueHash, targetGroup);
      expectedValueHash[candidateTargetGroup[i]] = Ei;
    }

    int PiN = 0;
    int currentValuePostUpdate = candidateTargetGroup[i][progressIndex[i]];
    if(currentValuePostUpdate == 1){
      PiN = numberOfFace;
      for(int j = 0; j < groupLength; ++j){
        if(currentGroup[j] != 0){
          PiN --;
        }
      }
    }else{
      for(int j = 0; j < groupLength; ++j){
        if(currentGroup[j] == currentValuePostUpdate - 1){
          PiN ++;
        }
      }
    }

    sumPi += PiN * probabilityUnit;
    sumPiEi += PiN * probabilityUnit * Ei;

  }

  double currentResult = (1.0 + sumPiEi ) / sumPi;

//  cout << "currentCandidate: \n";
//  for(int i = 0; i < candidateTargetGroup.size(); ++i){
//    for(int j = 0; j < groupLength; ++j){
//      cout << candidateTargetGroup[i][j] << " " ;
//    }
//    cout << endl;
//  }
//  cout << "currentResult: " << currentResult << "\n";
  // 3. return


  return currentResult;
}

void solve(){
  int numberOfDice, numberOfFace, numberOfGroup;
  cin >> numberOfDice >> numberOfFace >> numberOfGroup;
  vector<int> targetGroup;
  targetGroup.resize(numberOfGroup, 0);
  for(int i = 0; i < numberOfGroup; ++i){
    int j = 0;
    cin >> j;
    targetGroup[i] = j;
  }
  sort(targetGroup.begin(), targetGroup.end(), greater<int>());

  vector<int> emptySet(numberOfGroup, 0);
  map<vector<int>, double> expectedValueHash;
  double ans = calculateBestAverage(emptySet, targetGroup.size(), numberOfFace, expectedValueHash, targetGroup);

  cout << setprecision(10) << ans << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
