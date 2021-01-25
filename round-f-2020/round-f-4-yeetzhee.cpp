#include <bits/stdc++.h>
using namespace std;

// 3.2  Find the candidate new composition one roll from current composition that contributes
//        to the completion of target composition. for composition with two dice with same occurrence,
//        the candidate new composition add 1 to the first dice index, and the expected turn would be
//        multiplied later, as the two composition are interchangeable.
//      Ex. for target_composition = {5, 5, 4, 2,1}, current_composition = {3, 2, 2, 0, 0}
//        candidates are {4, 2, 2, 0, 0}, {3, 3, 2, 0, 0}, and {3, 2, 2, 1, 0}. Add 1 is added to the
//        first slot that starts a new same occurrence. This make sure the slot increased will not exceed
//        the slot before it, and when they get to the same occurrence, they can be interchanged.
void generateCandidate (const vector<int> &current_composition, const vector<int> &target_composition, int group_length,
                       vector<vector<int> > &returned_candidate_compositions, vector<int> &returned_candidate_adding_at) {
  int last_slot_occurrence = -1;
  for (int slot = 0; slot < group_length; ++slot) {
    bool slot_has_new_occurrence = current_composition[slot] != last_slot_occurrence;
    bool slot_not_full = current_composition[slot] + 1 <= target_composition[slot];
    bool slot_need_increment = slot_has_new_occurrence && slot_not_full;

    if (slot_need_increment) {
      vector<int> new_composition(group_length);
      new_composition = current_composition;
      new_composition[slot] ++;
      returned_candidate_adding_at.push_back(slot);

      last_slot_occurrence = current_composition[slot];
      returned_candidate_compositions.push_back(new_composition);

    }
  }
}

// 3.3.2 Count number of slots with same occurrence that can interchange with the slot's increment
int getNumInterchangableSlot (const vector<int> &current_composition, int slot_value_after_update, int group_length, int num_face) {
  int num_same_count_slot = 0;
  if (slot_value_after_update == 1) {
    // 3.3.2.1  If slot is to increase to 1, any empty slot can be used
    int non_empty_slot = 0;
    for (int j = 0; j < group_length; ++j){
      if (current_composition[j] != 0) non_empty_slot ++;
    }

    num_same_count_slot = num_face - non_empty_slot;

  } else {
    // 3.3.2.2  If slot is to increase to k more than 1, only slot with k - 1 originally can be used
    for (int j = 0; j < group_length; ++j) {
      int slot_value_before_update = slot_value_after_update - 1;
      if (current_composition[j] == slot_value_before_update) {
        num_same_count_slot ++;
      }
    }

  }
  return num_same_count_slot;
}

// 3. Calculate best average from an empty partition set
double calculateBestAverage (vector<int> &current_composition, int group_length, int num_face,
                            map<vector<int>, double> &expected_value_cache, vector<int> &target_composition) {

  // 3.1  Check if the composition is completed, if completed, no rolling is needed, return 0
  bool is_completed = true;
  for (int i = 0 ; i < group_length; ++i) {
    if (current_composition[i] != target_composition[i]) is_completed = false;
  }
  if (is_completed) return 0;

  // 3.2  Find the candidate new composition one roll from current composition that contributes
  vector<vector<int> > candidate_compositions;
  vector<int> candidate_adding_at;
  generateCandidate(current_composition, target_composition, group_length, candidate_compositions, candidate_adding_at);

  // 3.3  Calculate expected value of candidate composition for x = 1 + sigma(P_i * E_i) / sigma (P_i)
  double sigma_Pi = 0;
  double sigma_Pi_Ei = 0;
  double one_over_num_face = 1.0 / num_face;

  for (int i = 0; i < candidate_compositions.size(); ++i) {
    // 3.3.1 Try every candidate for their expected turn E_i
    double candidate_expected_turn = 0;
    if (expected_value_cache.find(candidate_compositions[i]) != expected_value_cache.end()) {
      candidate_expected_turn = expected_value_cache[candidate_compositions[i]];
    } else {
      candidate_expected_turn = calculateBestAverage(candidate_compositions[i], group_length, num_face, expected_value_cache, target_composition);
      expected_value_cache[candidate_compositions[i]] = candidate_expected_turn;
    }

    // 3.3.2 Count number of slots with same occurrence that can interchange with the slot's increment
    int slot_value_after_update = candidate_compositions[i][candidate_adding_at[i]];
    int num_same_count_slot = getNumInterchangableSlot(current_composition, slot_value_after_update, group_length, num_face);

    // 3.3.3 Update Sigma(P_i * E_i) and Sigma(P_i) for x = 1 + sigma(P_i * E_i) / sigma (P_i)
    sigma_Pi += num_same_count_slot * one_over_num_face;
    sigma_Pi_Ei += num_same_count_slot * one_over_num_face * candidate_expected_turn;
  }

  // 3.4 Run x = 1 + sigma(P_i * E_i) / sigma (P_i)
  double expected_turn = (1.0 + sigma_Pi_Ei ) / sigma_Pi;
  return expected_turn;
}

void solve() {

  // 1. Get input
  int num_dice, num_face, num_group;
  cin >> num_dice >> num_face >> num_group;
  vector<int> target_grouping(num_group);
  for (int i = 0; i < num_group; ++i) {
    int in = 0;
    cin >> in;
    target_grouping[i] = in;
  }

  // 2. Sort target grouping. So the greatest grouping will be in front, and partitioning
  //      can be kept from big partition to small partition
  sort(target_grouping.begin(), target_grouping.end(), greater<int>());

  // 3. calculate best average from an empty partition set
  vector<int> empty_set(num_group, 0);
  map<vector<int>, double> config_expected_value_cache;
  double ans = calculateBestAverage(empty_set, target_grouping.size(), num_face, config_expected_value_cache, target_grouping);

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
