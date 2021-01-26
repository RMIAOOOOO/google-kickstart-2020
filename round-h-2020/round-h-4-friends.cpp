#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  int N, Q;
  cin >> N >> Q ;
  vector<string> names(N);
  vector<pair<int, int> > queries(Q);
  for (int i = 0 ; i < N; ++i) {
    cin >> names[i];
  }
  for (int i = 0 ; i < Q; ++i) {
    int a, b;
    cin >> a >> b;
    queries[i] = make_pair(a-1, b-1);
  }

  // 2. Create a char to char distance lookup table.
  vector<vector<int> > char_to_char_distance(26, vector<int>(26, 999));
    // 2.1  Initialize it by lowering characters appearing in same name to 1, and same character to 0.
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < names[i].length() - 1; ++ j) {
      for (int k = j + 1; k < names[i].length(); ++ k) {
        int firstCharIndex = names[i][j] - 'A';
        int secondCharIndex = names[i][k] - 'A';
        char_to_char_distance[firstCharIndex][secondCharIndex] = 1;
        char_to_char_distance[secondCharIndex][firstCharIndex] = 1;
      }
    }
  }
  for (int i = 0; i < 26; ++i) char_to_char_distance[i][i] = 0;

    // 2.2 Find all pairs shortest path distance with Floyd-Warshall algorithm
  for (int k = 0; k < 26; ++k) {
      for (int i = 0; i < 26; ++i) {
          for (int j = 0; j < 26; ++j) {
            char_to_char_distance[i][j] = min(char_to_char_distance[i][j], char_to_char_distance[i][k] + char_to_char_distance[k][j]);
          }
      }
  }

  // 3. for every pair of query, iterate through every pair of character, update the closest distance
  for (int i = 0; i < Q; ++i) {

    string first_name = names[queries[i].first];
    string second_name = names[queries[i].second];

    int answer = 999;
    for (int j = 0; j < first_name.length(); ++j) {
      for (int k = 0; k < second_name.length(); ++k) {
        int first_char_index = first_name[j] - 'A';
        int second_char_index = second_name[k] - 'A';
        int cost = char_to_char_distance[first_char_index][second_char_index];
        answer = min(cost, answer);
      }
    }

    answer = answer == 999 ? -1 : answer + 2;
    cout << answer << " ";

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
