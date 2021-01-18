#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<iostream>
#include<math.h>
using namespace std;

long long getResult (long long num){
  vector<long long> record;
  record.resize(20, 0);
  if(num <= 9) return (num+1)/2;
  if(num == 10) return 6;

  long long ans = 5;
  long long base = 10;
  long long partialSum = 5;
  int recordIndex = 1;
  record[1] = 5;

  while(recordIndex <= 17 && base*10 <= num ){
    partialSum *= 5;
    record[++recordIndex] = partialSum;
    ans += partialSum;
    base *= 10;
  }

//  cout << "recordIndex: " << recordIndex << "\n";

  int TotalDigit = 1;
  long long digitCountingBase = 1;
  while(TotalDigit <= 18 && digitCountingBase * 10 <= num){
    TotalDigit += 1;
    digitCountingBase *= 10;
  }

//  cout << "totalDigit: " << TotalDigit<< "\n";
//  cout << "total digit: " << TotalDigit << "\n";


  int currentDigitIndex = TotalDigit;
  bool currentDigitOdd = true;
  while(currentDigitIndex >= 1){
    long long currentDigit = num/base;
//    cout << "!" << currentDigitIndex << " " ;
    num = num - currentDigit * base;
    base /= 10;
    if(currentDigitOdd){
      if(currentDigit == 0) return ans;
      if(currentDigitIndex == 1){
        ans += (currentDigit + 1) / 2;
        break;
      }
      long long expandableDigit = currentDigit / 2;
      ans += expandableDigit * record[currentDigitIndex-1];
//      cout << "aa";
      if(currentDigit % 2 == 0) break;
    }else{
//      cout << "bb";
//      if(currentDigit == 0) return ans;
      if(currentDigitIndex == 1){
        ans += (currentDigit + 2) / 2;
        break;
      }
      long long expandableDigit = (currentDigit+1) / 2;
      ans += expandableDigit * record[currentDigitIndex-1];
      if(currentDigit % 2 == 1) break;
    }
    currentDigitIndex --;
    currentDigitOdd = !currentDigitOdd;
  }

  return ans;

}

void solve(){
  long long L, R;
  cin >> L >> R;
  long long left = getResult(L - 1);
  long long right = getResult(R);
  cout << right - left << "\n";
//  cout << right << "\n";
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i){
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
