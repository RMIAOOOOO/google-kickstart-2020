#include <bits/stdc++.h>
using namespace std;

vector<long long> multiple_sum_tree;
vector<long long> regular_sum_tree;


// 4. Prepare tree construction functions
// 4.1  Initialize segment tree
//      Ex. for an array with element {1, 2, 3, 4, 5},
//        The num_leaf will be 8, tree_size will be 16
//        tree will be {0, 15, 10, 5, 3, 7, 5, 0, 1, 2, 3, 4, 5, 0, 0, 0}
//                      15
//               10              5
//           3       7       5       0
//         1   2   3   4   5   0   0   0
void initializeSegmentTree(vector<long long> &segment_nodes, int array_length) {
  int num_leaf = 1;
  while (1) {
    if(num_leaf >= array_length) break;
    num_leaf *= 2;
    if(num_leaf >= array_length) break;
  }

  int tree_size = num_leaf * 2;
  segment_nodes.resize(0);
  segment_nodes.resize(tree_size, 0);
}

// 4.2 Update segment tree
//     Work from leaf node upwards to root node
void updateSegmentTreeLeaf(vector<long long> &segment_nodes, int index, int new_value) {
  int num_leaves = segment_nodes.size() / 2;
  int target_leaf_index = index + num_leaves;
  int old_value = segment_nodes[target_leaf_index];
  int delta = new_value - old_value;
  for(int i = target_leaf_index; i > 0; i /= 2) {
    segment_nodes[i] += delta;
  }
}

// 4.3 Query segment tree
//     Query from leaf node upwards to root node, add incomplete node value to answer
//     Ex. Leaf Array {1, 2, 3, 4, 5} with query [2, 3] returns 3+4 = 7
long long querySegmentTreeLeaf(vector<long long> &segment_nodes, int left, int right) {
  long long result = 0;
  int num_leaves = segment_nodes.size() / 2;
  left = left + num_leaves;
  right = right + num_leaves;
  while(left <= right) {
    // If true, parent node's root tree will not be complete
    bool left_is_right_child = left % 2 == 1;
    bool right_is_left_child = right % 2 == 0;
    if (left_is_right_child) {
    // Add value and move to the right
      result += segment_nodes[left];
      left ++;
    }
    if (right_is_left_child) {
    // Add value and move to the left
      result += segment_nodes[right];
      right --;
    }
    // Move upwards
    left = left / 2;
    right = right / 2;
  }
  return result;
}

void solve() {

  // 1. Get input
  int N, Q;
  cin >> N >> Q;
  vector<int> candies(N);
  vector<char> queries_header(Q);
  vector<pair<int,int> > queries_parameters(Q);
  for (int i = 0; i < N; ++i) {
    int in;
    cin >> in;
    candies[i] = in;
  }
  for (int i = 0; i < Q; ++i) {
    string in;
    int a, b;
    cin >> in >> a >> b;
    queries_header[i] = in[0];
    queries_parameters[i] = make_pair(a, b);
  }

  // 2. Initialize two segment tree
  initializeSegmentTree(regular_sum_tree, N);
  initializeSegmentTree(multiple_sum_tree, N);
  for (int i = 0; i < N; ++i) {
    int regular_value = (i % 2 == 0 ? 1 : -1) * candies[i];
    updateSegmentTreeLeaf(regular_sum_tree, i, regular_value);
    int multiple_value = (i % 2 == 0 ? 1 : -1) * (i + 1) * candies[i];
    updateSegmentTreeLeaf(multiple_sum_tree, i, multiple_value);
  }

  // 3. Process every query
  long long answer = 0;
  for (int i = 0; i < Q; ++i) {
    if (queries_header[i] == 'Q') {
      int left = queries_parameters[i].first - 1;
      int right = queries_parameters[i].second - 1;

      long long multiple_query_result = querySegmentTreeLeaf(multiple_sum_tree, left, right);
      long long regualr_query_result = left * querySegmentTreeLeaf(regular_sum_tree, left, right);
      long long total_query_result = (left % 2 == 0? 1 : -1 ) * (multiple_query_result - regualr_query_result);

      answer += total_query_result ;

    } else if (queries_header[i] == 'U') {
      int index = queries_parameters[i].first - 1;
      int new_value = queries_parameters[i].second;

      int regular_value = (index % 2 == 0 ? 1 : -1) * new_value;
      updateSegmentTreeLeaf(regular_sum_tree, index, regular_value);
      int multiple_value = (index % 2 == 0 ? 1 : -1) * (index+1) * new_value;
      updateSegmentTreeLeaf(multiple_sum_tree, index, multiple_value);
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
