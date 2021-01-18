#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
#include<iostream>
using namespace std;

long long LIMIT = 1e9;

void solve(){

  string instruction;
  cin >> instruction;

  long long currentFactor = 0;
  long long ansX = 0;
  long long ansY = 0;

  stack<long long> factors;

  for(int i = 0; i < instruction.length(); ++i){
//    cout << i << " " << ansX << " " << ansY << endl;
    if(instruction[i] >= '0' && instruction[i] <= '9'){
      int currentDigit = instruction[i] - '0';
      currentFactor = (currentFactor * 10) % LIMIT;
      currentFactor += currentDigit;
    }else{
      long long currentMultiplier = currentFactor == 0 ? 1 : currentFactor;
      long long backgroundMultiplier = factors.empty() ? 1 : factors.top();
      long long multiplier = (currentMultiplier * backgroundMultiplier) % LIMIT;
      if(instruction[i] == '('){
        factors.push(multiplier);
        currentFactor = 0;
      }else if(instruction[i] == ')'){
        factors.pop();
      }else if(instruction[i] == 'E'){
        ansX = ( ansX + multiplier ) % LIMIT;
        currentFactor = 0;
      }else if(instruction[i] == 'W'){
        ansX = ( LIMIT + ansX - multiplier ) % LIMIT;
        currentFactor = 0;
      }else if(instruction[i] == 'S'){
        ansY = ( ansY + multiplier ) % LIMIT;
        currentFactor = 0;
      }else if(instruction[i] == 'N'){
        ansY = ( LIMIT + ansY - multiplier ) % LIMIT;
        currentFactor = 0;
      }
    }
  }

  cout << ansX + 1 << " " << ansY + 1 << endl;
}

int main(){

  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
