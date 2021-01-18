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
    int numExercise, numExtraSession;
    cin >> numExercise >> numExtraSession;

    priority_queue< pair<int, pair<int, int> > > spaceBetweenAndDivided;

    int last = 0;
    for(int j = 0; j < numExercise; ++j){
      int in;
      cin >> in;
      if(j!=0)spaceBetweenAndDivided.push(make_pair(in-last, make_pair(in-last, 1)));
      last = in;
    }
//    while(!spaceBetweenAndDivided.empty()){
//      cout << spaceBetweenAndDivided.top().first << " " ;
//      spaceBetweenAndDivided.pop();
//    }
    for(int j = 0; j < numExtraSession; ++j){
      pair<int, pair<int, int> > top = spaceBetweenAndDivided.top();
      spaceBetweenAndDivided.pop();
      int alreadyDivided = top.second.second;
      int originalValue = top.second.first;
      int newDivide = alreadyDivided+1;
      int newValue = originalValue / newDivide;
      if(originalValue % newDivide != 0) newValue ++;
      pair<int, pair<int, int> > newTop = make_pair(newValue, make_pair(originalValue, newDivide));
      spaceBetweenAndDivided.push(newTop);
    }

//    cout << spaceBetweenAndDivided.top().first;
    cout << "Case #" << i+1 <<": " << spaceBetweenAndDivided.top().first << "\n";
  }
}
