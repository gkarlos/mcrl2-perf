#!/bin/bash

BIN="../../mcrl2-release/mcrl2/build/stage/bin/"
LPSCONSTELM="$BIN/lpsconstelm"
LPSPARELM="$BIN/lpsparelm"
LPSSUMINST="$BIN/lpssuminst"
MCRL22LPS="$BIN/mcrl22lps"
LPS2LTS="$BIN/lps2lts"

TIME_PARSER="../../timeparse.py"
SUMMARY_CALC="../../summary.py"
PLOT="plot.py"

TCMALLOC="/usr/lib/libtcmalloc.so.4"
JEMALLOC="/usr/local/lib/libjemalloc.so"

#rm -rf results*

export NRUNS=15

declare -a flags=("" "-rjittyc" "-rjittyc --cached --prune")
declare -a sizes=("small" "medium")

curr=$(pwd)

cleanup()
{
  echo "Cleaning up..."
  rm -f *.bin *.o *.cpp *.log
  rm -rf tmp
  stty icanon echo echok
  exit 1
}

now()
{
  python -c 'import time; print time.time()'
}

create_results_files()
{
  basename=`basename "$2"`

  resultsfolder=results-$1/$basename

  #mkdir $resultsfolder

  raw_default=$resultsfolder/default.raw.csv
  raw_tcmalloc=$resultsfolder/tcmalloc.raw.csv
  raw_jemalloc=$resultsfolder/jemalloc.raw.csv

  summary_default=$resultsfolder/default.summary.csv
  summary_tcmalloc=$resultsfolder/tcmalloc.summary.csv
  summary_jemalloc=$resultsfolder/jemalloc.summary.csv

  # memory_default=$resultsfolder/default.memory.csv
  # memory_jemalloc=$resultsfolder/jemalloc.memory.csv
  # memory_tcmalloc=$resultsfolder/tcmalloc.memory.csv

  #rm -f $inputfolder/$basename.lps
  #${MCRL22LPS} -fD $2 2> /dev/null | ${LPSCONSTELM} | ${LPSPARELM} | ${LPSSUMINST} > $inputfolder/$basename.lps

  #rm -f $raw_default $summary_default $raw_tcmalloc $summary_tcmalloc $raw_jemalloc $summary_jemalloc
  #touch $raw_default $summary_default $raw_tcmalloc $summary_tcmalloc $raw_jemalloc $summary_jemalloc
}

trap 'cleanup' INT 20

echo
echo "[+] Running Benchmark: $(basename $(pwd))"

START=$(now)

for size in "${sizes[@]}"; do

  echo && echo "[+] $size inputs:"

  inputfolder="input-$size"

  #mkdir results-$size

  for file in $inputfolder/*.mcrl2; do

    create_results_files $size $file

    # for flag in "${flags[@]}"; do # for each flag
    #   # massif_default=$resultsfolder/$basename$(  echo $flag | tr -d ' ' | tr '-' '_').default.massif.out
    #   # massif_jemalloc=$resultsfolder/$basename$(  echo $flag | tr -d ' ' | tr '-' '_').jemalloc.massif.out
    #
    #   if [ "$flag" == "" ]; then
    #     echo "-default" >> $raw_default
    #     echo "-default" >> $raw_jemalloc
    #     echo "-default" >> $raw_tcmalloc
    #
    #     echo "-default" >> $summary_default
    #     echo "-default" >> $summary_jemalloc
    #     echo "-default" >> $summary_tcmalloc
    #   else
    #     echo "$flag" >> $raw_default
    #     echo "$flag" >> $raw_jemalloc
    #     echo "$flag" >> $raw_tcmalloc
    #
    #     echo "$flag" >> $summary_default
    #     echo "$flag" >> $summary_jemalloc
    #     echo "$flag" >> $summary_tcmalloc
    #   fi
    #
    #   # DEFAULT ALLOCATOR time
    #   echo "    > Running $basename.lps $flag | Default Allocator"
    #   for i in $(seq 1 $NRUNS); do
    #     { time $curr/${LPS2LTS} ${flag} $curr/$inputfolder/$basename.lps; } 2>&1 | python ${TIME_PARSER} >> $raw_default
    #   done
    #   echo "="  >> $raw_default
    #   # valgrind --tool=massif --massif-out-file=$massif_default ${LPS2LTS} ${flag} $inputfolder/$basename.lps #2> /dev/null
    #   # grep mem_heap_B $massif_default | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1 >> $memory_default
    #
    #
    #   # JEMALLOC time
    #   echo "    > Running $basename.lps $flag | JEmalloc"
    #   export LD_PRELOAD=$JEMALLOC
    #   for i in $(seq 1 $NRUNS); do
    #     { time $curr/${LPS2LTS} ${flag} $curr/$inputfolder/$basename.lps; } 2>&1 | python ${TIME_PARSER} >> $raw_jemalloc
    #   done
    #   echo "="  >> $raw_jemalloc
    #   unset LD_PRELOAD
    #
    #   # TCMALLOC time
    #   echo "    > Running $basename.lps $flag | TCmalloc"
    #   export LD_PRELOAD=$TCMALLOC
    #   for i in $(seq 1 $NRUNS); do
    #     { time $curr/${LPS2LTS} ${flag} $curr/$inputfolder/$basename.lps; } 2>&1 | python ${TIME_PARSER} >> $raw_tcmalloc
    #   done
    #   echo "="  >> $raw_tcmalloc
    #   unset LD_PRELOAD
    # done

    python ${SUMMARY_CALC} $raw_default  $summary_default
    python ${SUMMARY_CALC} $raw_jemalloc $summary_jemalloc
    python ${SUMMARY_CALC} $raw_tcmalloc $summary_tcmalloc
  done

  python ${PLOT} results-$size

done



END=$(now)
DIFF=$(echo "$END - $START" | bc)
echo
echo "[+] Benchmark $(basename $(pwd)) finished after $DIFF seconds"

rm -rf tmp
