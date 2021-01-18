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
    vector<int> prices;
    int number, budget;
    cin >> number >> budget;
    for(int j = 0 ; j < number; ++j){
        int price = 0;
      cin >> price;
      prices.push_back(price);
    }
    sort(prices.begin(), prices.end());
    int ans = 0;
    for(int z = 0; z < number; ++z){
      if(budget >= prices[z]){
        budget -= prices[z];
        ans ++;
      }else{
        break;
      }
    }
    cout << "Case #" << i+1 << ": " << ans << "\n";
  }
}
