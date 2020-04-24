update_headers() {
  OUT_FILE="algs/all.h"
  find -s algs -name "*.h" -maxdepth 1 | grep -v "$OUT_FILE" > $OUT_FILE
  find -s algs -name "*.h" -mindepth 2  >> $OUT_FILE
  sed -i '' -e 's/^/#include "/' -e 's/$/"/' $OUT_FILE
}

prepare_fs() {
  update_headers
  mkdir -p generated
  mkdir -p obj
}

compile() {
  filename="$(basename -s ".cpp" $1)"
  ./translate/__main__.py "$1" "generated/${filename}.cpp"
  g++-9 -std=gnu++1z -I . -O2 -D LOCAL "generated/${filename}.cpp" -o "obj/${filename}.out"
}

run() {
  compile main.cpp
  timeout 2s obj/main.out < input.txt &> output.txt
  unifdef -ULOCAL generated/main.cpp | pbcopy
  # cat output.txt
  echo "Done"
}

stress() {
  compile main.cpp
  compile stress/slow.cpp
  compile stress/generator.cpp
  compile stress/checker.cpp

  for i in {1..1000}
  do
    if (( $i % 50 == 0 ))
    then
      echo "Test #$i"
    fi
    timeout 2s obj/generator.out > input.txt 2> /dev/null
    timeout 2s obj/main.out < input.txt > output.txt 2> /dev/null
    timeout 2s obj/slow.out < input.txt > stress/output.txt 2> /dev/null
    if ! cmp -s output.txt stress/output.txt >/dev/null 2>&1 ; then
      echo "Diff found. Test #$i"
      return;
    fi
  done
  echo "No diff found"
}

tmp() {
  compile main.cpp
  compile stress/generator.cpp
  for i in {1..10000}
  do
    if (( $i % 50 == 0 ))
    then
      echo "Test #$i"
    fi
    n=$((5 + $(($RANDOM % 5)) ))
    m=$(($n + $(($RANDOM % 5)) ))
    n=$((1000 + $(($RANDOM % 5000)) ))
    m=$(($n + $(($RANDOM % 5000)) ))
    #echo "$n $m"
    if ! obj/graph_generator.out "$n" "$m" > stress/graph.txt ; then
      continue;
    fi
    timeout 2s obj/generator.out < stress/graph.txt > input.txt 2> /dev/null
    if ! obj/main.out < input.txt > output.txt 2> /dev/null ; then
      echo "Diff found. Test #$i"
      return;
    fi
  done
  echo "No diff found"
}

save() {
  mkdir -p $1
  cp -r stress "$1/"
  cp main.cpp "$1/"
}

new() {
    cp -r template/ .
}

main() {
  prepare_fs
  case "$1" in
          run)
                  run
                  ;;
          stress)
                  stress
                  ;;
          new)
                  new
                  ;;
          tmp)
                  tmp
                  ;;
          save)
                  save $2
                  ;;
      *)
          echo "Usage: $0 {run|new|save|stress}"
          exit 1
  esac
}

main "$@"
