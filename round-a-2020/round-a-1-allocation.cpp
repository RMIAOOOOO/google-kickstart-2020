#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get inputs
  int number_house, budget;
  cin >> number_house >> budget;
  vector<int> prices(number_house);
  for (int i = 0; i < number_house; ++i) {
    int in;
    cin >> in;
    prices[i] = in;
  }

  // 2. Sort house price from low to high
  sort(prices.begin(), prices.end());

  // 3. Buy houses from the cheapest to the most expensive
  int answer = 0;

  for (int i = 0; i < number_house; ++i) {
    int current_house_price = prices[i];

    if (budget >= current_house_price) {
      budget -= current_house_price;
      answer ++;
    }
  }

  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    cout << "Case #" << i+1 << ": " ;
    solve();
  }

}
