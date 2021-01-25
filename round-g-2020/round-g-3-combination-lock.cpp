#include <bits/stdc++.h>
using namespace std;

vector<long long> wheel;
vector<long long> wheel_sum;

// 4.2 Binary search the index at which the wheel should start turn in the opposite way
int findFrontReverseIndex (int front_reverse_value, int left_index, int right_index) {
  if (front_reverse_value == 1) {
    return -1;
  }
  if (right_index < left_index) return right_index;
  int mid_index = (left_index + right_index) / 2;
  if (wheel[mid_index] >= front_reverse_value) {
    right_index = mid_index - 1;
  } else {
    left_index = mid_index + 1;
  }
  return findFrontReverseIndex(front_reverse_value, left_index, right_index);
}


int findBackReverseIndex(int back_reverse_value, int left_index, int right_index, int num_wheel){
  if (back_reverse_value == num_wheel) {
    return num_wheel;
  }
  if (left_index > right_index) return left_index;
  int mid_index = (left_index + right_index + 1) / 2;
  if (wheel[mid_index] <= back_reverse_value) {
    left_index = mid_index + 1;
  } else {
    right_index = mid_index - 1;
  }
  return findBackReverseIndex(back_reverse_value, left_index, right_index, num_wheel);
}


void solve(){

  // 1. Get input
  long long num_wheel, wheel_max;
  cin >> num_wheel >> wheel_max;
  wheel.resize(num_wheel);
  for (int i = 0; i < num_wheel; ++i) {
    cin >> wheel[i];
  }


  // 2. sort wheel to allow review in ascending order
  sort(wheel.begin(), wheel.end());

  // 3. Prepare prefix sum of wheel
  wheel_sum.resize(num_wheel, 0);
  wheel_sum[0] = wheel[0];
  for (int i = 1; i < num_wheel; ++i) {
    wheel_sum[i] = wheel[i] + wheel_sum[i-1];
  }


  // 4. Try using every value of the wheels as the final value, calculate the cost, and update answer
  long long answer = num_wheel * wheel_max;

  for(int i = 0 ; i < num_wheel; ++i){

    long long current_wheel_value = wheel[i];

    // 4.1 Calculate the value at which the wheel should turn in the opposite way
    //       Ex. current wheel = 125, wheel_max = 400, front reverse value = 1, back reverse value = 325,
    //             (wheel smaller than 1 reverse turn, wheel greater than 325 reverse turn)
    //       Ex. current wheel = 333, wheel_max = 500, front reverse value = 83, back reverse value = 500,
    //             (wheel smaller than 83 reverse turn, wheel greater than 500 reverse turn)
    int max_step = wheel_max / 2;
    int front_reverse_value = current_wheel_value <= (max_step + 1) ? 1 : current_wheel_value - max_step;
    int back_reverse_value = current_wheel_value >= (wheel_max - max_step) ? wheel_max : current_wheel_value + max_step;

    // 4.2 Calculate the index at which the wheel should start turn in the opposite way
    //       Ex. wheel values = {32, 46, 98, 114, 115, 116, 142, 195, 246, 265, 266, 277}, wheel_max = 300
    //             current wheel = 265, front_reverse_value = 115
    //             then front_index = 3 (equal or lower than index 3 {wheel 32, 46, 98, 114} should go opposite way)
    //       Ex. wheel values = {32, 46, 98, 114, 115, 116, 142, 195, 246, 265, 266, 277}, wheel_max = 300
    //             current wheel = 115, back_reverse_value = 265
    //             back_index = 10 (equal or higher than index 10 {wheel 266, 277 } should go opposite way)
    int front_reverse_index = findFrontReverseIndex(front_reverse_value, 0, num_wheel - 1);
    int back_reverse_index = findBackReverseIndex(back_reverse_value, 0, num_wheel - 1, num_wheel);

    // 4.3 Calculate cost of different part.
    //       Ex. wheel values = {32, 46, 98, 114, 115, 116, 142, 195, 246, 265, 266, 277}, wheel_max = 300
    //           current_wheel 265, front_reverse_value = 115
    //           front_reverse:   32, 46, 98, 114
    //           front_straight:  116, 142, 195, 246
    //           back_straight:   266, 267
    //           back_reverse:    none
    long long front_reverse_cost = front_reverse_index == -1 ? 0 :
      (wheel_max - current_wheel_value) * (front_reverse_index + 1 ) + wheel_sum[front_reverse_index];

    long long front_straight_cost = front_reverse_index == -1 ? (i + 1) * current_wheel_value - wheel_sum[i] :
      (i - front_reverse_index) * current_wheel_value - (wheel_sum[i] - wheel_sum[front_reverse_index]);

    long long back_straight_cost = back_reverse_index == num_wheel ?
      wheel_sum[num_wheel - 1] - wheel_sum[i] - (num_wheel - 1 - i) * current_wheel_value :
      wheel_sum[back_reverse_index - 1] - wheel_sum[i] - (back_reverse_index - 1 - i) * current_wheel_value;

    long long back_reverse_cost = back_reverse_index == num_wheel ? 0 :
      (num_wheel - back_reverse_index) * current_wheel_value +
      (num_wheel - back_reverse_index) * wheel_max
      - (wheel_sum[num_wheel - 1] - wheel_sum[back_reverse_index - 1]);

    // 4.4 Update cost
    long long total_cost = front_reverse_cost + front_straight_cost + back_reverse_cost + back_straight_cost;

    answer = min(answer, total_cost);
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
