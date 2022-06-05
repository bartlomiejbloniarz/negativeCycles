RM = rm -f
MD	:= mkdir -p
MF := touch
CP := cp
RMDIR := rm -r -f
SYMLINK := ln -s

TESTER=bellman-ford-break

all: output bellman-ford bellman-ford-break saranya-shobhalatha BFCF BFCS goldfarb-hao-kai goldberg-radzik tarjan tarjan-with-update

output:
	$(MD) output

bellman-ford: output output/bellman-ford.o

bellman-ford-break: output output/bellman-ford-break.o

saranya-shobhalatha: output output/saranya-shobhalatha.o

BFCF: output output/BFCF.o

BFCS: output output/BFCS.o

goldfarb-hao-kai: output output/goldfarb-hao-kai.o

goldberg-radzik: output output/goldberg-radzik.o

tarjan: output output/tarjan.o

tarjan-with-update: output output/tarjan-with-update.o

test: test-random test-benchmark

test-random: saranya-shobhalatha-test-random bellman-ford-break-test-random

test-benchmark-create:
	$(MD) test-benchmark
	../cherkassky_goldberg_radzik/bin/sprand 200000 1000000 46378461 -ll32000 -lm-64000 > test-benchmark/test_raw.in
	cd test-benchmark; python3 ../parser.py > test.in

test-benchmark: test-benchmark-create BFCF-test-benchmark BFCS-test-benchmark goldfarb-hao-kai-test-benchmark goldberg-radzik-test-benchmark tarjan-test-benchmark tarjan-with-update-test-benchmark
	paste test-benchmark/*.out > test-benchmark/result.csv

%-test-random: % $(TESTER)
	$(MD) test-random/$@
	$(CP) gen.py test-random/$@
	$(CP) output/$(TESTER).o test-random/$@/tester.o
	$(CP) output/$<.o test-random/$@/tested.o
	$(CP) test.sh test-random/$@/test.sh
	cd test-random/$@; ./test.sh

%-test-benchmark: %
	echo $< > test-benchmark/$<.out
	output/$<.o -b < test-benchmark/test.in >> test-benchmark/$<.out

output/%.o: src/%.cpp
	g++ -std=c++17 -Wall -O3 -Wextra -g -Iinclude src/main.cpp $< -o $@

.PHONY: clean
clean:
	$(RMDIR) output
	$(RMDIR) test-random
	$(RMDIR) test-benchmark
