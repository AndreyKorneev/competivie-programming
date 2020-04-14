update_headers() {
  OUT_FILE="algs/all.h"
  find -s algs -name "*.h" -maxdepth 1 | grep -v "$OUT_FILE" > $OUT_FILE
  find -s algs -name "*.h" -mindepth 2  >> $OUT_FILE
  sed -i -e 's/^/#include "/' $OUT_FILE
  sed -i -e 's/$/"/' $OUT_FILE
}

run() {
  update_headers
  ./translate/__main__.py main.cpp main_.cpp
  g++-9 -std=gnu++1z -O2 -D LOCAL main_.cpp -o a.out
  timeout 2s ./a.out < input.txt &> output.txt
  cat main_.cpp | pbcopy
  # cat output.txt
  echo "Done"
}

new() {
    echo '' > input.txt
    echo '' > output.txt
    cp template.cpp main.cpp
}

case "$1" in
        run)
                run
                ;;
        new)
                new
                ;;
    *)
        echo "Usage: $0 {run|new}"
        exit 1
esac
