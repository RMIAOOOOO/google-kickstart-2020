#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<map>
#include<iomanip>
using namespace std;

long long LIMIT = 1e12;

void solve(){
  int numberOfJunction, numberOfStreet, numberOfStone, numberOfRecipe;
  cin >> numberOfJunction >> numberOfStreet >> numberOfStone >> numberOfRecipe;

  vector<pair<int, int> > streets(numberOfStreet);
  for(int i = 0; i < numberOfStreet; ++i){
    int j1, j2;
    cin >> j1 >> j2;
    streets[i] = make_pair(j1, j2);
  }

  vector<vector<int> > stonesAtJunction(numberOfJunction);
  for(int i = 0; i < numberOfJunction; ++i){
    int lin;
    cin >> lin;
    stonesAtJunction[i].resize(lin);
    for(int j = 0; j < lin; ++j){
      int sin;
      cin >> sin;
      stonesAtJunction[i][j] = sin;
    }
  }

  vector<vector<int> > recipesIngredient(numberOfRecipe);
  vector<int> recipesProduct(numberOfRecipe);
  for(int i = 0; i < numberOfRecipe; ++i){
    int lin;
    cin >> lin;
    recipesIngredient[i].resize(lin);
    for(int j = 0; j < lin; ++j){
      int iin;
      cin >> iin;
      recipesIngredient[i][j] = iin;
    }
    int pin;
    cin >> pin;
    recipesProduct[i] = pin;
  }


  // 1. Create vertices with junction, stone

  // 2. Create cost 2d vector
  vector<vector<long long> > costJunctionToStone(numberOfJunction, vector<long long>(numberOfStone, LIMIT));

  // 3. Create vector of junctions connected to junction
  vector<vector<int> > connectedJunctions(numberOfJunction, vector<int>(0));
  for(int i = 0; i < numberOfStreet; ++i){
    int junctionA = streets[i].first - 1;
    int junctionB = streets[i].second - 1;
    connectedJunctions[junctionA].push_back(junctionB);
    connectedJunctions[junctionB].push_back(junctionA);
  }

  // 4. initialize costs
  for(int i = 0; i < numberOfJunction; ++i){
    for(int j = 0; j < stonesAtJunction[i].size(); ++j){
      int stoneIndex = stonesAtJunction[i][j] - 1;
      costJunctionToStone[i][stoneIndex] = 0;
    }
  }

  // 5. Create priority queue
  priority_queue <pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>> >, greater<pair<long long, pair<int, int> > > > costPairPriorityQueue;

  // 6. prepare a map from a stone to list of ingredients
  vector<vector<int> > recipesNeedingStone(numberOfStone, vector<int>(0));
  for(int i = 0; i < numberOfRecipe; ++i){
    for(int j = 0; j < recipesIngredient[i].size(); ++j){
      int ingredientIndex = recipesIngredient[i][j] - 1;
      recipesNeedingStone[ingredientIndex].push_back(i);
    }
  }

  // 7. initialize a map for ingredients available at a junction
//  vector<vector<bool> > ingredientsCollected(numberOfJunction, vector<bool>(numberOfStone, false));

  // 8. initialize the costPairPriority
  for(int i = 0; i < numberOfJunction; ++i){
    for(int j = 0; j < stonesAtJunction[i].size(); ++j){
      int stoneIndex = stonesAtJunction[i][j] - 1;
//      ingredientsCollected[i][stoneIndex] = true;
      costPairPriorityQueue.push(make_pair(0, make_pair(i, stoneIndex)));
    }
  }



  // ! maybe run the ingredients first
//  for(int currentRecipe = 0; currentRecipe < numberOfRecipe; ++currentRecipe){
//
//    for(int currentJunction = 0; currentJunction < numberOfJunction; ++currentJunction){
//
//      long long recipeCost = 0;
//      for(int k = 0; k < recipesIngredient[currentRecipe].size(); ++ k){
//        int currentIngredient = recipesIngredient[currentRecipe][k] - 1;
//        recipeCost += costJunctionToStone[currentJunction][currentIngredient];
//      }
//      int product = recipesProduct[currentRecipe] - 1;
//      if(recipeCost < costJunctionToStone[currentJunction][product]){
//        costJunctionToStone[currentJunction][product] = recipeCost;
//        costPairPriorityQueue.push(make_pair(recipeCost, make_pair(currentJunction, product)));
//      }
//
//
//    }
//  }

  // 5. dijkstra
  //    5.1 enqueue the 0 cost nodes
  //    5.2 while queue has nodes
  //        5.3 for each edge
  //            5.4 try to reduce cost by taking the stone to the new path, enqueue
  //            5.5 check the recipes using the new ingredients, if the new ingredients is used, create a new stone, enqueue
  while(!costPairPriorityQueue.empty()){
    pair<long long, pair<int, int> > currentPair = costPairPriorityQueue.top();
    costPairPriorityQueue.pop();
    long long currentCost = currentPair.first;
    int currentJunction = currentPair.second.first;
    int currentStone = currentPair.second.second;
//    cout << "! " << currentJunction + 1 << " " << currentStone + 1 << endl;

    // self jump
    {
      for(int currentRecipe = 0; currentRecipe  < recipesNeedingStone[currentStone].size(); ++currentRecipe ){
//        cout << "s? " << currentRecipe + 1 << endl;
        long long costToNewProduct = 0;
        for(int k = 0; k < recipesIngredient[currentRecipe].size(); ++k){
          int ingredient = recipesIngredient[currentRecipe][k] - 1;
          costToNewProduct += costJunctionToStone[currentJunction][ingredient];
        }
//        cout << "s= " << costToNewProduct << endl;
        int product = recipesProduct[currentRecipe] - 1;
        if(costToNewProduct < costJunctionToStone[currentJunction][product]){
          costJunctionToStone[currentJunction][product] = costToNewProduct;
//          cout << "$$$" << endl;
          costPairPriorityQueue.push(make_pair(costToNewProduct, make_pair(currentJunction, product)));
        }
      }
    }

    for(int i = 0; i < connectedJunctions[currentJunction].size(); ++i){
      int destinationJunction = connectedJunctions[currentJunction][i];
//      cout << "@ " << destinationJunction + 1 << endl;
      long long newCost = costJunctionToStone[currentJunction][currentStone] + 1;
      if(costJunctionToStone[destinationJunction][currentStone] > newCost){
        costJunctionToStone[destinationJunction][currentStone] = newCost;
//        cout << "$$$" << endl;
        costPairPriorityQueue.push(make_pair(newCost, make_pair(destinationJunction, currentStone)));
      }

      for(int currentRecipe = 0; currentRecipe  < recipesNeedingStone[currentStone].size(); ++currentRecipe ){
//        cout << "? " << currentRecipe + 1 << endl;
        long long costToNewProduct = 0;
        int recipeIndex = recipesNeedingStone[currentStone][currentRecipe];
        for(int k = 0; k < recipesIngredient[recipeIndex].size(); ++k){
          int ingredient = recipesIngredient[recipeIndex][k] - 1;
          costToNewProduct += costJunctionToStone[destinationJunction][ingredient];
        }
//        cout << "= " << costToNewProduct << endl;
        int product = recipesProduct[recipeIndex] - 1;
        if(costToNewProduct < costJunctionToStone[destinationJunction][product]){
          costJunctionToStone[destinationJunction][product] = costToNewProduct;
//          cout << "$$$" << endl;
          costPairPriorityQueue.push(make_pair(costToNewProduct, make_pair(destinationJunction, product)));
        }
      }
    }
  }

//
//  for(int i = 0; i < numberOfJunction; ++i){
//    for(int j = 0; j < numberOfStone; ++j){
//      cout << costJunctionToStone[i][j] << " " ;
//    }
//    cout << endl;
//  }
//    cout << endl;


  long long ans = LIMIT;
  for(int i = 0; i < numberOfJunction; ++i){
    ans = min(ans, costJunctionToStone[i][0]);
  }
  cout << (ans == LIMIT ? -1 : ans) << "\n";

  {
//  // 1. create lookup from junction to junction
//  vector<vector<long long> > costToJunction(numberOfJunction);
//  for(int i = 0; i < costToJunction.size(); ++i){
//    costToJunction[i].resize(numberOfJunction, LIMIT);
//  }
//
//  // 2. create imaginary lookup from junction to stone
//  vector<vector<long long> > costToStone(numberOfJunction);
//  for(int i = 0; i < costToStone.size(); ++i){
//    costToStone[i].resize(numberOfStone, LIMIT);
//  }
//
//  // 3. initialize self to 0 and the connected junctions to 1
//  for(int i = 0; i < numberOfJunction; ++i) costToJunction[i][i] = 0;
//  for(int i = 0; i < numberOfStreet; ++i){
//    int u = streets[i].first - 1;
//    int v = streets[i].second - 1;
//    costToJunction[u][v] = 1;
//    costToJunction[v][u] = 1;
//  }
//
//  // 4. initialize the junction with stone to 0
//  for(int i = 0; i < stonesAtJunction.size(); ++i){
//    for(int j = 0; j < stonesAtJunction[i].size(); ++j){
//      int stone = stonesAtJunction[i][j] - 1;
//      costToStone[i][stone] = 0;
//    }
//  }
//
//  // 5. run recipes
//  for(int junction = 0; junction < costToStone.size(); ++junction){
//    for(int recipe = 0; recipe < recipesProduct.size(); ++recipe){
//      long long sumOfIngredientCost = 0;
//      for(int r = 0; r < recipesIngredient[recipe].size(); ++r){
//        int item = recipesIngredient[recipe][r] - 1;
//        sumOfIngredientCost += costToStone[junction][item];
//      }
//
//      if(sumOfIngredientCost < LIMIT){
//        int product = recipesProduct[recipe] - 1;
//        costToStone[junction][product] = sumOfIngredientCost;
//      }
//
//    }
//  }
//
//  // 6. for every junction
//  //   7. for every stone
//  //     8. for every starting junction
//  //       9. for every street, check update for two junctions and stone
//  //       10.for every recipe, check update
//  bool hasUpdate = true;
//  for(int z = 0; z < numberOfJunction ; ++z){
//    if(!hasUpdate) break;
//    hasUpdate = false;
//    for(int currentJunction = 0; currentJunction < numberOfJunction; ++currentJunction){
//      for(int currentStreet = 0; currentStreet < numberOfStreet; ++currentStreet){
//        int junctionA = streets[currentSt reet].first - 1;
//        int junctionB = streets[currentStreet].second - 1;
//
//
//        if(costToJunction[currentJunction][junctionA] + 1 < costToJunction[currentJunction][junctionB]){
//          costToJunction[currentJunction][junctionB] = costToJunction[currentJunction][junctionA] + 1;
//          hasUpdate = true;
//        }
//        if(costToJunction[currentJunction][junctionB] + 1 < costToJunction[currentJunction][junctionA]){
//          costToJunction[currentJunction][junctionA] = costToJunction[currentJunction][junctionB] + 1;
//          hasUpdate = true;
//        }
//
//        for(int currentStone = 0; currentStone < numberOfStone; ++currentStone){
//          if(costToJunction[currentJunction][junctionA] + costToStone[junctionA][currentStone] < costToStone[currentJunction][currentStone]){
//            costToStone[currentJunction][currentStone] = costToJunction[currentJunction][junctionA] + costToStone[junctionA][currentStone];
//            hasUpdate = true;
//          }
//          if(costToJunction[currentJunction][junctionB] + costToStone[junctionB][currentStone] < costToStone[currentJunction][currentStone]){
//            costToStone[currentJunction][currentStone] = costToJunction[currentJunction][junctionB] + costToStone[junctionB][currentStone];
//            hasUpdate = true;
//          }
//        }
//
//        for(int currentRecipe = 0; currentRecipe < numberOfRecipe; ++currentRecipe){
//          long long sumOfIngredientCostA = 0;
//          long long sumOfIngredientCostB = 0;
//          for(int r = 0; r < recipesIngredient[currentRecipe].size(); ++r){
//            int item = recipesIngredient[currentRecipe][r] - 1;
//            sumOfIngredientCostA += costToStone[junctionA][item];
//            sumOfIngredientCostB += costToStone[junctionB][item];
//          }
//          // collect at A
//          int product = recipesProduct[currentRecipe] - 1;
//          if(sumOfIngredientCostA < costToStone[junctionA][product]){
//            costToStone[junctionA][product] = sumOfIngredientCostA;
//            hasUpdate = true;
//          }
//          // collect at B
//          if(sumOfIngredientCostB < costToStone[junctionB][product]){
//            costToStone[junctionB][product] = sumOfIngredientCostB;
//            hasUpdate = true;
//          }
//          // self at A
//          if(sumOfIngredientCostA + costToJunction[currentJunction][junctionA] < costToStone[currentJunction][product] ){
//            costToStone[currentJunction][product] = sumOfIngredientCostA + costToJunction[currentJunction][junctionA] ;
//            hasUpdate = true;
//          }
//          // self at B
//          if(sumOfIngredientCostB + costToJunction[currentJunction][junctionB] < costToStone[currentJunction][product] ){
//            costToStone[currentJunction][product] = sumOfIngredientCostB + costToJunction[currentJunction][junctionB] ;
//            hasUpdate = true;
//          }
//        }
//      }
//
//    }
//
//  }
//
//  long long ans = LIMIT;
//  for(int i = 0 ; i < numberOfJunction; ++i){
//    ans = min(ans, costToStone[i][0]);
//  }
//  cout << ans << endl;
  }

}

  // check status

//    cout << "\n";
//  for(int i = 0; i < numberOfJunction; ++i){
//    for(int j = 0; j < numberOfJunction; ++j){
//      cout << costToJunction[i][j] << " " ;
//    }
//    cout << "\n";
//  }
//
//    cout << "\n";
//  for(int i = 0; i < numberOfJunction; ++i){
//    for(int j = 0; j < numberOfStone; ++j){
//      cout << costToStone[i][j] << " " ;
//    }
//    cout << "\n";
//  }


int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
