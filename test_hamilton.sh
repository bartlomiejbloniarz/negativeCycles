#!/bin/bash
mkdir -p test_hamilton
cd test_hamilton

echo BFCF > BFCF.out
echo BFCS > BFCS.out
echo goldberg-radzik > goldberg-radzik.out
echo goldfarb-hao-kai > goldfarb-hao-kai.out
echo tarjan > tarjan.out
echo tarjan-simple > tarjan-simple.out
echo tarjan-with-update > tarjan-with-update.out

for j in {1..10}
do
seed=$(python3 ../rand)
../cherkassky_goldberg_radzik_generators/sprand $1 $2 $seed -lm$3 -ll$4 > test_raw.in
python3 ../parser.py > test.in

for j in {1..1}
do
#../output/BFCF.o -b < test.in >> BFCF.out
echo BFCS
../output/BFCS.o -b < test.in #>> BFCS.out
#../output/goldberg-radzik.o -b < test.in >> goldberg-radzik.out
#../output/goldfarb-hao-kai.o -b < test.in >> goldfarb-hao-kai.out
echo tarjan
../output/tarjan.o -b < test.in #>> tarjan.out
#../output/tarjan-simple.o -b < test.in >> tarjan-simple.out
echo tarjan-with-update
../output/tarjan-with-update.o -b < test.in #>> tarjan-with-update.out
done
done
paste *.out > result.csv
