#include "algs/all.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "Expected 3 arguments <input> <jury_answer> <answer>" << endl;
    return 1;
  }
  ifstream input_stream(argv[1]);
  ifstream correct_stream(argv[2]);
  ifstream output_stream(argv[3]);
  cerr << "Default checker" << endl;
  return 1;
}
