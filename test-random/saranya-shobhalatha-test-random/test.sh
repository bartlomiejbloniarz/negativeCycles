#!/bin/sh

RES=""

while [ "$RES" = "" ]
do
    python gen.py > test.in
    ./tested.o -r < test.in > tested.out
    ./tester.o -r < test.in > tester.out
    RES=$(diff tested.out tester.out)

done
