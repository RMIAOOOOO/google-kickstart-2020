#include <bits/stdc++.h>
using namespace std;

long long LIMIT = 1e9;

string instruction;
map<int, int> left_bracket_index_to_right_bracket_index_map;

// 4. Decode instruction
//    return_x_delta and return_y_delta are total x and y mod LIMIT change done by the instruction from
//      instruction[left_index] to instruction[right_index] (inclusive).
//    For example, with instruction "2(3(EW)2(S2(EE)S))", decodeSegment(d_x, d_y, 9, 15) will decode "S2(EE)S"
//      and set d_x to 999999996 (=-4) and set d_y to 2
void decodeSegment (long long &returned_x_delta, long long &returned_y_delta, int left_index, int right_index) {

  long long local_x_delta = 0;
  long long local_y_delta = 0;

  long long current_digital_factor = 0;

  for(int i = left_index; i <= right_index; ++i) {

    if (instruction[i] >= '0' && instruction[i] <= '9') {
  // 4.1  Change the multiplying factor if it is a digit
      int current_digit = instruction[i] - '0';
      current_digital_factor = (current_digital_factor * 10) % LIMIT;
      current_digital_factor += current_digit;
    } else {
  // 4.2  If not a digit, get the multiplying factor to the next instruction
      long long multiplier = current_digital_factor != 0 ? current_digital_factor : 1;

      if(instruction[i] == '(') {
    // 4.2.1  If it is a left bracket, decode the entire bracket's content's delta,
    //          and then apply the change to the local delta, then continue decoding after the right bracket
        int left_bracket_index = i;
        int right_bracket_index = left_bracket_index_to_right_bracket_index_map[left_bracket_index];
        i = right_bracket_index;

        long long bracket_delta_x = 0;
        long long bracket_delta_y = 0;
        decodeSegment(bracket_delta_x, bracket_delta_y, left_bracket_index + 1, right_bracket_index - 1);

        local_x_delta += (LIMIT + bracket_delta_x * multiplier) % LIMIT;
        local_y_delta += (LIMIT + bracket_delta_y * multiplier) % LIMIT;

    // 4.2.2 If it is an alphabet instruction, apply the change with multiplier
      } else if (instruction[i] == 'E') {
        local_x_delta = (local_x_delta + multiplier) % LIMIT;
      } else if (instruction[i] == 'W') {
        local_x_delta = (LIMIT + local_x_delta - multiplier) % LIMIT;
      } else if (instruction[i] == 'S') {
        local_y_delta = (local_y_delta + multiplier) % LIMIT;
      } else if (instruction[i] == 'N') {
        local_y_delta = (LIMIT + local_y_delta - multiplier) % LIMIT;
      }

      current_digital_factor = 0;
    }
  }

  // 4.3 Apply the delta in this segment to the returned reference variable
  returned_x_delta = (returned_x_delta + LIMIT + local_x_delta) % LIMIT;
  returned_y_delta = (returned_y_delta + LIMIT + local_y_delta) % LIMIT;
}

void solve() {

  // 1. Get Input
  instruction = "";
  cin >> instruction;

  // 2. Prepare a map from left bracket's index to corresponding right bracket's index,
  //      this allows selecting the bracketed area by checking the map.
  //    For example, "EE(EEE())" will have {map[2] = 8, map[6] = 7}
  left_bracket_index_to_right_bracket_index_map.clear();
  stack<int> left_bracket_index_stack;
  for (int i = 0; i < instruction.length(); ++i) {
    if (instruction[i] == '(') {
    //  2.1 When found a left bracket, push it into stack
      left_bracket_index_stack.push(i);
    } else if (instruction[i] == ')') {
    //  2.2 when found a right bracket, map it with the closest left bracket
      int left_bracket_index = left_bracket_index_stack.top();
      left_bracket_index_stack.pop();
      left_bracket_index_to_right_bracket_index_map[left_bracket_index] = i;
    }
  }

  // 3. Get the delta_x and delta_y of the entire instruction
  long long x_delta = 0;
  long long y_delta = 0;
  decodeSegment(x_delta, y_delta, 0, instruction.length() - 1);

  cout << x_delta + 1 << " " << y_delta + 1 << endl;
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

