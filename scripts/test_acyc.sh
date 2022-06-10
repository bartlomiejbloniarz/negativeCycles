#!/bin/bash
mkdir -p test_acyc1
cd test_acyc1

echo BFCF > BFCF_t.out
echo BFCS > BFCS_t.out
#echo goldberg-radzik > goldberg-radzik.out
echo goldberg-radzik-simplified > goldberg-radzik-simplified_t.out
echo goldfarb-hao-kai > goldfarb-hao-kai_t.out
echo tarjan > tarjan_t.out
echo tarjan-simple > tarjan-simple_t.out
echo tarjan-with-update > tarjan-with-update_t.out

echo BFCF > BFCF_c.out
echo BFCS > BFCS_c.out
#echo goldberg-radzik > goldberg-radzik.out
echo goldberg-radzik-simplified > goldberg-radzik-simplified_c.out
echo goldfarb-hao-kai > goldfarb-hao-kai_c.out
echo tarjan > tarjan_c.out
echo tarjan-simple > tarjan-simple_c.out
echo tarjan-with-update > tarjan-with-update_c.out

for i in {1..10}
do
  echo $i
  seed=$(python3 ../rand)
  ../cherkassky_goldberg_radzik_generators/spacyc $1 $2 $seed -lm$3 -ll$4 > test_raw.in
  python3 ../parser.py > test.in

  for j in {1..5}
  do
    ../output/BFCF.o -t < test.in 2>> BFCF_t.out
    ../output/BFCS.o -t < test.in 2>> BFCS_t.out
    #../output/goldberg-radzik.o -$5 < test.in 2>> goldberg-radzik.out
    ../output/goldberg-radzik-simplified.o -t < test.in 2>> goldberg-radzik-simplified_t.out
    ../output/goldfarb-hao-kai.o -t < test.in 2>> goldfarb-hao-kai_t.out
    ../output/tarjan.o -t < test.in 2>> tarjan_t.out
    ../output/tarjan-simple.o -t < test.in 2>> tarjan-simple_t.out
    ../output/tarjan-with-update.o -t < test.in 2>> tarjan-with-update_t.out
  done
  ../output/BFCF.o -c < test.in 2>> BFCF_c.out
  ../output/BFCS.o -c < test.in 2>> BFCS_c.out
  #../output/goldberg-radzik.o -$5 < test.in 2>> goldberg-radzik.out
  ../output/goldberg-radzik-simplified.o -c < test.in 2>> goldberg-radzik-simplified_c.out
  ../output/goldfarb-hao-kai.o -c < test.in 2>> goldfarb-hao-kai_c.out
  ../output/tarjan.o -c < test.in 2>> tarjan_c.out
  ../output/tarjan-simple.o -c < test.in 2>> tarjan-simple_c.out
  ../output/tarjan-with-update.o -c < test.in 2>> tarjan-with-update_c.out
done
#paste *_t.out > result_t.csv
#paste *_c.out > result_c.csv
paste *_t.out > result_$1_$2_$3_$4_t.csv
paste *_c.out > result_$1_$2_$3_$4_c.csv
