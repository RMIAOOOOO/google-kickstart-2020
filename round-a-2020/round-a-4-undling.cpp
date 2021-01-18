#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
using namespace std;

class Node{
  char character;
  int occurrenceCount;
  int depth;
  vector<Node*> childNode;
  Node* parentNode;

public:
  Node (char c, Node* parent, int d) {
    character = c;
    parentNode = parent;
    depth = d;
    childNode.resize(26, nullptr);
    occurrenceCount = 0 ;
  }

  void rootInsertWord(const string &word){
    int firstCharIndex = word[0] - 'A';
    if(childNode[firstCharIndex] == nullptr){
      childNode[firstCharIndex] = new Node(word[0], this, 1);
    }
    childNode[firstCharIndex]->nodeInsertWord(word, 0);
  }

  void nodeInsertWord(const string &word, int index){
//    cout << "nodeInsertWord index " << index << "\n";
    occurrenceCount ++;
    if(index + 1 < word.length()){
      int charIndex = word[index + 1] - 'A';
      if(childNode[charIndex] == nullptr){
        childNode[charIndex] = new Node(word[index + 1], this, depth + 1);
      }
      childNode[charIndex]->nodeInsertWord(word, index + 1);
    }
//    cout << "nodeInsertWord occurrence " << occurrenceCount << "\n";
  }

  int rootGetResult(int K){
    int result = 0;
    for(int i = 0; i < 26; ++i){
      if(childNode[i] != nullptr) result += childNode[i]->nodeGetResult(K);
    }
    return result;
  }

  int nodeGetResult(int K){
    if(occurrenceCount < K){
      return 0;
    }else{
      int childrenResultsSum = 0;
      for(int i = 0; i < 26; ++i){
        if(childNode[i] != nullptr) childrenResultsSum += childNode[i]->nodeGetResult(K);
      }
      int currentNodeEffectiveOccurrence =  ( occurrenceCount / K ) * K;
      int currentNodeScore = ( currentNodeEffectiveOccurrence / K ) * depth ;
      parentNode->minusOccurrence(currentNodeEffectiveOccurrence);
      int score = currentNodeScore + childrenResultsSum;
//      cout << "nodeGetResult occurrenceCount " << occurrenceCount  << "\n";
//      cout << "nodeGetResult character " << character << "\n";
//      cout << "nodeGetResult childrenResultsSum" << childrenResultsSum << "\n";
//      cout << "nodeGetResult currentNodeScore" << currentNodeScore << "\n";
//      cout << "nodeGetResult score " << score << "\n";
      return score;
    }
  }

  void minusOccurrence(int toMinus){
    occurrenceCount -= toMinus;
    if(parentNode != nullptr){
      parentNode->minusOccurrence(toMinus);
    }
  }
};

void solve(){

  // 1. Get input
  int N, K;
  cin >> N >> K;
  vector<string> inputStrings(N);

  for(int i = 0; i < N; ++i){
    string in;
    cin >> in;
    inputStrings[i] = in;
  }
  // 2. Create tree data structure
  Node* tree = new Node(' ', nullptr, 0);

  // 3. Create mailing tree
  for(int i = 0; i < N; ++i){
      tree->rootInsertWord(inputStrings[i]);
    }

  // 4. Tree traversal (DFS) to get result
  int ans = tree->rootGetResult(K);

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
