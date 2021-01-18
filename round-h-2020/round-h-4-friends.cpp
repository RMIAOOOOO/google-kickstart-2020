#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<map>
using namespace std;

int getCost(int firstCharIndex, int secondCharIndex, const vector<vector<bool> > &namesMapping){
  if(firstCharIndex == secondCharIndex) return 0;
  vector<bool> explored(26, false);
  queue<int> queuedIndex;
  int depth = 1;
  explored[firstCharIndex] = true;
  for(int i = 0; i < 26; ++i){
    if(namesMapping[firstCharIndex][i] == 1 && i != firstCharIndex ){
      queuedIndex.push(i);
      explored[i] = true;
    }
  }
  while(!queuedIndex.empty()){
    queue<int> newQueue;
    while(!queuedIndex.empty()){
      int currentIndex = queuedIndex.front();
      if(currentIndex == secondCharIndex) return depth;
      queuedIndex.pop();
      explored [currentIndex] = true;
      for(int i = 0; i < 26; ++i){
        if(!explored[i] && namesMapping[currentIndex][i] == true){
          newQueue.push(i);
          explored[i] = true;
        }
      }
    }
    depth ++;

    while(!newQueue.empty()){
      int newIndex = newQueue.front();
      newQueue.pop();
      queuedIndex.push(newIndex);
    }
  }
  return 999;
};

void solve(){

  // 1. Get Input
  int N, Q;
  cin >> N >> Q ;


  vector<string> names(N);
  vector<pair<int, int> > queries(Q);
  for(int i = 0 ; i < N; ++i){
    string in;
    cin >> in;
    names[i] = in;
  }

  for(int i = 0 ; i < Q; ++i){
    int a, b;
    cin >> a >> b;
    queries[i] = make_pair(a-1, b-1);
  }

  // 2. Create 26 * 26 friend list
  vector<vector<bool> > namesMapping(26);
  for(int i = 0; i < 26; ++i){
    namesMapping[i].resize(0);
    namesMapping[i].resize(26, 0);
  }

  // 2.5 Create character to character cost table
  vector<vector<int> > characterToCharacterLookupTable(26);
  for(int i = 0; i < 26; ++i){
    characterToCharacterLookupTable[i].resize(0);
    characterToCharacterLookupTable[i].resize(26, 999);
  }


  for(int i = 0; i < N; ++i){
    int nameLen = names[i].length();
    for(int j = 0; j < nameLen - 1; ++ j){
      for(int k = j; k < nameLen; ++ k){
        int firstCharIndex = names[i][j] - 'A';
        int secondCharIndex = names[i][k] - 'A';
        namesMapping[firstCharIndex][secondCharIndex] = 1;
        namesMapping[secondCharIndex][firstCharIndex] = 1;
      }
    }
  }

  for(int i = 0; i < 26; ++i){
      for(int j = 0; j < 26; ++j){
          characterToCharacterLookupTable[i][j] = getCost(i, j, namesMapping);
      }
  }

  for(int i = 0; i < 26; ++i){
      for(int j = 0; j < 26; ++j){
          //cout << characterToCharacterLookupTable[i][j] << " ";
      }
      //cout << "\n";
  }

  // 3. for every name, BFS every pair of words, output the shortest path
  for(int i = 0; i < Q; ++i){
    string firstPerson = names[queries[i].first];
    string secondPerson = names[queries[i].second];
    int firstLen = firstPerson.length();
    int secondLen = secondPerson.length();
    int bestScore = 999;
    for(int j = 0; j < firstLen; ++j){
      for(int k = 0; k < secondLen; ++k){
        int firstCharIndex = firstPerson[j] - 'A';
        int secondCharIndex = secondPerson[k] - 'A';
        int cost = characterToCharacterLookupTable[firstCharIndex][secondCharIndex];
        bestScore = min(cost, bestScore);
      }
    }
    if(bestScore == 999 ) cout << -1 << " ";
    else {
      cout << bestScore + 2  << " ";
    }

  }
  cout << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
