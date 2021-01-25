#include <bits/stdc++.h>
using namespace std;

// 2. Get number of boring number equal or below a number
//    Ex. getNumBoring(16) = 9. with boring number being: 1, 3, 5, 7, 9, 10, 12, 14, 16
long long getNumBoring (long long number) {

  // 2.1  Take care of single digit case
  if(number <= 9) return (number + 1) / 2;


  // 2.2 Count the boring number before reaching the first digit
  //     Ex. 6532 will have 0 to 9 = 5, 10 to 99 = 5 * 5, 100 to 999 = 5 * 5 * 5,
  //         0 to 999 is calculated in this step, and result so far is 155
  long long ans = 5;
  int current_digit_index = 2;

  while(pow(10, current_digit_index - 1 ) <= LLONG_MAX / 10 && pow(10, current_digit_index) <= number) {
    current_digit_index ++;
    ans += pow(5, current_digit_index - 1);
  }

  // 2.3 Looking at the digit from front to back, count how many boring number it has with its
  //       previous digits selected
  //     Ex. 5632
  //         iteration 1:
  //            current digit index = 4. current digit = 5.
  //            will have 1 _ _ _, 3 _ _ _ to enumerate. Each has 125 possibility,
  //            Result so far is 155 + 250 = 405 steps.
  //         iteration 2:
  //            current digit index = 3. current digit = 6.
  //            will have 50 _ _, 52 _ _, 54 _ _ to enumerate. Each has 25 possibility,
  //            Result so far is 405 + 75 = 480 steps.
  //         iteration 3:
  //            current digit index = 2. current digit = 3.
  //            will have 561 _ to enumerate = 5 possibility.
  //            Result so far is 480 + 5 = 485 possibility.
  //         iteration 4:
  //            current digit index = 1. current digit = 2.
  //            will have 5610 and 5612.
  //            And final result will be 485 + 2 = 487 steps.

  bool is_current_digit_odd = true;

  while (current_digit_index >= 1) {

    long long current_digit = number / pow(10, current_digit_index - 1);
    number -= current_digit * pow(10, current_digit_index - 1);

    if (is_current_digit_odd) {
      if (current_digit_index == 1) {
        ans += (current_digit + 1) / 2;
        break;
      }

      long long expandable_digit = current_digit / 2;
      ans += expandable_digit * pow(5, current_digit_index - 1);

      if (current_digit % 2 == 0) break;

    } else {
      if (current_digit_index == 1) {
        ans += (current_digit + 2) / 2;
        break;
      }

      long long expandable_digit = (current_digit + 1) / 2;
      ans += expandable_digit * pow(5, current_digit_index - 1);

      if (current_digit % 2 == 1) break;

    }

    current_digit_index --;
    is_current_digit_odd = !is_current_digit_odd;

  }

  return ans;

}

void solve() {

  // 1. Get input
  long long L, R;
  cin >> L >> R;

  // 2. Get result, result = boring(right) - boring(left - 1).
  long long left = getNumBoring(L - 1);
  long long right = getNumBoring(R);

  cout << right - left << "\n";
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
