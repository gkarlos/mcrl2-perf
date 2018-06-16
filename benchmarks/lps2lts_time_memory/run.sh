#!/bin/bash

BIN="../../mcrl2-release/mcrl2/build/stage/bin/"
LPSCONSTELM="$BIN/lpsconstelm"
LPSPARELM="$BIN/lpsparelm"
LPSSUMINST="$BIN/lpssuminst"
MCRL22LPS="$BIN/mcrl22lps"
LPS2LTS="$BIN/lps2lts"

TIME_PARSER="../../timeparse.py"
SUMMARY_CALC="../../summary.py"
PLOT="../../plot.py"

rm -rf results && mkdir results

export NRUNS=10

declare -a flags=("" "-rjittyc" "-rjittyc --cached --prune")
declare -a sizes=("small" "medium" "large")

curr=$(pwd)

cleanup() {
  echo "Cleaning up..."
  cd $cure
  rm -f *.bin *.o *.cpp *.log
  stty icanon echo echok
  exit 1
}

now() {
  python -c 'import time; print time.time()'
}

trap 'cleanup' INT 20

echo
echo "[+] Running Benchmark: $(basename $(pwd))"
echo

START=$(now)

for size in "${sizes[@]}"; do
  echo "[+] $size inputs:"

  inputfolder="input-$size"
  resultsfolder=results/$size

  mkdir $resultsfolder

  for file in $inputfolder/*.mcrl2; do
    basename=`basename "$file"`
    raw=$resultsfolder/$basename.raw.csv
    summary=$resultsfolder/$basename.summary.csv
    memory=$resultsfolder/$basename.memory.csv

    # Create the lps2lts input file
    rm -f $inputfolder/$basename.lps
    ${MCRL22LPS} -fD $file 2> /dev/null | ${LPSCONSTELM} | ${LPSPARELM} | ${LPSSUMINST} > $inputfolder/$basename.lps

    #Create raw/summary csv for that input
    rm -f $raw $summary $memory && touch $raw $summary $memory

    for flag in "${flags[@]}"; do
      if [ "$flag" == "" ]; then
        echo "-default" >> $raw
        echo "-default" >> $summary
      else
        echo "$flag" >> $raw
        echo "$flag" >> $summary
      fi

      echo "User,Sys" >> $raw

      echo "    > Running $basename.lps $flag"

      for i in $(seq 1 $NRUNS); do
        { time $curr/${LPS2LTS} ${flag} $curr/$inputfolder/$basename.lps; } 2>&1 | python ${TIME_PARSER} >> $resultsfolder/$basename.raw.csv
      done

      echo "="        >> $resultsfolder/$basename.raw.csv
      valgrind --tool=massif --massif-out-file=$resultsfolder/"${basename}${flag}".massif.out ${LPS2LTS} ${flag} $inputfolder/$basename.lps 2> /dev/null
      grep mem_heap_B $resultsfolder/"${basename}${flag}".massif.out | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1 >> $memory
    done

    python ${SUMMARY_CALC} $resultsfolder/$basename.raw.csv $resultsfolder/$basename.summary.csv
  done

  python ${PLOT} $resultsfolder
done



END=$(now)
DIFF=$(echo "$END - $START" | bc)
echo
echo "[+] Benchmark $(basename $(pwd)) finished after $DIFF seconds"
