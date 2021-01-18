#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
#include<iostream>
#include<unordered_set>
using namespace std;

long long LIMIT = 1e9;

void solve(){

  int R, C;
  cin >> R >> C;

  vector<bool> hasChar(26, false);
  vector<vector<char> > maps(R, vector<char>(C, ' '));
  for(int i = 0; i < R; ++i){
    string in;
    cin >> in;
    for(int j = 0; j < C; ++j){
      maps[i][j] = in[j];
      int currentCharIndex = in[j] - 'A';
      hasChar[currentCharIndex] = true;
    }
  }

  vector<vector<bool> > dependsOn(26, vector<bool>(26, false));

  for(int i = 0; i < R - 1; ++i){
    for(int j = 0; j < C; ++j){
      int currentCharIndex = maps[i][j] - 'A';
      int belowCharIndex = maps[i+1][j] - 'A';
      if(currentCharIndex != belowCharIndex){
        dependsOn[currentCharIndex][belowCharIndex] = true;
      }
    }
  }



  vector<int> ans(0);
  vector<int> solved(26, false);
//  for(int i = 0; i < 26; ++i) cout << solved[i] << " ";
//  cout << endl;
  for(int i = 0 ; i < 26; ++i){
    if(!hasChar[i]){
      solved[i] = true;
    }else{
      bool isIndependent = true;
      for(int j = 0; j < 26; ++j){
        if(dependsOn[i][j]){
          isIndependent = false;
        }
      }
      if(isIndependent){
        ans.push_back(i);
        solved[i] = true;
      }
    }

  }


//
//  for(int i = 0; i < 26; ++i) cout << solved[i] << " ";
//  cout << endl;

  for(int j = 0; j < 26; ++j){
    for(int i = 0; i < 26; ++i){
      if(!solved[i]){
        bool isIndependent = true;
        for(int j = 0; j < 26; ++j){
          if(dependsOn[i][j] && !solved[j]){
            isIndependent = false;
          }
        }
        if(isIndependent){
          solved[i] = true;
          ans.push_back(i);
        }
      }
    }
  }


//  for(int i = 0; i < 26; ++i) cout << solved[i] << " ";
//  cout << endl;

  string ansString = "";
  for(int i = 0; i < ans.size(); ++i){
    char newChar = ans[i] + 'A';
    ansString += newChar;
  }

  bool hasSolution = true;
  for(int i = 0 ; i < 26; ++i){
    if(!solved[i]) hasSolution = false;
  }

  if(hasSolution)
    cout << ansString << endl;
  else
    cout << "-1" << endl;
}

int main(){

  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
