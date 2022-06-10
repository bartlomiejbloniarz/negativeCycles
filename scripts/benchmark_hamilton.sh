#!/bin/bash
./test_hamilton.sh 20000 100000 0 32000

./test_hamilton.sh 20000 100000 -1000 32000

./test_hamilton.sh 20000 100000 -32000 32000

./test_hamilton.sh 20000 100000 -64000 32000

./test_hamilton.sh 20000 20000 -32000 32000

./test_hamilton.sh 20000 20010 -32000 32000

./test_hamilton.sh 20000 20100 -32000 32000
