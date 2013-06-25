#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
int number_of_ways(const int &n, const int &m) {
  vector<vector<int>> A(n, vector<int>(m, 0));
  A[0][0] = 1;  // 1 way to start from (0, 0)
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      A[i][j] += (i < 1 ? 0 : A[i - 1][j]) + (j < 1 ? 0 : A[i][j - 1]);
    }
  }
  return A.back().back();
}
// @exclude

int check_ans(int n, int k) {
  vector<vector<int>> table(n + 1, vector<int>(k + 1));
  // Basic case: C(i, 0) = 1
  for (int i = 0; i <= n; ++i) {
    table[i][0] = 1;
  }
  // Basic case: C(i, i) = 1
  for (int i = 1; i <= k; ++i) {
    table[i][i] = 1;
  }
  // C(i, j) = C(i - 1, j) + C(i - 1, j - 1)
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i && j <= k; ++j) {
      table[i][j] = table[i - 1][j] + table[i - 1][j - 1];
    }
  }
  return table[n][k];
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else {
      n = 1 + (rand() % 10);
      m = 1 + (rand() % 10);
    }
    cout << "n = " << n << ", m = " << m << ", number of ways = " << number_of_ways(n, m) << endl;
    assert(check_ans(n + m - 2, m - 1) == number_of_ways(n, m));
    if (argc == 3) {
      break;
    }
  }
  return 0;
}
