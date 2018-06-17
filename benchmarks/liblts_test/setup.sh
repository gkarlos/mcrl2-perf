MCRL2_HOME=../../mcrl2-release/mcrl2
LIB_DIR=$MCRL2_HOME/libraries/lts
BENCH_DIR=$LIB_DIR/benchmarks
BIN=mcrl2_perf_benchmark_liblts_test

#Update the CMakeLists.txt of the LTSlib
echo "add_subdirectory(benchmarks)" >> $LIB_DIR/CMakeLists.txt
#Create a benchmarks dir to hold the sources under the LTSlib directory
rm -rf $BENCH_DIR && mkdir $BENCH_DIR
#Declare the source files
declare -a sources=(test.cpp)
#Copy the sources
for f in "${sources[@]}"; do
  cp $f $BENCH_DIR/
done
#copy the CMakeLists.txt for this benchmark
cp CMakeLists.txt $BENCH_DIR/

currdir=$(pwd)

cd $MCRL2_HOME/build
cmake .. && make -j6
cd $currdir

echo
echo "[+] Running $BIN"
echo

$MCRL2_HOME/build/stage/bin/$BIN

### CLEANUP ###

# Remove the benchmarks dir
rm -rf $BENCH_DIR
# Restore CMakeLists.txt
head -n -1 $LIB_DIR/CMakeLists.txt > temp.txt && mv temp.txt $LIB_DIR/CMakeLists.txt


# for filename in ../../files/*; do
#   f=$(head -n 1 $filename)
#   rm -f "$MCRL2_HOME/${f:1}"
#   cp $filename "$MCRL2_HOME/${f:1}"
#   echo ${f:1}
# done
#
# #rm -rf $LTS_LIB/benchmark && mkdir $LTS_LIB/benchmark
#
# rm -rf $MCRL2_HOME/benchmarks/ && make $MCRL2_HOME/benchmarks/

# cp test.cpp $LTS_LIB/benchmark/test.cpp
# cp CMakeLists.txt $LTS_LIB/benchmark/CMakeLists.txt
#
# curr = $(pwd)
# cd $MCRL2_HOME/build/ && cmake .. && make -j4
# cd $curr
