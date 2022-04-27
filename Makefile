RM = rm -f
MD	:= mkdir -p
MF := touch
CP := cp
RMDIR := rm -r -f
SYMLINK := ln -s

TESTER=bellman-ford

all: output bellman-ford bellman-ford-break saranya-shobhalatha BFCF BFCS goldfarb-hao-kai goldberg-radzik

output:
	$(MD) output

bellman-ford: output output/bellman-ford.o

bellman-ford-break: output output/bellman-ford-break.o

saranya-shobhalatha: output output/saranya-shobhalatha.o

BFCF: output output/BFCF.o

BFCS: output output/BFCS.o

goldfarb-hao-kai: output output/goldfarb-hao-kai.o

goldberg-radzik: output output/goldberg-radzik.o

test: test-random test-benchmark

test-random: saranya-shobhalatha-test-random bellman-ford-break-test-random

test-benchmark-create:
	$(MD) test-benchmark
	python3 gen.py > test-benchmark/test.in

test-benchmark: test-benchmark-create bellman-ford-test-benchmark bellman-ford-break-test-benchmark saranya-shobhalatha-test-benchmark
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
	g++ -std=c++17 -Wall -Wextra -g -Iinclude src/main.cpp $< -o $@

.PHONY: clean
clean:
	$(RMDIR) output
	$(RMDIR) test-random
	$(RMDIR) test-benchmark
