#include <bits/stdc++.h>
using namespace std;

long long LIMIT = 1e12;
vector<pair<int, int> > streets;
vector<vector<int> > stones_at_junction;
vector<vector<int> > recipe_ingredients;
vector<int> recipe_product;

vector<vector<int> > connected_junctions;
vector<vector<int> > recipes_needing_stone;
vector<vector<long long> > cost_junction_to_stone;
priority_queue <pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>> >, greater<pair<long long, pair<int, int> > > >
  cost_junction_stone_pair_priority_queue;

// 6.2  Try recipe on the current junction, try all recipes involving current_stone
void tryApplyRecipesWithStone(int current_stone, int current_junction) {
  for (int current_recipe = 0; current_recipe < recipes_needing_stone[current_stone].size(); ++current_recipe) {
    // 6.2.1  Try building product stone by using recipe at current_junction.
    long long cost_to_new_product = 0;
    int recipe_index = recipes_needing_stone[current_stone][current_recipe];
    for (int k = 0; k < recipe_ingredients[recipe_index].size(); ++k) {
      int ingredient = recipe_ingredients[recipe_index][k] - 1;
      cost_to_new_product += cost_junction_to_stone[current_junction][ingredient];
    }
    int product = recipe_product[recipe_index] - 1;
    // 6.2.2  If the product can be made easier, update cost and add target combination to priority queue
    if (cost_to_new_product < cost_junction_to_stone[current_junction][product]) {
      cost_junction_to_stone[current_junction][product] = cost_to_new_product;
      cost_junction_stone_pair_priority_queue.push(make_pair(cost_to_new_product, make_pair(current_junction, product)));
    }
  }
}

// 6.3  Try relax adjacent junction with the connected path
void tryDijkstraRelax(int current_junction, int current_stone, int destination_junction){
  long long new_cost = cost_junction_to_stone[current_junction][current_stone] + 1;
  if(cost_junction_to_stone[destination_junction][current_stone] > new_cost){
    cost_junction_to_stone[destination_junction][current_stone] = new_cost;
    cost_junction_stone_pair_priority_queue.push(make_pair(new_cost, make_pair(destination_junction, current_stone)));
  }
}

void solve(){

  // 1. Get input
  int num_junction, num_street, num_stone, num_recipe;
  cin >> num_junction >> num_street >> num_stone >> num_recipe;

  streets.resize(num_street);
  for(int i = 0; i < num_street; ++i) {
    int j1, j2;
    cin >> j1 >> j2;
    streets[i] = make_pair(j1, j2);
  }

  stones_at_junction.resize(num_junction);
  for (int i = 0; i < num_junction; ++i) {
    int lin;
    cin >> lin;
    stones_at_junction[i].resize(lin);
    for(int j = 0; j < lin; ++j){
      int sin;
      cin >> sin;
      stones_at_junction[i][j] = sin;
    }
  }

  recipe_ingredients.resize(num_recipe);
  recipe_product.resize(num_recipe);
  for (int i = 0; i < num_recipe; ++i) {
    int lin;
    cin >> lin;
    recipe_ingredients[i].resize(lin);
    for (int j = 0; j < lin; ++j) {
      int iin;
      cin >> iin;
      recipe_ingredients[i][j] = iin;
    }
    int pin;
    cin >> pin;
    recipe_product[i] = pin;
  }

  // 2. List the junctions connected to every junction
  //    Ex. connected_junctions[2] = {3, 4, 5} means junction 3 is connected to junction 4, 5, 6
  connected_junctions.resize(0);
  connected_junctions.resize(num_junction, vector<int>(0));
  for (int i = 0; i < num_street; ++i) {
    int junction_a = streets[i].first - 1;
    int junction_b = streets[i].second - 1;
    connected_junctions[junction_a].push_back(junction_b);
    connected_junctions[junction_b].push_back(junction_a);
  }

  // 3. List the recipes every stones are needed by
  //    Ex. recipes_needing_stone[3] = {6, 7} means stone 4 is used in recipe 7 and recipe 8
  recipes_needing_stone.resize(0);
  recipes_needing_stone.resize(num_stone, vector<int>(0));
  for(int i = 0; i < num_recipe; ++i){
    for(int j = 0; j < recipe_ingredients[i].size(); ++j){
      int ingredientIndex = recipe_ingredients[i][j] - 1;
      recipes_needing_stone[ingredientIndex].push_back(i);
    }
  }

  // 4. Initialize costs table from junction to stone.
  //      set cost of stone at junction to zero if the junction has the stone
  //    Ex. cost_junction_to_stone[3][6] = 9 means moving stone 7 to junction 4 takes 9 moves.
  cost_junction_to_stone.resize(0);
  cost_junction_to_stone.resize(num_junction, vector<long long>(num_stone, LIMIT));
  for (int i = 0; i < num_junction; ++i) {
    for(int j = 0; j < stones_at_junction[i].size(); ++j){
      int stoneIndex = stones_at_junction[i][j] - 1;
      cost_junction_to_stone[i][stoneIndex] = 0;
    }
  }

  // 5. Create priority queue for Dijkstra update, enqueue the 0 cost junction-stone pair.
  //    cost_junction_stone_pair_priority_queue sorts the junction
  //      stone pair waiting to be explored by their cost, smallest are in the front
  while (!cost_junction_stone_pair_priority_queue.empty()) cost_junction_stone_pair_priority_queue.pop();
  for (int i = 0; i < num_junction; ++i) {
    for (int j = 0; j < stones_at_junction[i].size(); ++j) {
      int stone_index = stones_at_junction[i][j] - 1;
      cost_junction_stone_pair_priority_queue.push(make_pair(0, make_pair(i, stone_index)));
    }
  }


  // 6. Run Dijkstra algorithm
  while (!cost_junction_stone_pair_priority_queue.empty()) {

    // 6.1  Get the pair with least cost
    pair<long long, pair<int, int> > current_cost_junction_stone_pair = cost_junction_stone_pair_priority_queue.top();
    cost_junction_stone_pair_priority_queue.pop();
    long long current_cost = current_cost_junction_stone_pair.first;
    int current_junction = current_cost_junction_stone_pair.second.first;
    int current_stone = current_cost_junction_stone_pair.second.second;

    // 6.2  Try recipe on the current junction
    tryApplyRecipesWithStone(current_stone, current_junction);

    // 6.3  Try relax cost on the adjacent paths
    for (int i = 0; i < connected_junctions[current_junction].size(); ++i) {
      int destination_junction = connected_junctions[current_junction][i];
      tryDijkstraRelax(current_junction, current_stone, destination_junction);
    }
  }

  // 7. Iterate through all junction's cost to create stone 1 for minimum cost cost across the map.
  long long ans = LIMIT;
  for (int i = 0; i < num_junction; ++i) {
    ans = min(ans, cost_junction_to_stone[i][0]);
  }
  cout << (ans == LIMIT ? -1 : ans) << "\n";

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
