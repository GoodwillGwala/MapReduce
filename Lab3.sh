set -e

echo Cleaning working directory

echo

make clean


echo Building Lab...
echo
make
echo Building Done...
echo



echo Running Lab...
echo


echo Please enter list of input files
echo
read inputFiles


echo
echo Please enter output file
echo
read outputFile


./main.out $inputFiles $outputFile
