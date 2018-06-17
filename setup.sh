GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

DEBUG_DIR="mcrl2-debug"
RELEASE_DIR="mcrl2-release"

rm -rf $DEBUG_DIR $RELEASE_DIR

if [ ! -d "$DEBUG_DIR" ] || [ ! -d "$RELEASE_DIR" ]; then
  #### DOWNLOAD AND COMPILE MCRL2 ####
  echo
  echo "###############     Cloning   mCRL2     ###############"
  echo
  git clone https://github.com/mCRL2org/mCRL2 $DEBUG_DIR/mcrl2
  git clone https://github.com/mCRL2org/mCRL2 $RELEASE_DIR/mcrl2
fi

echo
echo "-------------------------------------------------------"
echo "###############  Building  mcrl2-debug  ###############"
echo "-------------------------------------------------------"
echo

cd $DEBUG_DIR/mcrl2/build/
cmake .. -DCMAKE_BUILD_TYPE=Debug && make -j6
rm -f ../../mcrl22lps ../../lps2lts ../../pbes2bool
cp stage/bin/mcrl22lps stage/bin/lps2lts stage/bin/pbes2bool ../../

echo
echo "-------------------------------------------------------"
echo "##############  Building  mcrl2-release  ##############"
echo "-------------------------------------------------------"
echo

cd ../../../$RELEASE_DIR/mcrl2/build
cmake .. -DCMAKE_BUILD_TYPE=Debug && make -j6
rm -f ../../mcrl22lps ../../lps2lts ../../pbes2bool
cp stage/bin/mcrl22lps stage/bin/lps2lts stage/bin/pbes2bool ../../
