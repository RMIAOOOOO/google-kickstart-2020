#include <bits/stdc++.h>
using namespace std;

void solve() {

  // 1. Get input
  string S;
  cin >> S;

  // 2. Find the word within the text
  vector<char> word_found(S.length(), ' ');
  for (int i = 0 ; i + 3 < S.length(); ++i) {
    if (S[i] == 'K' && S[i+1] == 'I' && S[i+2] == 'C' && S[i+3] == 'K') {
      word_found[i] = 'K';
    }
  }
  for (int i = 0 ; i + 4 < S.length(); ++i) {
    if (S[i] == 'S' && S[i+1] == 'T' && S[i+2] == 'A' && S[i+3] == 'R'&& S[i+4] == 'T'){
      word_found[i] = 'S';
    }
  }

  // 3. Iterate through the words, when find 'K', add it for matching for upcoming 'S',
  //      when find 'S', match up with previous 'K' and update answer.
  int ans = 0;
  int k_count = 0;
  for (int i = 0; i < word_found.size() ; ++i) {
    if (word_found[i] == 'K'){
      k_count ++;
    } else if(word_found[i] == 'S') {
      ans += k_count;
    }
  }

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
