#include <bits/stdc++.h>
using namespace std;

// 4. DFS through doors to count how many sub-nodes a node has
int dfsCountSubnode(vector<int> &subnode_count, const vector<int> &left_child, const vector<int> &right_child, int current_node){
  int left_subnode_count = 0;
  int right_subnode_count = 0;
  if(left_child[current_node] != -1){
    left_subnode_count = dfsCountSubnode(subnode_count, left_child, right_child, left_child[current_node]);
  }
  if(right_child[current_node] != -1){
    right_subnode_count = dfsCountSubnode(subnode_count, left_child, right_child, right_child[current_node]);
  }
  subnode_count[current_node] = 1 + left_subnode_count + right_subnode_count;
  return subnode_count[current_node];
}

void solve(){

  // 1. Get input
  int N, Q;
  cin >> N >> Q;
  vector<int> difficulties(N-1);
  vector<int> query_start(Q);
  vector<int> query_nth_room(Q);
  for (int i = 0; i < N - 1; ++i) {
    int in;
    cin >> in;
    difficulties[i] = in;
  }
  for (int i = 0 ; i < Q; ++i) {
    int start, step;
    cin >> start >> step;
    query_start[i] = start;
    query_nth_room[i] = step;
  }


  // 2. Calculate the left and right closest door with higher but smallest difficulty
  vector<int> left_next(N - 1);
  stack<int> left_max_stack;
  for(int i = 0; i < N - 1 ; ++i){
    // 2.1  Remove the values smaller than the current value, the set it as the next difficult door.
    while(left_max_stack.size() > 0 && difficulties[i] > difficulties[left_max_stack.top()])
      left_max_stack.pop();
    left_next[i] = (left_max_stack.size() == 0) ? -1 : left_max_stack.top();
    // 2.2  Push the door to the stack for the following door to try difficulties.
    left_max_stack.push(i);
  }

  vector<int> right_next(N - 1);
  stack<int> right_max_stack;
  for (int i = N - 2; i >= 0; --i) {
    while(right_max_stack.size() > 0 && difficulties[i] > difficulties[right_max_stack.top()])
      right_max_stack.pop();
    right_next[i] = (right_max_stack.size() == 0) ? -1 : right_max_stack.top();
    right_max_stack.push(i);
  }

  // 3. Construct the Cartesian Tree based on the door opening next.
  //    When a door is opened, the next door that would be more difficult to open but will
  //      be opened first will be its parent node.
  //    If a parent node is opened, all its children node are either going to be opened immediately
  //      or are already opened.
  vector<int> parent(N - 1);
  vector<int> left_child(N - 1, -1);
  vector<int> right_child(N - 1, -1);
  int root_index = -1;
  for(int i = 0 ; i < N - 1; ++i){
    if (right_next[i] == -1 && left_next[i] == -1) {
  //    3.1 Root node
      parent[i] = -1;
      root_index = i;
    } else if (left_next[i] == -1 || ( right_next[i] != -1 && difficulties[left_next[i]] > difficulties[right_next[i]])) {
  //    3.2 Select right door if there is no left door with higher difficulty or the right difficult door is easier than left
      int right_child_index = right_next[i];
      parent[i] = right_child_index;
      right_child[right_child_index] = i;
    } else {
  //    3.3 Else select left door
      int left_next_index = left_next[i];
      parent[i] = left_next_index;
      left_child[left_next_index] = i;
    }
  }

// 4. DFS sub-node count calculation.
//    DFS through the tree to calculate how many sub-nodes every node has, which
//      also represents how many doors need to be opened before opening door i.
  vector<int> subnode_count(N, 0);
  dfsCountSubnode(subnode_count, left_child, right_child, root_index);

// 5. Binary step tree search construction.
//    Ex. lookup[2][0] = node 3's parent, = 1 level up
//        lookup[2][1] = node 3's parent's[0] lookup, = 2 level up
//        lookup[2][2] = node 3's [2] lookup's [2] lookup, = 4 level up
//        lookup[2][5] = node 3's [4] lookup's [4] lookup, = 32 level up
  int lookup_length = 1; // N-1 = 5, lookup length = 2
  while(pow(2, lookup_length) <= (N - 1) - 1){
    lookup_length ++;
  }
  vector<vector<int> > binary_parent_lookup(N-1, vector<int>(lookup_length, -1));
  for(int binary_step = 0; binary_step < lookup_length; ++binary_step){
    for(int current_node_index = 0; current_node_index < N - 1; ++current_node_index){
    // 5.1 All [0] level lookup is parent
      if(binary_step == 0){
        if(parent[current_node_index] != -1){
          binary_parent_lookup[current_node_index][binary_step] = parent[current_node_index];
        }
      }else{
    // 5.2 All [k] level lookup finds its' [k-1] level lookup's [k-1] level up
    //     As 2^k level up is 2^(k-1) level up then another 2^(k-1) level up
    //     As 8 level up is 4 level up then another 4 level up
        if (binary_parent_lookup[current_node_index][binary_step - 1] != -1) {
          int parent_step_upward = binary_step - 1;
          int stepped_parent_index = binary_parent_lookup[current_node_index][parent_step_upward];
          binary_parent_lookup[current_node_index][binary_step] = binary_parent_lookup[stepped_parent_index][parent_step_upward];
        }
      }
    }
  }

  // 6. Process input cases
  for (int i = 0; i < Q; ++i) {
    int starting_room = query_start[i];
    int door_open_quota = query_nth_room[i] - 1;
    int first_door;
    // 6.1 Select the first opened door (node)
    if(starting_room == 1){
      first_door = 0;
    } else if( starting_room == N) {
      first_door = N-2;
    } else {
      first_door = difficulties[starting_room - 2] > difficulties[starting_room-1] ? starting_room - 1 : starting_room-2;
    }
    // 6.2.1  Case 1: If the first opened door has sub-node count greater than steps.
    //               Go all the way in same direction as the other direction won't be opened until
    //               all other side is opened and steps used up.
    if (subnode_count[first_door] >= door_open_quota) {
      bool is_first_step_right = first_door == starting_room - 1 ;
      if (is_first_step_right) {
        cout << starting_room + door_open_quota << " ";
      } else {
        cout << starting_room - door_open_quota << " ";
      }
    }else{
    // 6.2.2  Case 2: The firs opened door's sub-node count is not greater than total door to open.
    //               Travel upward the tree until find a door that needs more doors opened than step
      int max_completed_door = first_door;
      // 6.2.2.1  Binary step up to find the parent node with the greatest sub-node count but lesser than the door open quota
      for (int k = lookup_length - 1; k >= 0; --k){
          // find the room such that the current node can be finished but need to go up for next step
          // quota = 7, next node sub-node count = 4 or 5 or 6 go up
          // quota = 7, next node sub-node count = 7, 8 stay
        int parent_2_to_k_step_above = binary_parent_lookup[max_completed_door][k];
        if (parent_2_to_k_step_above != -1 && subnode_count[parent_2_to_k_step_above] < door_open_quota) {
          max_completed_door = parent_2_to_k_step_above;
        }
      }
      // 6.2.2.2  Use up the remaining door opening quota to open door in the direction of the next difficult door
      int current_node_sub_door = subnode_count[max_completed_door];
      int residual_steps = door_open_quota - current_node_sub_door;
      bool is_next_difficult_door_at_left = parent[max_completed_door] < first_door;
      if (is_next_difficult_door_at_left) {
        int before_enter_room_number = parent[max_completed_door] + 2;
          cout << before_enter_room_number - residual_steps << " ";
      }else{
        int before_enter_room_number = parent[max_completed_door] + 1;
          cout << before_enter_room_number + residual_steps << " ";
      }

    }
  }
  cout << "\n";
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
