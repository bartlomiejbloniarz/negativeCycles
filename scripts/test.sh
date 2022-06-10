#!/bin/sh

RES=""

while [ "$RES" = "" ]
do
    python gen.py > test.in
    ./tested.o -r < test.in > tested.out 2> /dev/null
    ./tester.o -r < test.in > tester.out 2> /dev/null
    RES=$(diff tested.out tester.out)

done
