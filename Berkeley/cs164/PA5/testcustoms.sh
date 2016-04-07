#!/bin/bash

for i in custom_tests/*.cl; do
    echo $i
    ./script $i > $i.out.my
    ./rightscript $i > $i.out.ref
    diff $i.out.my $i.out.ref > $i.out.diff
    DIFF=$(cat $i.out.diff)
    if [ "$DIFF" != "" ]
    then
	echo $i >> failed_tests
    fi
done
