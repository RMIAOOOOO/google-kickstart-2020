
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<unordered_map>
using namespace std;

class SegmentTreeNode{
    int leftBound;
    int rightBound;
    long long sum;
    SegmentTreeNode* leftNode;
    SegmentTreeNode* rightNode;

  public:
    SegmentTreeNode(int l, int r){
      leftBound = l;
      rightBound = r;
      int range = r - l + 1;
      sum = 0;
      if(leftBound != rightBound){
        int leftNodeLeftBound = leftBound;
        int leftNodeRightBound = leftBound + range / 2 - 1; ;
        int rightNodeLeftBound = leftBound + range / 2;
        int rightNodeRightBound = rightBound;
        leftNode = new SegmentTreeNode(leftNodeLeftBound, leftNodeRightBound);
        rightNode = new SegmentTreeNode(rightNodeLeftBound, rightNodeRightBound);
      }else{
        leftNode = nullptr;
        rightNode = nullptr;
      }
    }

    void addNode(int index, long long value){
      sum += value;
      if(leftBound != rightBound){
        int range = rightBound - leftBound + 1;
        int leftNodeRightBound = leftBound + (range / 2) - 1;
        if(index <= leftNodeRightBound){
          leftNode -> addNode(index, value);
        }else{
          rightNode -> addNode(index, value);
        }
      }
    }

    long long getSum(int leftIndex, int rightIndex){
      if(leftIndex <= leftBound && rightIndex >= rightBound){
        return sum;
      }
      if(leftIndex > rightBound) return 0;
      if(rightIndex < leftBound) return 0;
      return leftNode->getSum(leftIndex, rightIndex) + rightNode->getSum(leftIndex, rightIndex);
    }
};



class SegmentTree{
    int treeSize;
    SegmentTreeNode* rootNode;

  public:
    SegmentTree(int s){
      int totalLength = 1;
      while(totalLength < s){
        totalLength *= 2;
      }
      rootNode = new SegmentTreeNode(1, totalLength);
    }

    void addNode(int index, long long value){
      rootNode->addNode(index, value);
    }

    long long getSum(int left, int right){
      return rootNode->getSum(left, right);
    }
};

void solve(){

  // 1. input
  int N, Q;
  cin >> N >> Q;
  vector<int> candies(N);
  vector<char> queriesHeader(Q);
  vector<pair<int,int> > queriesParameters(Q);
  for(int i = 0; i < N; ++i){
    int in;
    cin >> in;
    candies[i] = in;
  }
  for(int i = 0; i < Q; ++i){
    string in;
    int a, b;
    cin >> in >> a >> b;
    queriesHeader[i] = in[0];
    queriesParameters[i] = make_pair(a, b);
  }

  // 2. Create candy cumulative array
  SegmentTree* cumulativeCandiesTree = new SegmentTree(N);
  long long cumulativeSum = 0;
  for(int i = 0; i < N; ++i){
    long long newVal = (i+1) * candies[i] * ( i%2 == 0 ? 1: -1);
    cumulativeCandiesTree->addNode(i+1, newVal);
  }
  // 3. Create normal sum array
  SegmentTree* normalSumTree = new SegmentTree(N);
  for(int i = 0; i < N; ++i){
    long long newVal = candies[i] * (i%2 == 0 ? 1 : -1);
    normalSumTree->addNode(i+1, newVal);
  }

//
//  for(int i = 0; i < N; ++i){
//    cout << cumulativeCandiesTree->getSum(i+1, i+1) << " ";
//  }
//  cout << "\n";
//  for(int i = 0; i < N; ++i){
//    cout << normalSumTree->getSum(i+1, i+1) << " ";
//  }
//  cout << "\n";

  // 4. Add query logic
  long long ans = 0;
  for(int i = 0; i < Q; ++i){
    if(queriesHeader[i] == 'Q'){
      int left = queriesParameters[i].first;
      int right = queriesParameters[i].second;
      long long cumulativeCandy = cumulativeCandiesTree->getSum(left, right);
      long long baseToSubtract = (left - 1) * normalSumTree->getSum(left, right);
      long long queryResult = (left%2 == 0 ? -1 : 1) * (cumulativeCandy - baseToSubtract);
      ans += queryResult;
    }else{
      int index = queriesParameters[i].first;
      int newValue = queriesParameters[i].second;
      int valueDifference = newValue - candies[index-1];
      candies[index-1] = newValue;
      int candyUpdateQuantity = valueDifference * (index) * (index%2 == 0? -1: 1);
      cumulativeCandiesTree->addNode(index, candyUpdateQuantity );
      int sumUpdateQuantity = valueDifference * (index%2 == 0? -1: 1);
      normalSumTree->addNode(index, sumUpdateQuantity);
    }
  }

//
//  for(int i = 0; i < N; ++i){
//    cout << cumulativeCandiesTree->getSum(i+1, i+1) << " ";
//  }
//  cout << "\n";
//  for(int i = 0; i < N; ++i){
//    cout << normalSumTree->getSum(i+1, i+1) << " ";
//  }
//  cout << "\n";

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
