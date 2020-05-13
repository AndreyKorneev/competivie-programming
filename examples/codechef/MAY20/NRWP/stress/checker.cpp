#include "algs/all.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "Expected 3 arguments <input> <jury_answer> <answer>" << endl;
    return 1;
  }
  ifstream input_stream(argv[1]);
  ifstream correct_stream(argv[2]);
  ifstream output_stream(argv[3]);
  int a, b;
  correct_stream >> a;
  output_stream >> b;
  if (a != b) {
    cerr << "Found " << b << " . Expected " << a << endl;
    return 1;
  }
  return 0;
}
