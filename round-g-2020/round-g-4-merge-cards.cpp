#include <bits/stdc++.h>
using namespace std;

void solve() {
  // 1. Get input
  int num_card;
  cin >> num_card;
  vector<int> cards(num_card);
  for (int i = 0; i < num_card; ++i) {
    cin >> cards[i];
  }

  // 2. Create lookup table for n cards k-th coefficient
  //    Ex. Lookup[3][2] = 2 means in a set of 3 cards, the average coefficient of card no.2 is 2.
  vector<vector<double> > n_card_kth_coefficient_lookup(num_card + 1, vector<double>(num_card + 1, 0));
  n_card_kth_coefficient_lookup[2][1] = 1;
  n_card_kth_coefficient_lookup[2][2] = 1;
  for (int n_card = 3; n_card <= num_card; ++n_card) {
    for (int kth_coefficient = 1; kth_coefficient <= n_card; ++kth_coefficient) {
      // 2.1  left_selected_coefficient calculate the coefficient where k_th card is combined to number of its left.
      //      k-th card's coefficient will be increased by 1, as it adds points when merging with the left card.
      //      In the following step, its coefficient is the same as the k-1 th card in set of n-1 card.
      double left_selected_coefficient = 0;
      int left_selected_scenario = 0;
      double right_selected_coefficient = 0;
      int right_selected_scenario = 0;
      // 2.2 left_not_selected_coefficient calculate the coefficient where
      //       left side of k_th card merges card, not involving k_th card.
      //     k-th card's coefficient will not be changed as it is not selected.
      //     In the following step, its coefficient is the same as the k-1 th card in he set of n-1 card.
      //     Such situation can repeats in any of the k - 2 pairs of cards to the left of k_th card, so
      //       the coefficient is multiplied by the number of scenario
      double left_not_selected_coefficient = 0;
      int left_not_selected_scenario = 0;
      double right_not_selected_coefficient = 0;
      int right_not_selected_scenario = 0;

      if(kth_coefficient > 1) {
        left_selected_coefficient = 1 + n_card_kth_coefficient_lookup[n_card - 1][kth_coefficient - 1];
        left_selected_scenario = 1;

        left_not_selected_coefficient = n_card_kth_coefficient_lookup[n_card - 1][kth_coefficient - 1];
        left_not_selected_scenario = kth_coefficient - 2;
      }

      if(kth_coefficient < n_card) {
        right_selected_coefficient = 1 + n_card_kth_coefficient_lookup[n_card - 1][kth_coefficient];
        right_selected_scenario = 1;

        right_not_selected_coefficient = n_card_kth_coefficient_lookup[n_card - 1][kth_coefficient];
        right_not_selected_scenario = n_card - kth_coefficient - 1;
      }

      // 2.2 total_coefficient will be the weighted sum of the above 4 situations' coefficient
      double total_coefficient = (  left_selected_coefficient * left_selected_scenario
                                  + left_not_selected_coefficient * left_not_selected_scenario
                                  + right_selected_coefficient * right_selected_scenario
                                  + right_not_selected_coefficient * right_not_selected_scenario
                                  ) / (n_card - 1);

      n_card_kth_coefficient_lookup[n_card][kth_coefficient] = total_coefficient;
    }
  }


  // 3. Iterate through the lookup table and apply the coefficient
  double ans = 0;
  for (int i = 0; i < num_card; ++i) {
    ans += cards[i] * n_card_kth_coefficient_lookup[num_card][i+1];
  }

  cout << setprecision(10) << ans << "\n";
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
