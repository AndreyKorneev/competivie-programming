#include "algs/all.h"

int main(int argc, char** argv) {
  int testCase = 0;
  if (argc == 2) {
    testCase = std::stoi(argv[1]);
    std::srand(testCase);
  } else {
    std::srand(std::time(nullptr));
  }
  ios_base::sync_with_stdio(false);
  int n = rand_int(10);
  for (int i = 0; i < n; ++i) cout << rand_int(10) << ' ';
  return 0;
}
