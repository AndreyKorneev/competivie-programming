#DEBUG_FLAGS=(-g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL -rdynamic)
MAIN_TIMEOUT="2s"
DEBUG_FLAGS=(-g -fsanitize=address -fsanitize=undefined -DLOCAL -rdynamic)
STRESS_TEST_COUNT=10000
STRESS_TEST_OUTPUT_EACH=1000
STRESS_FAIL_ON_INCORRECT_TEST=true

strip_debug_code() {
  if command -v unifdef > /dev/null; then
    unifdef -ULOCAL $1 > $2
  else
    cat $1 > $2
  fi
}

update_headers() {
  OUT_FILE="algs/all.h"
  find -s algs -name "*.h" -maxdepth 1 | grep -v "$OUT_FILE" > $OUT_FILE
  find -s algs -name "*.h" -mindepth 2 >> $OUT_FILE
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
  strip_debug_code "generated/${filename}.cpp" "generated/${filename}_no_debug.cpp"
  g++-9 -std=gnu++1z -I . -O2 -D LOCAL "generated/${filename}.cpp" -o "obj/${filename}.out"
}

run() {
  compile main.cpp
  if ! timeout ${MAIN_TIMEOUT} obj/main.out < input.txt &> output.txt ; then
    echo "Failed; running in debug mode"
    g++-9 -std=gnu++1z "${DEBUG_FLAGS[@]}" "generated/main.cpp" -o "obj/main_debug.out"
    timeout ${MAIN_TIMEOUT} obj/main_debug.out < input.txt &> output.txt
  else
    cat "generated/main_no_debug.cpp" | pbcopy
    echo "Done"
  fi
}

stress() {
  compile main.cpp
  compile stress/slow.cpp
  compile stress/generator.cpp
  compile stress/checker.cpp

  for (( i=1; i<=${STRESS_TEST_COUNT}; i++ )); do
    if (($i % ${STRESS_TEST_OUTPUT_EACH} == 0)); then
      echo "Test #$i"
    fi
    timeout 2s obj/generator.out $i > input.txt 2> /dev/null
    if ! timeout 2s obj/slow.out < input.txt > stress/output.txt 2> /dev/null; then
      echo "Incorrect test #$i"
      if [ "${STRESS_FAIL_ON_INCORRECT_TEST}" = true ] ; then
        return
      else
        continue
      fi
    fi
    timeout ${MAIN_TIMEOUT} obj/main.out < input.txt > output.txt 2> /dev/null
    if ! cmp -s output.txt stress/output.txt > /dev/null 2>&1; then
      if ! timeout 2s obj/checker.out input.txt stress/output.txt output.txt  &> stress/checker.txt; then
        echo "Diff found. Test #$i"
        cat stress/checker.txt
        return;
      fi
    fi
  done
  echo "No diff found"
}

# Example of usage both: external graph generator and custom generator.
# [jngen](https://github.com/ifsmirnov/jngen) - super useful generators for stress testing.
tmp() {
  compile main.cpp
  compile stress/generator.cpp
  for i in {1..10000}; do
    if (($i % 50 == 0)); then
      echo "Test #$i"
    fi
    n=$((5 + $(($RANDOM % 5))))
    m=$(($n + $(($RANDOM % 5))))
    n=$((1000 + $(($RANDOM % 5000))))
    m=$(($n + $(($RANDOM % 5000))))
    #echo "$n $m"
    if ! obj/graph_generator.out "$n" "$m" > stress/graph.txt; then
      continue
    fi
    timeout 2s obj/generator.out < stress/graph.txt > input.txt 2> /dev/null
    if ! obj/main.out < input.txt > output.txt 2> /dev/null; then
      echo "Diff found. Test #$i"
      return
    fi
  done
  echo "No diff found"
}

save() {
  mkdir -p $1
  cp -r stress "$1/"
  cp main.cpp "$1/"
  cp input.txt "$1/"
  cp output.txt "$1/"
}

restore() {
  cp -r "$1/" .
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
    restore)
      restore $2
      ;;
    compile)
      compile $2
      ;;
    *)
      echo "Usage: $0 {run|new|compile|save|restore|stress}"
      exit 1
      ;;
  esac
}

main "$@"
