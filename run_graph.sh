./run.sh compile main.cpp
cp obj/main.out obj/main_g_2.out

echo "Compile Done"

function compare() {
  first=$(obj/checker.out $1 $2)
  second=$(obj/checker.out $1 $3)
  echo "First: $first"
  echo "Second: $second"
  if [[ $first > $second ]] ; then
    echo "OK" $first $second
    cp -f $2 $3
  fi
}

for i in {0..3}
do
  in="/Users/korneev/Downloads/icpc-challenge-2020-tests/a$i.in"
  candidate="/tmp/b$i.out"
  best="generated/b$i.out"
  obj/main_g_2.out $i < $in > $candidate
  compare $in $candidate $best
  echo "$i Done"
done
