#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN_OF_STRING = 2e6;
const int ROOT_INDEX_ZERO = 0;

vector<vector<int> > children_index_lookup;
vector<int> occurrence_of_segment;


// 3. DFS through the tree, try to translate the occurrence count to answer points,
//      the occurrences not used up is collected up to the parent segment.
int dfs (int bundle_size, int parent_index = ROOT_INDEX_ZERO,
         int current_segment_index = ROOT_INDEX_ZERO, int current_depth = 0) {
//  3.1 Step through each possible character following the current segment, probe into it if it has an index not root
  int children_score = 0;
  for (int current_char_index = 0; current_char_index < 26; ++current_char_index) {
    int new_segment_index = children_index_lookup[current_segment_index][current_char_index];
    if (new_segment_index != ROOT_INDEX_ZERO) {
//    3.1.1 DFS into the child and collect their completed scores.
      children_score +=
        dfs(bundle_size, current_segment_index, new_segment_index, current_depth + 1);
    }
  }

//  3.2 Collect the total complete score at this segment + its children
  int current_segment_count = occurrence_of_segment[current_segment_index] ;
  int current_num_bundle = (current_segment_count / bundle_size);
  int current_segment_score = current_num_bundle * current_depth;
  int total_score = children_score + current_segment_score;

// 3.3 Add back the not used up scores to its parent index count, so they can be bundled at a
//       lower depth.
  int remaining_segment_count = current_segment_count - current_num_bundle * bundle_size;
  if (current_depth >= 2) occurrence_of_segment[parent_index] += remaining_segment_count;

  return total_score;

}

void solve(){

  // 1. Get input
  int number_words, bundle_size;
  cin >> number_words >> bundle_size;
  vector<string> inputStrings(number_words);
  for (int i = 0; i < number_words; ++i) {
    string in;
    cin >> in;
    inputStrings[i] = in;
  }


  // 2. Translates words into trees
  //   2.1 Children_index_lookup[i] is an array of 26 index pointed to from segment made up of
  //         i-th segment following the next char ('A' to 'Z')
  //       Children_index_lookup[0] is an array of 26 index pointed to from root segment,
  //         which represents the segment "" followed by 'A' to 'Z', which are segment "A" to "Z".
  //       A new segment is added to index if it has not been previously created.
  //       Children_index_lookup[7][2] stores the index of the 7-th indexed segment
  //         followed by character 'C' (2 = 'C' - 'A').
  //       Children_index_lookup[0][11] stores the index pointed to from segment "" following 'L'
  //         which is the index of the segment ("" + "L") = "L".
  children_index_lookup.resize(0);
  children_index_lookup.resize(MAX_LEN_OF_STRING + 1, vector<int>(26, 0));
  //   2.2 occurrence_of_segment stores the occurrence of a string indexed by i
  occurrence_of_segment.resize(0);
  occurrence_of_segment.resize(MAX_LEN_OF_STRING  + 1, ROOT_INDEX_ZERO);
  //   2.3 Iterate through words to construct tree and add occurrence_of_segment count
  int next_new_index = 1;
  for (int i = 0; i < number_words; ++i) {
    string current_string = inputStrings[i];
    int previous_segment_index = ROOT_INDEX_ZERO;
    //   2.3.1 Step through a word from beginning to end
    for (int j = 0; j < current_string.size(); ++j){
      int current_char_index = current_string[j] - 'A';
      // 2.3.2 If the segment following this char is not yet indexed, give it a new index
      if (children_index_lookup[previous_segment_index][current_char_index] == ROOT_INDEX_ZERO) {
        children_index_lookup[previous_segment_index][current_char_index] = next_new_index;
        next_new_index ++;
      }
      // 2.3.3 Step into the new segment to get ready to step into next char's index
      previous_segment_index = children_index_lookup[previous_segment_index][current_char_index];
    }
    // 2.3.4 increment the occurrence at the last character's index
    occurrence_of_segment[previous_segment_index] ++;
  }

  // 3. DFS through the tree to collect points from bottom to up.
  int answer = 0;
  answer = dfs(bundle_size);

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
