#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include <sstream>
#include <queue>
#include <iostream>
using namespace std;

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    int numOfStack, numPlatePerStack, numPlateToTake;
    cin >> numOfStack >> numPlatePerStack >> numPlateToTake;
    vector< vector<double> > cumScore;
    cumScore.clear();
    cumScore.resize(numOfStack);
    for(int j = 0; j < numOfStack; ++j){
      cumScore[j].clear();
      cumScore[j].resize(numPlatePerStack);
    }
    for(int j = 0; j < numOfStack; ++j){
      double cumu = 0;
      for(int k = 0; k < numPlatePerStack; ++k){
        int input = 0;
        cin >> input;
        cumu += input;
        cumScore[j][k] = cumu;
      }
    }


    for(int j = 0; j < numOfStack; ++j){
        for(int k = 0; k < numPlatePerStack; ++k){
//          cout << cumScore[j][k] << " ";
        }
      }



    vector<double> bestAvailable;
    bestAvailable.clear();
    bestAvailable.resize(numPlateToTake+1, 0);

    double ans = 0;
    for(int j = 0; j < numOfStack; ++j){
      vector<double> nextBest ;
      nextBest.clear();
      nextBest.resize(numPlateToTake+1, 0);
      for(int k = 0; k < numPlatePerStack; ++k){
        if(k+1 <= numPlateToTake){
          for(int l = 0; l < numPlateToTake; ++l){
            int cost = k+1 + l;
            if(cost <= numPlateToTake){
              double trial = cumScore[j][k] + bestAvailable[l];
//              cout << j << " " << k << " " << cumScore[j][k]<< " " << bestAvailable[l] << " " << cost << " "  << trial << "\n";
              if(trial > bestAvailable[cost]) {
                nextBest[cost] = max(nextBest[cost], trial);
                ans = max(ans, trial);
              }
            }
          }
        }else{
          break;
        }
      }
      for(int z = 0; z < numPlateToTake+1; ++z){
        bestAvailable[z] = max(bestAvailable[z], nextBest[z]);
      }
    }


    cout << "Case #" << i+1 <<": " << ans << "\n";
  }
}
