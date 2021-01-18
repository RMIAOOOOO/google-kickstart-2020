#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

class Compare{
public:
  bool operator() (pair<long long, long long> a, pair<long long, long long> b){
    return a.first + a.second < b.first + b.second;
  }
};

void solve(){

  // get input
  int numberOfToys;
  vector<pair<long long, long long> > toysVector;
  cin >> numberOfToys;
  long long bestScore = 0;
  long long roundTime = 0;
  for(int i = 0; i < numberOfToys; ++i){
    long long enjoy, remember;
    cin >> enjoy >> remember;
    bestScore += enjoy;
    roundTime += enjoy;
    toysVector.push_back(make_pair(enjoy, remember));
  }

  // calculate initial best value;
  priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, Compare> pq;

  int removedToysCount = 0;
  int bestRemovedToysCount = 0;
  long long trialScore = bestScore;
  for(int i = 0; i < numberOfToys; ++i){
    long long enjoy = toysVector[i].first;
    long long remember = toysVector[i].second;
    if(roundTime - enjoy < remember) {
//      cout << "a";
      removedToysCount ++;
      roundTime -= toysVector[i].first;
      trialScore -=  toysVector[i].first;
      while(!pq.empty() && pq.top().first + pq.top().second > roundTime){
//        cout << "b";
        trialScore -= pq.top().first * 2;
        roundTime -= pq.top().first;
        pq.pop();
        removedToysCount ++;
      }
    }else{
//      cout << "c";
      trialScore += toysVector[i].first;
      if(trialScore > bestScore)bestRemovedToysCount = removedToysCount;
      bestScore = max(bestScore, trialScore);
      pq.push(make_pair(toysVector[i].first, toysVector[i].second));
    }
  }

  // check for possible infinite solution;
  if(!pq.empty()) {
    cout << removedToysCount << " " << "INDEFINITELY"<< "\n";
    return;
  } else{
    cout << bestRemovedToysCount << " " << bestScore << "\n";
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
