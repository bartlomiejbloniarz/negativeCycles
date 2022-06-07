#!/bin/bash
./test_hamilton.sh 20000 100000 0 32000
mv test_hamilton/result.csv test_hamilton/result_0_32000.csv

./test_hamilton.sh 20000 100000 -1000 32000
mv test_hamilton/result.csv test_hamilton/result_-1000_32000.csv

./test_hamilton.sh 20000 100000 -32000 32000
mv test_hamilton/result.csv test_hamilton/result_-32000_32000.csv

./test_hamilton.sh 20000 100000 -64000 32000
mv test_hamilton/result.csv test_hamilton/result_-64000_32000.csv
