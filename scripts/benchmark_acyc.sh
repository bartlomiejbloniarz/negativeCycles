#!/bin/bash
./test_acyc.sh 5000 10000 0 32000

./test_acyc.sh 5000 10000 -1000 32000

./test_acyc.sh 5000 10000 -32000 32000

./test_acyc.sh 5000 10000 -64000 32000

./test_acyc.sh 5000 5000 -32000 32000

./test_acyc.sh 5000 5010 -32000 32000

./test_acyc.sh 5000 5100 -32000 32000
