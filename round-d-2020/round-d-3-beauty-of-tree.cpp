#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<limits>
using namespace std;

typedef std::numeric_limits< double > dbl;

void solve(){

  // prepare data
  int N, A, B;
  vector<int> parents;
  vector<vector<int> > childNodes;

  cin >> N >> A >> B;
  parents.resize(N);
  parents[0] = -1;
  for(int i = 1; i < N; ++i){
    int input;
    cin >> input;
    input--;
    parents[i] = input;
  }
  childNodes.resize(N);
  for(int i = 0; i < N; ++i) childNodes[i].resize(0);
  for(int i = 1; i < N; ++i){
    childNodes[parents[i]].push_back(i);
  }


  // tree traversal
  vector<int> nextTraversal;
  vector<int> pathRecord;
  vector<long long> Acount;
  vector<long long> Bcount;
  vector<long long> ABcount;

  int currentNode = 0;

  nextTraversal.resize(N, 0);
  pathRecord.resize(1, 0);
  Acount.resize(N, 0);
  Bcount.resize(N, 0);
  ABcount.resize(N, 0);

  while(currentNode >= 0){
    int subpathSize = childNodes[currentNode].size();
    if(subpathSize > nextTraversal[currentNode]){
      int nextNode = childNodes[currentNode][nextTraversal[currentNode]];
      nextTraversal[currentNode] ++;
      pathRecord.push_back(nextNode);
      currentNode = nextNode;
    }else{
      Acount[currentNode] ++;
      Bcount[currentNode] ++;
      int pathSize = pathRecord.size();
      if(pathSize - A > 0) Acount[pathRecord[pathSize - 1 - A]] += Acount[currentNode];
      if(pathSize - B > 0) Bcount[pathRecord[pathSize - 1 - B]] += Bcount[currentNode];
      pathRecord.resize(pathRecord.size()-1);
      currentNode = parents[currentNode];
    }

  }

  for(int i = 0 ; i < N; ++i){
    ABcount[i] = Acount[i] * Bcount[i];
  }

  long long ASum = 0;
  long long BSum = 0;
  long long ABSum = 0;

  for(int i = 0 ; i < N; ++i){
    ASum += Acount[i];
    BSum += Bcount[i];
    ABSum += ABcount[i];
  }

  double ASumD = ASum;
  double BSumD = BSum;
  double ABSumD = ABSum;
  double ans = ASumD / N + BSumD / N - ABSumD / N / N ;

  cout.precision(dbl::max_digits10);

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
