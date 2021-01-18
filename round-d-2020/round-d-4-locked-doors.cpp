#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
#include<iostream>
#include<math.h>
#include<memory>
using namespace std;

class Node{
public:
  Node* leftNode;
  Node* rightNode;
  Node* parentNode;
  int subTreeCount;
  int index;
  int value;

  Node(){
    leftNode = nullptr;
    rightNode = nullptr;
    parentNode = nullptr;
    subTreeCount = 0;
    index = 0;
    value = 0;
  }

  int DFSAddWeight(){
    int weight = 1;
    if(leftNode != nullptr){
      weight += leftNode->DFSAddWeight();
    }
    if(rightNode != nullptr){
      weight += rightNode->DFSAddWeight();
    }
    subTreeCount = weight;
    return weight;
  }
};

void solve(){
  // 1. Get input
  int N, Q;
  cin >> N >> Q;
  vector<int> difficulties(N-1);
  vector<pair<int, int> > queires(Q);
  for(int i = 0; i < N - 1; ++i ){
    int in;
    cin >> in;
    difficulties[i] = in;
  }
  for(int i = 0 ; i < Q; ++i){
    int start, step;
    cin >> start >> step;
    queires[i] = make_pair(start, step);
  }


  // 2. Left, right, and i
  vector<int> leftNext(N - 1);
  stack<int> leftMaxStack;
  for(int i = 0; i < N - 1 ; ++i){
    while(leftMaxStack.size() > 0){
      if(difficulties[i] > difficulties[leftMaxStack.top()]){
        leftMaxStack.pop();
      }else{
        break;
      }
    }
    if(leftMaxStack.size() == 0){
      leftNext[i] = -1;
    }else{
      leftNext[i] = leftMaxStack.top();
    }
    leftMaxStack.push(i);
  }

  vector<int> rightNext(N - 1);
  stack<int> rightMaxStack;
  for(int i = N-2; i >= 0; --i){
    while(rightMaxStack.size() > 0){
      if(difficulties[i] > difficulties[rightMaxStack.top()]){
        rightMaxStack.pop();
      }else{
        break;
      }
    }
    if(rightMaxStack.size() == 0){
      rightNext[i] = -1;
    }else{
      rightNext[i] = rightMaxStack.top();
    }
    rightMaxStack.push(i);
  }

  vector<int> next(N - 1);
  for(int i = 0 ; i < N - 1; ++i){
    if(rightNext[i] == -1 && leftNext[i] == -1){
      next[i] = -1;
    }else if(rightNext[i] == -1){
      next[i] = leftNext[i];
    }else if(leftNext[i] == -1){
      next[i] = rightNext[i];
    }else{
      next[i] = (difficulties[leftNext[i]] > difficulties[rightNext[i]]) ? rightNext[i] : leftNext[i];
    }
  }

  // 3. Tree construction
  Node* nodes = new Node[N-1]();
  int rootNodeIndex = -1;
  for(int i = 0; i < N - 1; ++i){
    nodes[i].index = i;
    nodes[i].value = difficulties[i];
    if(next[i] != -1){
      nodes[i].parentNode = &nodes[next[i]];
      if(i > next[i]){
        nodes[next[i]].rightNode = &nodes[i];
      }else{
        nodes[next[i]].leftNode = &nodes[i];
      }
    }else{
      rootNodeIndex = i;
    }
  }

  // 4. Tree weight construction
  nodes[rootNodeIndex].DFSAddWeight();

  // 5. Binary step tree search construction
  vector<vector<int> > parentLookup(N-1);
  int lookupLength = 1; // N-1 = 5, lookup length = 2
  while(pow(2, lookupLength) <= (N - 1) - 1){
    lookupLength ++;
  }
  for(int i = 0; i < N - 1; ++i){
    parentLookup[i].resize(lookupLength, -1);
  }
  for(int i = 0; i < lookupLength; ++i){
    for(int j = 0; j < N - 1; ++j){
      if(i == 0){
        if(nodes[j].parentNode != nullptr){
          parentLookup[j][i] = nodes[j].parentNode->index;
        }
      }else{
        int stepsUpwards = i - 1;
        if(parentLookup[j][stepsUpwards] != -1){
          int parIndex = parentLookup[j][stepsUpwards];
          parentLookup[j][i] = parentLookup[parIndex][stepsUpwards];
        }
      }
    }
  }

//  for(int i = 0 ; i < N - 1; ++i){
//    for(int j = 0; j < lookupLength; ++j){
//      cout << parentLookup[i][j] << " ";
//    }
//    cout << endl;
//  }
//  cout << endl;

  // 6. input case
  for(int i = 0; i < Q; ++i){
    int room = queires[i].first;
    int step = queires[i].second;
    if(step == 1){
      cout << room << " ";
      continue;
    }else{
      int firstDoor;
      if(room == 1){
        firstDoor = 0;
      }else if( room == N){
        firstDoor = N-2;
      }else{
        firstDoor = difficulties[room-2] > difficulties[room-1] ? room-1 : room-2;
      }
      if(nodes[firstDoor].subTreeCount + 1 >= step ){
        bool firstStepRight = firstDoor == room - 1 ;
        if(firstStepRight){
            cout << room + step -1 << " ";
        }else{
            cout << room - step + 1 << " ";
        }
      }else{
        int upwardFirstDoor = firstDoor;
//        cout << "(upwardFirstDoor original) " << upwardFirstDoor << ". " << endl;
        for(int k = lookupLength - 1; k >= 0; --k){
            // find the room such that the current node can be finished but need to go up for next step
            // room = 8, next sub = 4.5.6 go up
            // room = 8, next sub = 7.8.9 stay
          if(parentLookup[upwardFirstDoor][k] != -1 && nodes[parentLookup[upwardFirstDoor][k]].subTreeCount < step - 1){
            upwardFirstDoor = parentLookup[upwardFirstDoor][k];
          }
        }
//        cout << "(upwardFirstDoorIndex) " << upwardFirstDoor << ". " << endl;

        int currentNodeSubDoor = nodes[upwardFirstDoor].subTreeCount;
        int residualSteps = step - currentNodeSubDoor - 1;
        bool rightToLeft = nodes[upwardFirstDoor].parentNode->index < firstDoor;
        if(rightToLeft ){
          // before: room 3 residual step = 2
          int beforeEnterRoomNumber = nodes[upwardFirstDoor].parentNode->index+2;
            cout << beforeEnterRoomNumber - residualSteps << " ";
        }else{
          int beforeEnterRoomNumber = nodes[upwardFirstDoor].parentNode->index+1;
          int remainingRoom = room - beforeEnterRoomNumber;
            cout << beforeEnterRoomNumber + residualSteps << " ";
        }

      }
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
