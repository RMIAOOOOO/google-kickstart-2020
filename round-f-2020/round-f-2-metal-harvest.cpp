#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

void solve(){

  int numberOfIntervals, maximumHarvest;
  cin >> numberOfIntervals >> maximumHarvest;
  vector<pair<int, int> > que;
  que.resize(numberOfIntervals);
  for(int i = 0; i < numberOfIntervals; ++i){
    int startTime, endTime;
    cin >> startTime >> endTime;
    int cost = endTime - startTime;
    que[i] = make_pair(startTime, cost);
  }
  sort(que.begin(), que.end());
  int answer = 0;
  int lastEnd = que[0].first;
  for(int i = 0; i < numberOfIntervals; ++i){
    if(lastEnd >= que[i].first + que[i].second){
      continue;
    }
    int newStart = max(lastEnd, que[i].first);

    int newCost = 0;
    if (lastEnd > que[i].first){
      newCost = que[i].second - (lastEnd - que[i].first);
    } else {
      newCost = que[i].second;
    }

    int thisRoundDeploy = ((newCost - 1) / maximumHarvest) + 1;
    answer += thisRoundDeploy;
    lastEnd = newStart + (thisRoundDeploy * maximumHarvest);
  }

  cout << answer << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
