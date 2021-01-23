#include <bits/stdc++.h>
using namespace std;

void solve(){

  // 1. Get input
  int num_nodes, amandea, bilva;
  vector<int> parents;
  cin >> num_nodes >> amandea >> bilva;
  parents.resize(num_nodes);
  parents[0] = -1;
  for (int i = 1; i < num_nodes; ++i) {
    int in;
    cin >> in;
    in--;
    parents[i] = in;
  }

  // 2. Construct list of child_nodes for every node
  vector<vector<int> > child_nodes(num_nodes, vector<int>(0));
  for (int i = 1; i < num_nodes; ++i) {
    child_nodes[parents[i]].push_back(i);
  }

  // 3. DFS through tree nodes. Add count after a node is explored.
  //      And update the nodes a and b steps above.
  vector<long long> a_count(num_nodes, 0);
  vector<long long> b_count(num_nodes, 0);
  vector<int> path_record(1, 0);
  vector<int> now_at_nth_child(num_nodes, 0);

  int current_node_index = 0;

  while(current_node_index >= 0) {
    int num_children = child_nodes[current_node_index].size();
    // 3.1  If there is child nodes, DFS through it
    if (num_children > now_at_nth_child[current_node_index]) {
      int child_to_visit = child_nodes[current_node_index][now_at_nth_child[current_node_index]];
      now_at_nth_child[current_node_index] ++;
      path_record.push_back(child_to_visit);
      current_node_index = child_to_visit;
    } else {
    // 3.2 If a node is explored completely, update A and B and steps above the path.
      a_count[current_node_index] ++;
      b_count[current_node_index] ++;
      int path_depth = path_record.size();
      if (path_depth - amandea > 0) {
        int node_index_a_steps_above = path_record[path_depth - 1 - amandea];
        a_count[node_index_a_steps_above] += a_count[current_node_index];
      }
      if (path_depth - bilva > 0) {
        int node_index_b_steps_above = path_record[path_depth - 1 - bilva];
        b_count[node_index_b_steps_above] += b_count[current_node_index];
      }
      path_record.resize(path_depth - 1);
      current_node_index = parents[current_node_index];
    }
  }

  // 4. Calculate number of ways reachable by an "a" and a "b" steps below.
  vector<long long> ab_count(num_nodes, 0);
  for (int i = 0 ; i < num_nodes; ++i) {
    ab_count[i] = a_count[i] * b_count[i];
  }

  // 5. Sum up the count across the tree
  long long a_count_sum = 0;
  long long b_count_sum = 0;
  long long ab_count_sum = 0;
  for (int i = 0 ; i < num_nodes; ++i) {
    a_count_sum += a_count[i];
    b_count_sum += b_count[i];
    ab_count_sum += ab_count[i];
  }

  // 6. Calculate answer by probability of event a or b
  double ans = static_cast<double>(a_count_sum) / num_nodes
                + static_cast<double>(b_count_sum) / num_nodes
                - static_cast<double>(ab_count_sum) / num_nodes / num_nodes;

  cout.precision(numeric_limits<double>::max_digits10);
  cout << ans << "\n";
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
