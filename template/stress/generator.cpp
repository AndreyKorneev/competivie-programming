#include "algs/all.h"

int main(int argc, char** argv) {
  if (argc == 2) {
    std::srand(std::stoi(argv[1]));
  } else {
    std::srand(std::time(nullptr));
  }
  ios_base::sync_with_stdio(false);
  int n = rand_int(10);
  for (int i = 0; i < n; ++i) cout << rand_int(10) << ' ';
  return 0;
}
